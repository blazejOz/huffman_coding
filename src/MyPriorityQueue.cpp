#include "MyPriorityQueue.hpp"
#include <algorithm>

void MyPriorityQueue::heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        // If parent frequency > current frequency, swap
        if (compare(heap[parent], heap[idx])) {
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void MyPriorityQueue::heapifyDown(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // Check if left child exists and is SMALLER than current smallest
    // Since compare(a, b) is (a->freq > b->freq), 
    // compare(heap[smallest], heap[left]) returns true if smallest is larger than left.
    if (left < (int)heap.size() && compare(heap[smallest], heap[left])) {
        smallest = left;
    }

    // Check if right child exists and is SMALLER than current smallest
    if (right < (int)heap.size() && compare(heap[smallest], heap[right])) {
        smallest = right;
    }

    if (smallest != idx) {
        std::swap(heap[idx], heap[smallest]);
        heapifyDown(smallest);
    }
}

void MyPriorityQueue::push(Node* node) {
    heap.push_back(node);
    heapifyUp((int)heap.size() - 1);
}

Node* MyPriorityQueue::pop() {
    if (heap.empty()) throw std::out_of_range("Queue is empty");
    
    Node* root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return root;
}

void MyPriorityQueue::build(const std::vector<Node*>& data) {
    heap = data;
    // Start from the last non-leaf node and move up
    for (int i = ((int)heap.size() / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

void MyPriorityQueue::print(){
    for(Node* node: heap){
        std::cout << node->freq << ":" << node->ch << ' ';
    }
    std::cout << std::endl;
}

