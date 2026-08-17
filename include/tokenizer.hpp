#pragma once
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

enum TokenType { name, lcpy, rcpy, lmov, rmov, semicolon };

struct Token {
    TokenType type;
    std::string value;
};

std::pair<std::vector<Token>, int> getTokens(std::string src);
void printTokens(const std::pair<std::vector<Token>, int>& tokenData);