#include "HuffmanCoding.hpp"
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
    MyPriorityQueue queue;
    std::vector<Node*> nodes;
    // Create new leaf nodes from frequencies and add them to the priority queue
    for (auto const& [ch, freq] : frequencies) {
        nodes.push_back(new Node(std::string(1, ch), freq));
    }
    queue.build(nodes);
    
    // HUFFMAN ALGORITHM: Merge nodes until only the root remains
    while (queue.size() > 1) {
        Node* left = queue.pop();
        Node* right = queue.pop();

        // Concatenate strings from left and right children
        std::string combinedStr = left->ch + right->ch;

        Node* parent = new Node(combinedStr, left->freq + right->freq);
        parent->left = left;
        parent->right = right;
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

    // A leaf node in a Huffman tree is defined by having no children
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        if (!currentNode->ch.empty()) {
            char actualChar = currentNode->ch[0]; 
            huffmanCodes[actualChar] = code; 
        }
        return;
    }

    // Recurse: go left (append "0") and go right (append "1")
    generateCodes(currentNode->left, code + "0");
    generateCodes(currentNode->right, code + "1");
}

// Public method: File compression
void HuffmanCoding::compress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "BŁĄD: Nie można otworzyć pliku do dekompresji: " << inputFilePath << std::endl;
        return;
    }

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
    
    // Save dictionary to file
    for (auto const& [ch, freq] : this->dictionary) {
        if (ch == '\n') outFile << "\\n:" << freq << " ";
        else if (ch == '\r') outFile << "\\r:" << freq << " ";
        else outFile << ch << ":" << freq << " ";
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

    // Handle remaining bits
    if (bitCount > 0) {
        byteBuffer <<= (8 - bitCount);
        outFile.put(byteBuffer);
    }
    outFile.close();
}

// Public method: File decompression
void HuffmanCoding::decompress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inFile(inputFilePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Can't open file: " << inputFilePath << std::endl;
        return;
    }

    // Read Dictionery Line
    std::string line;
    if (!std::getline(inFile, line) || line.empty()) {
        std::cerr << "Error: No Dictionary" << std::endl;
        return;
    }

    std::map<char, int> restoredDictionary;
    long long totalChars = 0;

    //Parse Dictionary
    for (size_t i = 0; i < line.length(); ++i) {
    //Get Key(Char)
        char ch;
        // check for \n \r
        if (line[i] == '\\' && i + 1 < line.length()) {
            if (line[i+1] == 'n') ch = '\n';
            else if (line[i+1] == 'r') ch = '\r';
            else ch = line[i]; 
            i++; 
        } else {
            ch = line[i];
        }

    //Get Value(Number)    
        size_t colonPos = line.find(':', i + 1);
        if (colonPos != std::string::npos) {
            std::string numStr = "";
            size_t j = colonPos + 1;
            //build string number
            while (j < line.length() && std::isdigit(line[j])) {
                numStr += line[j];
                j++;
            }
            //convert string number and add to dictionary
            if (!numStr.empty()) {
                restoredDictionary[ch] = std::stoi(numStr);
                totalChars += restoredDictionary[ch];
                i = j;
            }
        }
    }

    //Clear and Rebuild Tree
    if (root != nullptr) {
        clearTree(root);
        root = nullptr;
    }
    buildTree(restoredDictionary);

    //Binary Decoding
    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile.is_open()) return;

    Node* current = root;
    long long charsDecoded = 0;
    unsigned char byte;

    // Read one Byte from file 
    while (charsDecoded < totalChars && inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        //Procces read Byte:
        for (int i = 7; i >= 0 && charsDecoded < totalChars; --i) {
            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left;

            if (current->left == nullptr && current->right == nullptr) {
                char ch = current->ch[0]; 
                outFile.put(ch);
                charsDecoded++;
                current = root;
            }
        }
    }

    outFile.close();
    inFile.close();
    std::cout << "Dekompresja zakonczona sukcesem!" << std::endl;
}