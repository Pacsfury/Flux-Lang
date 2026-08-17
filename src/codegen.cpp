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
    if (str.size() >= 2 && (str.front() == '"' || str.front() == '\'') && str.back() == str.front()) {
        return str.substr(1, str.size() - 2);
    }

    auto it = vars.find(str);
    if (it != vars.end()) {
        return clean(it->second);
    } else {
        return "";
    }

    return str;
}

static void handleCopy(const std::string& source, const std::string& target, FILE* output) {
    if (target == "@stdout") {
        fprintf(output, "%s", print(clean(source)).c_str());
    }
    vars[target] = source;
}

static void handleMove(const std::string& source, const std::string& target, FILE* output) {
    if (target == "@stdout") {
        fprintf(output, "%s", print(clean(source)).c_str());
    }

    std::string val = source;
    auto it = vars.find(source);
    if (it != vars.end()) {
        val = it->second;
        vars.erase(it);
    }

    vars[target] = val;
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
                if (i >= 2) {
                    if (mode == "rcpy") {
                        handleCopy(tokens[i - 2].value, tokens[i].value, output);
                        mode = "";
                    } else if (mode == "lcpy") {
                        handleCopy(tokens[i].value, tokens[i - 2].value, output);
                        mode = "";
                    } else if (mode == "rmov") {
                        handleMove(tokens[i - 2].value, tokens[i].value, output);
                        mode = "";
                    } else if (mode == "lmov") {
                        handleMove(tokens[i].value, tokens[i - 2].value, output);
                        mode = "";
                    }
                }
                break;

            case TokenType::lcpy:
                mode = "lcpy";
                break;

            case TokenType::rcpy:
                mode = "rcpy";
                break;

            case TokenType::lmov:
                mode = "lmov";
                break;

            case TokenType::rmov:
                mode = "rmov";
                break;

            case TokenType::semicolon:
                mode = "";
                break;
        }
    }
    fclose(output);
}