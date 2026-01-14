#include <iostream>
#include <string>
#include "src/MyPriorityQueue.hpp" 
#include "src/Node.hpp"

template <typename T>
void printSortedMPQ(MyPriorityQueue<T> queue) { 
    while (!queue.isEmpty()) {
        std::cout << queue.pop() << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Kolejka dla intów
    MyPriorityQueue<int> intQueue;
    intQueue.push(10);
    intQueue.push(5);
    intQueue.push(20);
    std::cout << "Sorted PriorityQueue: "; printSortedMPQ(intQueue);
    std::cout << "Najmniejszy int: " << intQueue.pop() << std::endl; // Wynik: 5

    // Kolejka dla stringów 
    MyPriorityQueue<std::string> stringQueue;
    stringQueue.push("Zebra");
    stringQueue.push("Alfa");
    stringQueue.push("Gama");
    std::cout << "Sorted PriorityQueue: "; printSortedMPQ(stringQueue);
    std::cout << "Pierwszy string: " << stringQueue.pop() << std::endl; // Wynik: Alfa


    MyPriorityQueue<Node*, NodeComparator> nodeQueue;
    nodeQueue.push(new Node('A', 10));
    nodeQueue.push(new Node('B', 5));
    nodeQueue.push(new Node('C', 1));
    nodeQueue.push(new Node('X', 100));
    Node *top = nodeQueue.pop();
    std::cout << "Pierwszy Node: " << top->ch << ":" << top->freq << std::endl; 
    

    return 0;
}