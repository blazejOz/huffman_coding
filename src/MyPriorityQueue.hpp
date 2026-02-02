#ifndef MY_PRIORITY_QUEUE_HPP
#define MY_PRIORITY_QUEUE_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <iostream>
#include "Node.hpp"

class MyPriorityQueue {
private:
    std::vector<Node*> heap;
    NodeComparator compare;

    void heapifyUp(int idx);
    void heapifyDown(int idx);


public:
    void push(Node* node);
    Node* pop();

    void build(const std::vector<Node*>& data);

    bool isEmpty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }

    void print();
};

#endif