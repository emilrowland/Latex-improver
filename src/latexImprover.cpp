#include "latexImprover.h"

#include <iostream>

#include "KMP.h"

latexImprover::latexImprover(std::stringstream& file, std::stringstream& output){
    //Init KMP
    int KMP_enviromentAlign_begin_next [] = {0,1,1,1,1,1,1,1,1,1,1,1,1};
    KMP* KMP_enviromentAlign_begin = new KMP("\\begin{align}", KMP_enviromentAlign_begin_next, sizeof(KMP_enviromentAlign_begin_next));
    int KMP_enviromentAlign_end_next [] = {0,1,1,1,1,1,1,1,1,1,1};
    KMP* KMP_enviromentAlign_end = new KMP("\\end{align}", KMP_enviromentAlign_end_next, sizeof(KMP_enviromentAlign_begin_next));
    int KMP_leftParenthes_next [] = {0,1,1,1,1};
    KMP* KMP_leftParenthes = new KMP("\\left(", KMP_leftParenthes_next, sizeof(KMP_leftParenthes_next));
    int KMP_rightParenthes_next [] = {0,1,1,1,1,1};
    KMP* KMP_rightParenthes = new KMP("\\right)", KMP_rightParenthes_next, sizeof(KMP_rightParenthes_next));

    char c;
    while(file.get(c)){
        if(KMP_enviromentAlign_begin->read(c)){
            latexImprover::inEnviromentAlign = true;
        }
        if(KMP_enviromentAlign_end->read(c)){
            latexImprover::inEnviromentAlign = false;
        }

        if(latexImprover::inEnviromentAlign){
            if(KMP_leftParenthes->read(c) || KMP_rightParenthes->read(c)){
                output << c;
            }
            else if(c == '('){
                output << "\\left(";
            }
            else if(c == ')'){
                output << "\\right)";
            }
            else{
                output << c;
            }
        }
        else{
            output << c;
        }
    }
    std::cout << std::endl;
}
