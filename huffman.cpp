#include <iostream>
#include <string>
#include "src/HuffmanCoding.hpp"

void printUsage(const char* progName) {
    std::cout << "Uzycie: " << progName << " [OPCJA] [PLIK_WEJSCIOWY] [OPCJONALNIE: PLIK_WYJSCIOWY]" << std::endl;
    std::cout << "Opcje:" << std::endl;
    std::cout << "  -c    Kompresja (domyslny output: plik.huff)" << std::endl;
    std::cout << "  -d    Dekompresja (domyslny output: plik.txt)" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    std::string option = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile;

    if (argc >= 4) {
        outputFile = argv[3];
    } else {
        if (option == "-c") {
            outputFile = "compressed.huff";
        } else if (option == "-d") {
            outputFile = "decompressed.txt";
        }
    }

    HuffmanCoding huffman;

    if (option == "-c") {
        std::cout << "[KOMPRESJA] Cel: " << outputFile << std::endl;
        huffman.compress(inputFile, outputFile);
    } 
    else if (option == "-d") {
        std::cout << "[DEKOMPRESJA] Cel: " << outputFile << std::endl;
        huffman.decompress(inputFile, outputFile);
    } 
    else {
        std::cerr << "Blad: Nieznana opcja " << option << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    std::cout << "Gotowe!" << std::endl;
    return 0;
}