#include "latexImprover.h"

#include <iostream>

#include "stringFinder.h"

latexImprover::latexImprover(std::stringstream& file, std::stringstream& output){
    std::vector<std::string> stringsToFind;
    stringsToFind.push_back("\\begin{align}");
    stringsToFind.push_back("\\end{align}");
    stringsToFind.push_back("\\begin{align}*");
    stringsToFind.push_back("\\begin{equation}");
    stringsToFind.push_back("\\end{equation}");
    stringsToFind.push_back("\\begin{equation}*");
    stringsToFind.push_back("\\left(");
    stringsToFind.push_back("\\right)");
    stringFinder* stringFinderObj = new stringFinder(stringsToFind);

    char prev_c = '\0';
    char c;
    while(file.get(c)){
        int foundPos = stringFinderObj->read(c);
        if(foundPos >= 0){
            switch(foundPos){
                case 0: latexImprover::inEnviromentAlign = true;
                        break;
                case 1: latexImprover::inEnviromentAlign = false;
                        break;
                case 2: latexImprover::inEnviromentAlign = true;
                        break;
                case 3: latexImprover::inEnviromentEquation = true;
                        break;
                case 4: latexImprover::inEnviromentEquation = false;
                        break;
                case 5: latexImprover::inEnviromentEquation = true;
                        break;
            }

        }
        if(prev_c == '\\' && (c == '(' || c == '[')){
            latexImprover::inSimpeEquation = true;
        }
        if(prev_c == '\\' && (c == ')' || c == ']')){
            latexImprover::inSimpeEquation = false;
        }

        if(latexImprover::inEnviromentAlign || latexImprover::inEnviromentEquation || latexImprover::inSimpeEquation){
            if(foundPos == 6 || foundPos == 7){
                output << c;
            }
            else if(c == '(' && prev_c != '\\'){
                output << "\\left(";
            }
            else if(c == ')' && prev_c != '\\'){
                output << "\\right)";
            }
            else{
                output << c;
            }
        }
        else{
            output << c;
        }
        prev_c = c;
    }
    std::cout << std::endl;
}
