#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "../include/tokenizer.hpp"
#include "../include/codegen.hpp"

void generateCode(const std::pair<std::vector<Token>, int>& tokenData) {
    FILE* output = fopen("vm/program.gosb", "w");

    if (!output) {
        std::cerr << "Error: Couldn't open output file.\n";
        return;
    }

    std::unordered_map<std::string, int> substacks;

    std::string next = "";
    std::string mode = "";
    std::string gen  = "";

    for (size_t i = 0; i<tokenData.second;i++) {
        switch (tokenData.first[i].type) {
            case TokenType::name:
                if (tokenData.first[i].value == "@stdout") {
                    if (mode == "rcpy") {
                        gen += "SCRT, 5, SGO, 5";
                        std::string str = next;

                        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
                            return c == '"' || c == '\'';
                        }), str.end());

                        for (int j = 0; j<str.size(); j++) {
                            gen += ", PUSH, " + std::to_string(static_cast<int>(str[j]));
                            gen += ", SPUSH";
                        }
                        gen +=  ", SRUN, COUT, SDROP, 5,";
                        
                        fprintf(output, "%s", gen.c_str());
                        mode = "";
                    }
                    next = "@stdout";
                } else {
                    if (mode == "lcpy") {
                        gen += "SCRT, 5, SGO, 5";
                        std::string str = tokenData.first[i].value;

                        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
                            return c == '"' || c == '\'';
                        }), str.end());

                        for (int j = 0; j<str.size(); j++) {
                            gen += ", PUSH, " + std::to_string(static_cast<int>(str[j]));
                            gen += ", SPUSH";
                        }
                        gen +=  ", SRUN, COUT, SDROP, 5,";
                        
                        fprintf(output, "%s", gen.c_str());
                        mode = "";
                    } else if (mode == "") {
                        next = tokenData.first[i].value;
                    }
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
                gen  = "";
                next = "";
                break;
        }
    }
    fclose(output);
}