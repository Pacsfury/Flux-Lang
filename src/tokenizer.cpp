#include <iostream>
#include <string>
#include <vector>
#include "../include/tokenizer.hpp"

std::pair<std::vector<Token>, int>& getTokens(std::string src) {
    std::vector<Token> tokens;
    
    for (size_t idx = 0; idx < src.length(); idx++) {
        char actual = src[idx];
        
        if (std::isspace(actual)) {
            continue;
        }

        Token tok;
        switch (actual) {
            case '<': 
                tok.type = TokenType::lcpy;
                tokens.push_back(tok);
                break;
            case '>': 
                tok.type = TokenType::rcpy;
                tokens.push_back(tok);
                break;
            case ';':
                tok.type = TokenType::semicolon;
                tokens.push_back(tok);
                break;
            default: {
                std::string buffer = "";
                size_t j = 0;
                bool is_on_string = false;
                
                while (idx + j < src.length() && 
                       (!std::isspace(src[idx + j]) || is_on_string) && 
                       src[idx + j] != '<' && 
                       src[idx + j] != '>' && 
                       src[idx + j] != ';') {
                    if (src[idx + j] == '"') is_on_string = !is_on_string;
                    buffer += src[idx + j];
                    j++;
                }
                
                tok.type = TokenType::name;
                tok.value = buffer;
                tokens.push_back(tok);
                
                idx += j - 1; 
                break;
            }
        }
    }
    
    static std::pair<std::vector<Token>, int> pair;
    pair = {tokens, static_cast<int>(tokens.size())};
    return pair;
}

void printTokens(const std::pair<std::vector<Token>, int>& tokenData) {
    for (size_t i = 0; i < tokenData.second; i++) {
        switch (tokenData.first[i].type) {
            case TokenType::lcpy:
                std::cout << "LCPY\n";
                break;
            case TokenType::rcpy:
                std::cout << "RCPY\n";
                break;
            case TokenType::name:
                std::cout << tokenData.first[i].value << ": NAME\n";
                break;
            case TokenType::semicolon:
                std::cout << ";\n";
                break;
            default:
                std::cout << tokenData.first[i].value << ": UNKNOWN\n";
                break;
        }
    }
}