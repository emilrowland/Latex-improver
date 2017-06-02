#include "KMP.h"

KMP::KMP(std::string pattern, int* next, int next_size){
    KMP::KMP_next.assign(next, next + next_size/sizeof(int));
    KMP::KMP_next.insert(KMP::KMP_next.begin(), 0);
    std::copy(pattern.begin(), pattern.end(), std::back_inserter(KMP::KMP_pattern));
}
bool KMP::read(char c){
    unsigned int i = KMP::KMP_pos;
    if(c == KMP::KMP_pattern[i]){
        i ++;
        if(i >= KMP::KMP_pattern.size()){
            KMP::KMP_pos = 0;
            return true;
        }
    }
    else{
        while(i > 1){
            i = KMP::KMP_next[i];
            KMP::KMP_pos = i;
            KMP::read(c);
        }
    }
    KMP::KMP_pos = i;
    return false;
}
