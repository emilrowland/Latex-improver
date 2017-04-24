#ifndef STRINGFINDER_H
#define STRINGFINDER_H

#include <vector>
#include <string>

class stringFinder
{
    public:
        stringFinder(std::vector<std::string> stringsToFind);
        int read(char c);
    protected:
    private:
        struct Node{
            char c;
            int value = -1; //The position of the string in the input vector. If negative the node dose not have any value.
            std::vector<Node*> nextNodes;
        };
        Node* firstNode;
        void addStringToFinder(std::string newString, int pos);
        Node* posNode;
};

#endif // STRINGFINDER_H
