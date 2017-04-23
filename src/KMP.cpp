#include "KMP.h"

KMP::KMP(std::string pattern, int* next, int next_size){
    KMP::KMP_next.assign(next, next + next_size/sizeof(int));
    std::copy(pattern.begin(), pattern.end(), std::back_inserter(KMP::KMP_pattern));
}
bool KMP::read(char c){
    int i = KMP::KMP_pos - 1;
    if(i == -1){
        i = 0;
    }
    if(c == KMP::KMP_pattern[i]){
        i += 2;
        if(i >= KMP::KMP_pattern.size() + 1){
            KMP::KMP_pos = 0;
            return true;
        }
    }
    else{
        i = KMP::KMP_next[i];
    }
    KMP::KMP_pos = i;
    return false;
}
