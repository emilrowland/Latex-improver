#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <vector>
class KMP
{
    public:
        KMP(std::string pattern, int* next, int next_size);
        bool read(char c);
    protected:
    private:
        int KMP_pos = 0;
        std::vector<int> KMP_next;
        std::vector<char> KMP_pattern;
};

#endif // KMP_H
