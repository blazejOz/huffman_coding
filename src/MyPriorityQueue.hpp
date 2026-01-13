#ifndef MY_PRIORITY_QUEUE_HPP
#define MY_PRIORITY_QUEUE_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MyPriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            // Używamy operatora < , więc T musi go obsługiwać
            if (heap[idx] < heap[parent]) {
                std::swap(heap[idx], heap[parent]);
                idx = parent;
            } else break;
        }
    }

    void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heap.size() && heap[left] < heap[smallest]) smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest]) smallest = right;

        if (smallest != idx) {
            std::swap(heap[idx], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Dodawanie elementu
    void push(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Usuwanie i zwracanie najmniejszego elementu i naprawa stosu
    T pop() {
        if (heap.empty()) throw std::out_of_range("Queue is empty");
        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return root;
    }

    // Budowanie z vectora
    void build(const std::vector<T>& data) {
        heap = data;
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    bool isEmpty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }
};

#endif