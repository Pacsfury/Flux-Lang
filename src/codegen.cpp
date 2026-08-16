#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../include/codegen.hpp"
#include "../include/tokenizer.hpp"

void generateCode(const std::pair<std::vector<Token>, int>& tokenData) {
    FILE* output = fopen("vm/program.gosb", "w");

    if (!output) {
        std::cerr << "Error: Couldn't open output file.\n";
        return;
    }

    std::unordered_map<std::string, std::string> vars;

    std::string next = "";
    std::string mode = "";
    std::string gen = "";

    for (size_t i = 0; i < tokenData.second; i++) {
        switch (tokenData.first[i].type) { // Current token type
            case TokenType::name: 
                if (tokenData.first[i].value == "@stdout") { // Is current @stdout?
                    if (mode == "rcpy") { // If it is, then, print A, as A > @stdout
                        gen += "SCRT, 5, SGO, 5"; // Create the substack
                        std::string str = next;

                        //// TODO: MAKE A TOKEN TYPE FOR STRINGS
                        if ((str[0] == '"' || str[0] == '\'') && str[str.size()] == str[0]) { // Is it a string
                            str.erase(
                                std::remove_if(
                                    str.begin(), str.end(),
                                    [](char c) { return c == '"' || c == '\''; }),
                                str.end());
                        } else {
                            str = vars[str];
                            str.erase(
                                std::remove_if(
                                    str.begin(), str.end(),
                                    [](char c) { return c == '"' || c == '\''; }),
                                str.end());
                        }

                        for (int j = 0; j < str.size(); j++) {
                            gen += ", PUSH, " +
                                   std::to_string(static_cast<int>(str[j]));
                            gen += ", SPUSH"; // Push the character to main stack and then to substack
                        }
                        gen += ", SRUN, COUT, SDROP, 5,"; // execute cout to substack and delete it

                        fprintf(output, "%s", gen.c_str());
                        gen = "";
                        mode = "";
                    }
                    next = "@stdout";
                } else { // It isn't @stdout?
                    if (mode == "lcpy" && tokenData.first[i-2].value == "@stdout") { // If its <, then, is the next token after < stdout? 
                        gen += "SCRT, 5, SGO, 5";
                        std::string str = tokenData.first[i].value;

                        //// TODO: MAKE A TOKEN TYPE FOR STRINGS
                        if ((str[0] == '"' || str[0] == '\'') && str[str.size()] == str[0]) { // Is it a string
                            str.erase(
                                std::remove_if(
                                    str.begin(), str.end(),
                                    [](char c) { return c == '"' || c == '\''; }),
                                str.end());
                        } else {
                            str = vars[str];
                            str.erase(
                                std::remove_if(
                                    str.begin(), str.end(),
                                    [](char c) { return c == '"' || c == '\''; }),
                                str.end());
                        }

                        for (int j = 0; j < str.size(); j++) {
                            gen += ", PUSH, " +
                                   std::to_string(static_cast<int>(str[j]));
                            gen += ", SPUSH";
                        }
                        gen += ", SRUN, COUT, SDROP, 5,";

                        fprintf(output, "%s", gen.c_str());
                        gen = "";
                        mode = "";
                    } else if (mode == "lcpy") { // Then it is just a variable
                        vars[tokenData.first[i-2].value] = tokenData.first[i].value;
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
                gen = "";
                next = "";
                break;
        }
    }
    fclose(output);
}
