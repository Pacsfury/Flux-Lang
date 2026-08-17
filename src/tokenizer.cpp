#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../include/tokenizer.hpp"

std::pair<std::vector<Token>, int> getTokens(std::string src) {
    std::vector<Token> tokens;
    bool is_on_string = false;

    for (size_t idx = 0; idx < src.length(); idx++) {
        char actual = src[idx];

        if (!is_on_string && std::isspace(actual)) {
            continue;
        }

        Token tok;
        switch (actual) {
            case '<':
                if (src[idx] +1 == '-') {
                    tok.type = TokenType::lmov;
                } else {
                    tok.type = TokenType::lcpy;
                }
                tokens.push_back(tok);
                break;
            case '-':
                if (src[idx] +1 == '>') {
                    tok.type = TokenType::rmov;
                }
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
            case '/':
                if (!is_on_string) {
                    idx++;
                    while (idx < src.length() && src[idx] != '/') {
                        idx++;
                    }
                    if (idx >= src.length()) {
                        idx = src.length() - 1; 
                    }
                    break;
                }
            default: {
              std::string buffer = "";
                
                while (idx < src.length()) {
                    char c = src[idx];
                    
                    if (c == '"') {
                        is_on_string = !is_on_string;
                    }
                    
                    if (!is_on_string) {
                        if (std::isspace(static_cast<unsigned char>(c)) || 
                            c == '<' || c == '>' || c == ';' || c == '/') {
                            break; 
                        }
                    }
                    
                    buffer += c;
                    idx++;
                }

                if (!buffer.empty()) {
                    tok.type = TokenType::name;
                    tok.value = buffer;
                    tokens.push_back(tok);
                }

                idx--; 
                break;
            }
        }
    }

    return {tokens, static_cast<int>(tokens.size())};
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