#include <iostream>
#include <vector>
#include <string>
#include "../include/tokenizer.hpp"
#include "../include/codegen.hpp"

int main() {
    auto tokens = getTokens("@stdout < 'hi';");
    generateCode(tokens);
    return 0;
}