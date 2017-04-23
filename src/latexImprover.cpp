#include "latexImprover.h"

#include <iostream>

#include "KMP.h"

latexImprover::latexImprover(std::stringstream& file){
    //Init KMP
    int KMP_enviromentAlign_begin_next [] = {0,1,1,1,1,1,1,1,1,1,1,1,1};
    KMP* KMP_enviromentAlign_begin = new KMP("\\begin{align}", KMP_enviromentAlign_begin_next, sizeof(KMP_enviromentAlign_begin_next));
    int KMP_enviromentAlign_end_next [] = {0,1,1,1,1,1,1,1,1,1,1};
    KMP* KMP_enviromentAlign_end = new KMP("\\end{align}", KMP_enviromentAlign_end_next, sizeof(KMP_enviromentAlign_begin_next));

    char c;
    while(file.get(c)){
        if(KMP_enviromentAlign_begin->read(c)){
            latexImprover::inEnviromentAlign = true;
        }
        if(KMP_enviromentAlign_end->read(c)){
            latexImprover::inEnviromentAlign = false;
        }

        if(latexImprover::inEnviromentAlign){

        }
    }
    std::cout << std::endl;
}
