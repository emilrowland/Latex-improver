#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "latexImprover.h"

int main(int argc, char* argv[]){
    // argv[0] is not interesting, since it's just your program's path.
    for (int i = 1; i < argc; ++i){
        std::string filePath = argv[i];
        std::ifstream file(filePath);
        if(file){
            auto started = std::chrono::high_resolution_clock::now();
            std::stringstream buffer;
            std::stringstream out;
            buffer << file.rdbuf();
            file.close();
            latexImprover(buffer, out);
            std::ofstream file("newFile.tex");
            if (file){
                file << out.rdbuf();
                file.close();
            }
            auto done = std::chrono::high_resolution_clock::now();
            std::cout << "Executed: " << filePath << " In: " << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms" << std::endl;
        }
    }
    std::string input;
    std::cin >> input;
    return 0;
}
