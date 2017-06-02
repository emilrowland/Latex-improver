#include "latexImprover.h"

#include <iostream>

#include "stringFinder.h"

latexImprover::latexImprover(std::stringstream& file, std::stringstream& output){
    std::vector<latexImprover::ReplaceInstruction> inst = latexImprover::preFormater(file);
    file.clear();
    file.seekg(0,file.beg);
    latexImprover::formater(file, output, inst);
}
std::vector<latexImprover::ReplaceInstruction> latexImprover::preFormater(std::stringstream& file){
    std::vector<std::string> stringsToFind;
    stringsToFind.push_back("\\begin{align}"); //0
    stringsToFind.push_back("\\end{align}");
    stringsToFind.push_back("\\begin{align*}");
    stringsToFind.push_back("\\begin{equation}");
    stringsToFind.push_back("\\end{equation}");
    stringsToFind.push_back("\\begin{equation*}"); //5
    stringsToFind.push_back("\\left(");
    stringsToFind.push_back("\\right)");
    stringsToFind.push_back("\\left[");
    stringsToFind.push_back("\\right]");
    stringsToFind.push_back("\\label{"); //10
    stringsToFind.push_back("\\end{equation*}");
    stringsToFind.push_back("\\end{align*}");
    stringsToFind.push_back("\\usepackage{amsmath}");
    stringFinder* stringFinderObj = new stringFinder(stringsToFind);

    std::vector<latexImprover::ReplaceInstruction> outputVect;

    char prev_c = '\0';
    char c;
    int pos = 0;
    while(file.get(c)){
        if(c == '%' && prev_c != '\\'){
            //Comment line
            std::string line;
            std::getline(file, line); //get rest of comment line
            pos += line.size() + 2;
            continue; //We don't need to run anything below if comment.
        }
        int foundPos = stringFinderObj->read(c);
        if(foundPos >= 0){
            switch(foundPos){
                case 0:     latexImprover::inEnviromentAlign = true;
                            break;
                case 1:     latexImprover::inEnviromentAlign = false;
                            break;
                case 2:     latexImprover::inEnviromentAlign = true;
                            break;
                case 3:     latexImprover::inEnviromentEquation = true;
                            break;
                case 4:     latexImprover::inEnviromentEquation = false;
                            break;
                case 5:     latexImprover::inEnviromentEquation = true;
                            break;
                case 10:    latexImprover::inLabel = true;
                            break;
                case 11:    latexImprover::inEnviromentEquation = false;
                            break;
                case 12:    latexImprover::inEnviromentAlign = false;
                            break;
                case 13:    latexImprover::usePackageAmsmath = true;
                            break;
            }

        }
        if(prev_c == '\\' && (c == '(' || c == '[')){
            latexImprover::inSimpelEquation = true;
        }
        else if(prev_c == '\\' && (c == ')' || c == ']')){
            latexImprover::inSimpelEquation = false;
        }
        else if(c == '}' && latexImprover::inLabel){
            latexImprover::inLabel = false;
        }
        else if(c == '$'){
            if(latexImprover::inShortEquation){
                latexImprover::inShortEquation = false;
            }
            else{
                latexImprover::inShortEquation = true;
            }
        }

        if((latexImprover::inEnviromentAlign || latexImprover::inEnviromentEquation || latexImprover::inSimpelEquation || latexImprover::inShortEquation)
            && !latexImprover::inLabel && latexImprover::usePackageAmsmath){
            if(foundPos >= 6 && foundPos <= 9){ // foundPos in range 6 to 9
            }
            else if(prev_c != '\\'){
                if(c == '('){
                    latexImprover::ReplaceInstruction output;
                    output.pos = pos;
                    output.replacment = "\\left(";
                    outputVect.push_back(output);
                }
                else if(c == ')'){
                    latexImprover::ReplaceInstruction output;
                    output.pos = pos;
                    output.replacment = "\\right)";
                    outputVect.push_back(output);
                }
                else if(c == '['){
                    latexImprover::ReplaceInstruction output;
                    output.pos = pos;
                    output.replacment = "\\left[";
                    outputVect.push_back(output);
                }
                else if(c == ']'){
                    latexImprover::ReplaceInstruction output;
                    output.pos = pos;
                    output.replacment = "\\right]";
                    outputVect.push_back(output);
                }
            }
        }
        prev_c = c;
        pos++;
    }
    return outputVect;
}
void latexImprover::formater(std::stringstream& file, std::stringstream& output, std::vector<ReplaceInstruction> instructions){
    char c;
    int pos = 0;
    while(file.get(c)){
        if(instructions.empty()){ //No more special things we can output the rest directly
            output << file.str();
            break;
        }
        else if(instructions.front().pos == pos){

            output << instructions.front().replacment;
            pos += instructions.front().replacment.size();

            instructions.erase(instructions.begin());
        }
        else{
            output << c;
        }
        pos++;
    }
}
