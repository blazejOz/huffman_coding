#include <iostream>
#include <string>
#include "src/MyPriorityQueue.hpp" 

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
    printSortedMPQ(intQueue);
    std::cout << "Najmniejszy int: " << intQueue.pop() << std::endl; // Wynik: 5

    // Kolejka dla stringów 
    MyPriorityQueue<std::string> stringQueue;
    stringQueue.push("Zebra");
    stringQueue.push("Alfa");
    stringQueue.push("Gama");
    printSortedMPQ(stringQueue);
    std::cout << "Pierwszy string: " << stringQueue.pop() << std::endl; // Wynik: Alfa

    return 0;
}