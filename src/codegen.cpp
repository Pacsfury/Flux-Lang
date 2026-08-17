#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/codegen.hpp"
#include "../include/tokenizer.hpp"

std::unordered_map<std::string, std::string> vars;

std::string print(const std::string& text) {
    std::string gen = "SCRT, 5, SGO, 5";
    for (char c : text) {
        gen += ", PUSH, " + std::to_string(static_cast<unsigned char>(c));
        gen += ", SPUSH";
    }
    gen += ", SRUN, COUT, SDROP, 5,";
    return gen;
}

std::string clean(std::string str) {
    //// TODO: ADD A STRING TOKEN TYPE
    if (str.size() >= 2 && (str.front() == '"' || str.front() == '\'') && str.back() == str.front()) {
        return str.substr(1, str.size() - 2);
    } else {
        return clean(vars[str]);
    }
    return str;
}

void generateCode(const std::pair<std::vector<Token>, int>& tokenData) {
    FILE* output = fopen("vm/program.gosb", "w");
    if (!output) {
        std::cerr << "Error: Couldn't open output file.\n";
        return;
    }

    std::string mode = "";
    const auto& tokens = tokenData.first;
    size_t tokenCount = tokenData.second;

    for (size_t i = 0; i < tokenCount; i++) {
        switch (tokens[i].type) {
            case TokenType::name:
                if (mode == "rcpy" && i >= 2) {
                    const std::string& source = tokens[i - 2].value;
                    const std::string& target = tokens[i].value;

                    if (target == "@stdout") {
                        fprintf(output, "%s", print(clean(source)).c_str());
                    }
                    vars[target] = source;
                    mode = "";
                } else if (mode == "lcpy" && i >= 2) {
                    const std::string& target = tokens[i - 2].value;
                    const std::string& source = tokens[i].value;

                    if (target == "@stdout") {
                        fprintf(output, "%s", print(clean(source)).c_str());
                    }
                    vars[target] = source;

                    mode = "";
                }
                break;

            case TokenType::lcpy:
                mode = "lcpy";
                break;

            case TokenType::rcpy:
                mode = "rcpy";
                break;

            case TokenType::semicolon:
                mode = "";
                break;
        }
    }
    fclose(output);
}