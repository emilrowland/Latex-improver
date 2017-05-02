#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstring>
#include "latexImprover.h"

int main(int argc, char* argv[]){
    // argv[0] is not interesting, since it's just the program's path.
    bool debug = false;
    int fileCount = 0;
    for (int i = 1; i < argc; ++i){
        if(std::strcmp(argv[i], "-d") == 0){
            debug = true;
        }
        else{
            fileCount++;
            std::string filePath = argv[i];
            std::ifstream file(filePath);
            if(file){
                auto started = std::chrono::high_resolution_clock::now();
                std::stringstream buffer;
                std::stringstream out;
                buffer << file.rdbuf();
                file.close();
                latexImprover(buffer, out);
                std::ofstream file("newFile" + std::to_string(fileCount) + ".tex");
                if (file){
                    file << out.rdbuf();
                    file.close();
                }
                if(debug){
                    auto done = std::chrono::high_resolution_clock::now();
                    std::cout << "Executed: " << filePath << " In: " << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << "ms" << std::endl;
                }
            }
        }
    }
    return 0;
}
