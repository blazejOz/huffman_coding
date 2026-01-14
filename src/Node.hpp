#ifndef NODE_HPP
#define NODE_HPP

struct Node{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

};

// Structure for node comparison in MyPriorityQueue.hpp
struct NodeComparator {
    bool operator()(const Node* a, const Node* b) const {
        return a->freq < b->freq;
    }
};

#endif