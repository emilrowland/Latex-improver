#include <iostream>
#include <fstream>
#include <sstream>
#include "latexImprover.h"

int main(int argc, char* argv[]){
    // argv[0] is not interesting, since it's just your program's path.
    for (int i = 1; i < argc; ++i){
        std::string filePath = argv[i];
        std::ifstream file(filePath);
        if(file){
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            latexImprover* latex = new latexImprover(buffer);
        }
    }
    std::cout << "Completed ";
    std::string line;
    std::cin >> line;
    return 0;
}
