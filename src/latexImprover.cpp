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
    stringsToFind.push_back("\\left[");
    stringsToFind.push_back("\\right]");
    stringsToFind.push_back("\\label{");
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
                case 10:    latexImprover::inLabel = true;
                            break;
            }

        }
        if(prev_c == '\\' && (c == '(' || c == '[')){
            latexImprover::inSimpeEquation = true;
        }
        else if(prev_c == '\\' && (c == ')' || c == ']')){
            latexImprover::inSimpeEquation = false;
        }
        else if(c == '}' && latexImprover::inLabel){
            latexImprover::inLabel = false;
        }

        if((latexImprover::inEnviromentAlign || latexImprover::inEnviromentEquation || latexImprover::inSimpeEquation) && !latexImprover::inLabel){
            if(foundPos >= 6 && foundPos <= 9){ // foundPos in range 6 to 9
                output << c;
            }
            if(prev_c != '\\'){
                if(c == '('){
                    output << "\\left(";
                }
                else if(c == ')'){
                    output << "\\right)";
                }
                else if(c == '['){
                    output << "\\left[";
                }
                else if(c == ']'){
                    output << "\\right]";
                }
                else{
                    output << c;
                }
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
}
