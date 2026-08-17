#pragma once
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "tokenizer.hpp"

void generateCode(const std::pair<std::vector<Token>, int>& tokenData);

std::string print(const std::string& text);

std::string clean(std::string str);