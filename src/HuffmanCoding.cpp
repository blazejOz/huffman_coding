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
    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile.is_open()) return;

    std::stringstream ss;
    ss << inFile.rdbuf();
    std::string text = ss.str();
    inFile.close();

    if (text.empty()) return;

    this->dictionary = generateDictionary(text);
    buildTree(this->dictionary);
    huffmanCodes.clear(); // Clear old codes if any
    generateCodes(this->root, "");

    // Open file in BINARY mode
    std::ofstream outFile(outputFilePath, std::ios::binary);
    
    // Save dictionary (text-based header is fine)
    for (auto const& [ch, freq] : this->dictionary) {
        outFile << ch << ":" << freq << " ";
    }
    outFile << "\n";

    // Binary Encoding
    unsigned char byteBuffer = 0;
    int bitCount = 0;

    for (char c : text) {
        std::string code = huffmanCodes[c];
        for (char bit : code) {
            byteBuffer <<= 1;
            if (bit == '1') byteBuffer |= 1;
            bitCount++;

            if (bitCount == 8) {
                outFile.put(byteBuffer);
                byteBuffer = 0;
                bitCount = 0;
            }
        }
    }

    // Handle remaining bits (Padding)
    if (bitCount > 0) {
        byteBuffer <<= (8 - bitCount);
        outFile.put(byteBuffer);
    }
    outFile.close();
}

// Public method: File decompression
void HuffmanCoding::decompress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile.is_open()) return;

//Generate Dictionary 
    std::string headerLine;
    if (!std::getline(inFile, headerLine) || headerLine.empty()) return;

    std::map<char, int> restoredFreqs;
    long long totalChars = 0;

    for (size_t i = 0; i < headerLine.length(); ++i) {
        if (i + 1 < headerLine.length() && headerLine[i + 1] == ':') {
            char ch = headerLine[i];
            size_t colonPos = i + 1;
            std::string numStr = "";
            size_t j = colonPos + 1;

            while (j < headerLine.length() && std::isdigit(headerLine[j])) {
                numStr += headerLine[j];
                j++;
            }

            if (!numStr.empty()) {
                restoredFreqs[ch] = std::stoi(numStr);
                totalChars += restoredFreqs[ch];
                i = j - 1;
            }
        }
    }

    // Clear old root tree
    if (root != nullptr) {
        clearTree(root);
        root = nullptr;
    }

    buildTree(restoredFreqs);

//Decode binary code:
    std::ofstream outFile(outputFilePath, std::ios::binary);
    Node* current = root;
    long long charsDecoded = 0;
    unsigned char byte;

    while (charsDecoded < totalChars && inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0 && charsDecoded < totalChars; --i) {
            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left;

            if (current->left == nullptr && current->right == nullptr) {
                outFile.put(current->ch);
                charsDecoded++;
                current = root;
            }
        }
    }
    outFile.close();
}