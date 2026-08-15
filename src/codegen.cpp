#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <unordered_map>
#include "../include/tokenizer.hpp"
#include "../include/codegen.hpp"

void generateCode(const std::pair<std::vector<Token>, int>& tokenData) {
    FILE* output = fopen("vm/program.gosb", "w");
    std::unordered_map<std::string, int> substacks;
    std::string next;
    std::string mode;
    std::string gen = "";

    for (size_t i = 0; i<tokenData.second;i++) {
        switch (tokenData.first[i].type) {
            case TokenType::name:
                if (tokenData.first[i].value == "@stdout") {
                    next = "@stdout";
                } else {
                    if (mode == "lcpy" && next == "@stdout") {
                        gen += "SCRT, 5, SGO, 5";
                        for (int j = 0; j< tokenData.first[i].value.size(); j++) {
                            gen += ", PUSH, " + std::to_string(static_cast<int>(tokenData.first[i].value[j]));
                            gen += ", SPUSH";
                        }
                        gen +=  ", SRUN, COUT, ";
                        
                        fprintf(output, "%s", gen.c_str());
                    }
                }
                break;
            case TokenType::lcpy:
                mode = "lcpy";
                break;
            case TokenType::rcpy:
                break;
            case TokenType::semicolon:
                break;
        }
    }
    fclose(output);
}