#include <iostream>
#include <string>
#include <vector>
#include "src/MyPriorityQueue.hpp"



int main() {
   
    MyPriorityQueue myQueue;
    std::vector<Node*> nodes;

    nodes.push_back(new Node("A", 10));
    nodes.push_back(new Node("B", 3));
    nodes.push_back(new Node("C", 15));
    nodes.push_back(new Node("D", 1));
    nodes.push_back(new Node("E", 7));
    
    myQueue.build(nodes);
    myQueue.print();
    


    return 0;
}