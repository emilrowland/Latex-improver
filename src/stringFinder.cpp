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
}

int stringFinder::read(char c){
    try{
        stringFinder::posNode = stringFinder::posNode->nextNodes.at(c);
        return stringFinder::posNode->value;
    }
    catch (const std::out_of_range& oor){}
    stringFinder::posNode = stringFinder::firstNode;
    try{
        stringFinder::posNode = stringFinder::posNode->nextNodes.at(c);
        return stringFinder::posNode->value;
    }
    catch (const std::out_of_range& oor){}
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
