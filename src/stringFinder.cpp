#include "stringFinder.h"

#include <iostream>
#include <stdexcept>

stringFinder::stringFinder(std::vector<std::string> stringsToFind){
    Node* first = new Node();
    first->c = '\0';
    first->value = -1;
    stringFinder::firstNode = first;
    stringFinder::posNode = first;
    for(unsigned int i = 0; i < stringsToFind.size(); i++){
        stringFinder::addStringToFinder(stringsToFind.at(i), i);
    }
    #ifndef NDEBUG //DEBUG code
        std::cout << "Size of empty stringFinder node: " << sizeof(Node) << "B" << std::endl;
        std::tuple<int, int> values = stringFinder::getMemoryUsage(stringFinder::firstNode);
        std::cout << "Memory usage of all nodes in the stringFinder: " << std::get<0>(values) << "B and uses: " << std::get<1>(values) << " Nodes" << std::endl;
    #endif // NDEBUG
}

stringFinder::~stringFinder(){
    delete stringFinder::destroyNodes(stringFinder::firstNode);
}

int stringFinder::read(char c){
    try{//Test if char exists in nodes.
        stringFinder::posNode = stringFinder::posNode->nextNodes.at(c);
        return stringFinder::posNode->value;
    }
    catch (const std::out_of_range& oor){}//Char did't exists in node.
    try{//Test if char exists in start node.
        stringFinder::posNode = stringFinder::firstNode->nextNodes.at(c);
        return stringFinder::posNode->value;
    }
    catch (const std::out_of_range& oor){}//Can't find the char in the start node set posNode to start node.
    stringFinder::posNode = stringFinder::firstNode;
    return -1;
}

void stringFinder::addStringToFinder(std::string newString, int pos){
    Node* currentNode = stringFinder::firstNode;
    for(std::string::size_type i = 0; i < newString.size(); ++i) {
        try{
            currentNode = currentNode->nextNodes.at(newString[i]);
        }
        catch (const std::out_of_range& oor){
            Node* next = new Node();
            next->c = newString[i];
            next->value = -1;
            currentNode->nextNodes[newString[i]] = next;
            currentNode = next;
        }
    }
    currentNode->value = pos;
}

stringFinder::Node* stringFinder::destroyNodes(Node* node){
    std::unordered_map<char, Node*>::iterator it = node->nextNodes.begin();
    while(it != node->nextNodes.end()){
        delete stringFinder::destroyNodes(it->second); //Recursive call
        ++it;
    }
    return node;
}

#ifndef NDEBUG //DEBUG code
    std::tuple<int, int> stringFinder::getMemoryUsage(Node* node){
        int memoryUsage = sizeof(*node);
        int num = 1;
        std::unordered_map<char, Node*>::iterator it = node->nextNodes.begin();
        while(it != node->nextNodes.end()){
            std::tuple<int, int> values = stringFinder::getMemoryUsage(it->second); //Recursive call
            memoryUsage += std::get<0>(values);
            num += std::get<1>(values);
            ++it;
        }
        return std::make_tuple(memoryUsage, num);
    }
#endif // NDEBUG
