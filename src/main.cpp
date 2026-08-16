#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/arguments.hpp"
#include "../include/codegen.hpp"
#include "../include/tokenizer.hpp"

int main(int argc, char* argv[]) {
    ArgsContext args(argc, argv);

    if (args.hasArg("--test")) {
        return 0;
    }

    if (args.hasArg("run")) {
        std::ifstream file((std::string(args.getArg("run").value())));

        if (!file) {
            std::cerr << "Error: Couldn't open file.\n";
            return 1;
        }

        std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        auto tokens = getTokens(source);
        generateCode(tokens);
        system("cd vm && go run .");
    }
    return 0;
}