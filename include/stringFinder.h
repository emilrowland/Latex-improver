#ifndef STRINGFINDER_H
#define STRINGFINDER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>

class stringFinder
{
    public:
        stringFinder(std::vector<std::string> stringsToFind);
        int read(char c);
        bool debug;
    protected:
    private:
        struct Node{
            char c;
            int value = -1; //The position of the string in the input vector. If negative the node dose not have any value.
            std::unordered_map<char, Node*> nextNodes; //Hash table
        };
        Node* firstNode;
        void addStringToFinder(std::string newString, int pos);
        Node* posNode;
    public:
        std::tuple<int, int> getMemoryUsage(Node* node); //Returns (memoryUsage, numberOfNodes)
};

#endif // STRINGFINDER_H
