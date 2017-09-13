#include "latexImprover.h"

#include <iostream>
#include <stack>

#include "stringFinder.h"

latexImprover::latexImprover(std::stringstream& file, std::stringstream& output){
    std::vector<latexImprover::ReplaceInstruction*> inst = latexImprover::preFormater(file);
    file.clear();
    file.seekg(0, file.beg);
    latexImprover::formater(file, output, inst);

    //Clean
    for(unsigned int i = 0; i < inst.size(); i++){
        delete inst.at(i);
    }
}
std::vector<latexImprover::ReplaceInstruction*> latexImprover::preFormater(std::stringstream& file){
    //String finder
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

    //Replace instruction
    std::vector<latexImprover::ReplaceInstruction*> outputVect;
    std::vector<latexImprover::ReplaceInstruction*> instParamVect;

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
            if((foundPos >= 6 && foundPos <= 9) || prev_c == '\\' || c == '^' || c == '_'){ // foundPos in range 6 to 9 or prev_c is '\\'
                //If it is a command inside an equation
                for(unsigned int i = 0; i < instParamVect.size(); i++){
                    instParamVect.at(i)->active = true;
                }
            }
            else{
                if(c == '('){
                    latexImprover::ReplaceInstruction* output = new latexImprover::ReplaceInstruction;
                    output->pos = pos;
                    output->replacment = "\\left(";
                    output->active = false;
                    outputVect.push_back(output);
                    instParamVect.push_back(output);
                }
                else if(c == ')'){
                    latexImprover::ReplaceInstruction* output = new latexImprover::ReplaceInstruction;
                    output->pos = pos;
                    output->replacment = "\\right)";
                    outputVect.push_back(output);
                    latexImprover::ReplaceInstruction* popRes = instParamVect.back();
                    instParamVect.pop_back();
                    output->active = popRes->active;
                }
                else if(c == '['){
                    latexImprover::ReplaceInstruction* output = new latexImprover::ReplaceInstruction;
                    output->pos = pos;
                    output->replacment = "\\left[";
                    output->active = false;
                    outputVect.push_back(output);
                    instParamVect.push_back(output);
                }
                else if(c == ']'){
                    latexImprover::ReplaceInstruction* output = new latexImprover::ReplaceInstruction;
                    output->pos = pos;
                    output->replacment = "\\right]";
                    outputVect.push_back(output);
                    latexImprover::ReplaceInstruction* popRes = instParamVect.back();
                    instParamVect.pop_back();
                    output->active = popRes->active;
                }
            }
        }
        prev_c = c;
        pos++;
    }
    delete stringFinderObj;
    return outputVect;
}
void latexImprover::formater(std::stringstream& file, std::stringstream& output, std::vector<ReplaceInstruction*> instructions){
    char c;
    int pos = 0;
    while(file.get(c)){
        if(instructions.empty()){ //No more special things we can output the rest directly
            output << c;
            continue;
        }
        else if(instructions.front()->pos == pos){
            if(instructions.front()->active){
                output << instructions.front()->replacment;
            }
            else{
                output << c;
            }
            instructions.erase(instructions.begin());
        }
        else{
            output << c;
        }
        pos++;
    }
}
