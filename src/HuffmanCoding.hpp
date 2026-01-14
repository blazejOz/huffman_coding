#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <string>
#include <map>
#include <vector>
#include "Node.hpp"
#include "MyPriorityQueue.hpp"

class HuffmanCoding {
private:
    //Storage for frequencies(ex. A:10, B:20 ...)
    std::map<char, int> dictionary;
    //storage for codes(ex. A:0101, B:001011 ...)
    std::map<char, std::string> huffmanCodes;

    Node* root;

    void generateCodes(Node* currentNode, std::string code);
    void clearTree(Node* currentNode);
    std::map<char, int> generateDictionary(const std::string& text);
    void buildTree(const std::map<char, int>& frequencies);

public:
    HuffmanCoding(); 
    ~HuffmanCoding(); 
    
    void compress(const std::string& inputFilePath, const std::string& outputFilePath);
    void decompress(const std::string& inputFilePath, const std::string& outputFilePath);
};


#endif