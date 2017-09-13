#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cstring>
#include "latexImprover.h"

static void helpMessage(){
    //Select the executable name
    #ifdef _WIN32
    const std::string EXECUTABLE = "latexImprover.exe";
    #else
    const std::string EXECUTABLE = "latexImprover";
    #endif // _WIN32


    std::cerr << "usage: " << EXECUTABLE << " [options] filenames..\n"
              << "Options:\n"
              << "\t-h\t\tShow this help message\n"
              << "\t-d\t\tDebug mode"
              << std::endl;
}

int main(int argc, char* argv[]){
    bool debug = false;
    int fileCount = 0;
    if(argc < 2){
        helpMessage();
        return 1;
    }
    for (int i = 1; i < argc; ++i){// argv[0] is not interesting, since it's just the program's path.
        if(std::strcmp(argv[i], "-d") == 0){
            debug = true;
        }
        else if(std::strcmp(argv[i], "-h") == 0){
            helpMessage();
            return 0;
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
                std::ostringstream convert;
                convert << fileCount;
                std::ofstream file("newFile" + convert.str() + ".tex");
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
    if(fileCount < 1){
        //No files has been provided
        helpMessage();
        return 1;
    }
    return 0;
}
