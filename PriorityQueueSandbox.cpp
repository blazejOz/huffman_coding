#include <iostream>
#include <string>
#include <vector>
#include "src/MyPriorityQueue.hpp" 
#include "src/Node.hpp"

// Funkcja pomocnicza
template <typename T, typename Comparator = std::less<T>>
void printSortedMPQ(MyPriorityQueue<T, Comparator> queue) { 
    while (!queue.isEmpty()) {
        std::cout << queue.pop() << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. Test dla INT
    std::vector<int> list = {1, 99, 20, 9};
    MyPriorityQueue<int> intQueue;
    intQueue.build(list); 
    intQueue.push(10);
    intQueue.push(5);
    intQueue.push(20);
    
    std::cout << "Kolejka INT: "; 
    printSortedMPQ(intQueue); // Wypisze: 1 5 9 10 20 20 99 

    // 2. Test dla STRING
    std::vector<std::string> strings = {"Zeta", "Delta"};
    MyPriorityQueue<std::string> stringQueue;
    stringQueue.build(strings);
    stringQueue.push("Zebra");
    stringQueue.push("Alfa");
    stringQueue.push("Gama");
    
    std::cout << "Kolejka STRING: "; 
    printSortedMPQ(stringQueue); // Wypisze: Alfa Delta Gama Zebra Zeta

    // 3. Test dla NODE
    MyPriorityQueue<Node*, NodeComparator> nodeQueue;
    nodeQueue.push(new Node('A', 10));
    nodeQueue.push(new Node('B', 5));
    nodeQueue.push(new Node('C', 1));
    nodeQueue.push(new Node('X', 100));
    
    Node *top = nodeQueue.pop();
    std::cout << "Najmniejszy Node (freq): " << top->ch << ":" << top->freq << std::endl; 
    
    delete top;
    while(!nodeQueue.isEmpty()) delete nodeQueue.pop();

    return 0;
}