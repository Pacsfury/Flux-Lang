#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum TokenType { name, lcpy, rcpy, semicolon };

struct Token {
    TokenType type;
    std::string value;
};

std::pair<std::vector<Token>, int> getTokens(std::string src);
void printTokens(const std::pair<std::vector<Token>, int>& tokenData);