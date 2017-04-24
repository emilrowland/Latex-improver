#include "stringFinder.h"

#include <iostream>

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
    for(unsigned int i = 0; i < stringFinder::posNode->nextNodes.size(); i++){
        if(stringFinder::posNode->nextNodes[i]->c == c){
            stringFinder::posNode = stringFinder::posNode->nextNodes[i];
            return stringFinder::posNode->value;
        }
    }
    stringFinder::posNode = stringFinder::firstNode;
    return -1;
}

void stringFinder::addStringToFinder(std::string newString, int pos){
    Node* currentNode = stringFinder::firstNode;
    for(std::string::size_type i = 0; i < newString.size(); ++i) {
        bool match = false;
        for(unsigned int j = 0; j < currentNode->nextNodes.size(); j++){
            if(currentNode->nextNodes[j]->c == newString[i]){
                currentNode = currentNode->nextNodes[j];
                match = true;
                continue;
            }
        }
        if(!match){
            Node* next = new Node();
            next->c = newString[i];
            next->value = -1;
            currentNode->nextNodes.push_back(next);
            currentNode = next;
        }
    }
    currentNode->value = pos;
}
