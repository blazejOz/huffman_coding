#include "HuffmanCoding.hpp"
#include "Node.hpp"
#include "MyPriorityQueue.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor - initializes root as nullptr
HuffmanCoding::HuffmanCoding() : root(nullptr) {
}

// Destructor - releases tree memory
HuffmanCoding::~HuffmanCoding() {
    clearTree(root);
}

// Private method: Recursive node deletion (post-order traversal)
void HuffmanCoding::clearTree(Node* currentNode) {
    if (currentNode == nullptr) return;
    clearTree(currentNode->left);
    clearTree(currentNode->right);
    delete currentNode;
}

// Private method: Counting character occurrences
std::map<char, int> HuffmanCoding::generateDictionary(const std::string& text) {
    std::map<char, int> dictionary;
    for (char c : text) {
        dictionary[c]++;
    }
    return dictionary;
}

// Private method: Building the Huffman tree using MyPriorityQueue
void HuffmanCoding::buildTree(const std::map<char, int>& frequencies) {
    MyPriorityQueue<Node*, NodeComparator> queue;

    // Create new leaf nodes from frequencies and add to the priority queue
    for (auto const& [ch, freq] : frequencies) {
        queue.push(new Node(ch, freq));
    }
    
    // HUFFMAN ALGORITHM: Merge nodes until only the root remains
    while (queue.size() > 1) {
        // Pop two nodes with the lowest frequencies
        Node* left = queue.pop();
        Node* right = queue.pop();

        // Create a new parent node
        // Its frequency is the sum of its children's frequencies
        // Character is set to '\0' as internal nodes don't store data
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // Push the parent back into the queue
        queue.push(parent);
    }

    // Set the last remaining element in the queue as the ROOT
    if (!queue.isEmpty()) {
        this->root = queue.pop();
    }
}

// Private method: Recursive code generation (0 for left, 1 for right)
void HuffmanCoding::generateCodes(Node* currentNode, std::string code) {
    if (currentNode == nullptr) return;

    // Check if it's a leaf node (no children)
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        // Save the generated bit string to the huffmanCodes map
        huffmanCodes[currentNode->ch] = code; 
        return;
    }

    // Recurse: go left (append "0") and go right (append "1")
    generateCodes(currentNode->left, code + "0");
    generateCodes(currentNode->right, code + "1");
}

// Public method: File compression
void HuffmanCoding::compress(const std::string& inputFilePath, const std::string& outputFilePath) {
    // 1. Read input file (ifstream)
    // 2. Call generateDictionary
    // 3. Call buildTree
    // 4. Call generateCodes(root, "")
    // 5. Save dictionary (frequencies) and encoded text to output file (ofstream)
}

// Public method: File decompression
void HuffmanCoding::decompress(const std::string& inputFilePath, const std::string& outputFilePath) {
    // 1. Read dictionary from the first line of the file
    // 2. Rebuild the tree (using buildTree)
    // 3. Read bits and traverse the tree from root to leaves
    // 4. Save decoded text to output file
}