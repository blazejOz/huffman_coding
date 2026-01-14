#include <iostream>
#include <fstream>
#include <string>
#include "src/HuffmanCoding.hpp"

// Funkcja pomocnicza do tworzenia pliku testowego
void createDummyFile(const std::string& filename) {
    std::ofstream file(filename);
    file << "ala ma kota, a kot ma ale. Huffman coding test 123!";
    file.close();
}

int main() {
    HuffmanCoding huffman;
    
    std::string originalFile = "input.txt";
    std::string compressedFile = "compressed.huff";
    std::string decompressedFile = "output.txt";

    // 1. Przygotowanie danych testowych
    std::cout << "--- Step 1: Creating test file ---" << std::endl;
    createDummyFile(originalFile);
    std::cout << "File '" << originalFile << "' created." << std::endl;

    // 2. Kompresja
    std::cout << "\n--- Step 2: Compressing ---" << std::endl;
    huffman.compress(originalFile, compressedFile);

    // 3. Dekompresja
    // Tworzymy nowy obiekt, żeby mieć pewność, że dekompresja 
    // odbuduje drzewo z pliku, a nie korzysta z tego w pamięci
    HuffmanCoding huffmanDecoder; 
    std::cout << "\n--- Step 3: Decompressing ---" << std::endl;
    huffmanDecoder.decompress(compressedFile, decompressedFile);

    // 4. Weryfikacja
    std::cout << "\n--- Step 4: Verification ---" << std::endl;
    std::ifstream f1(originalFile), f2(decompressedFile);
    std::string s1((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::string s2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());

    if (s1 == s2) {
        std::cout << "SUCCESS: Files are identical!" << std::endl;
        std::cout << "Content: " << s2 << std::endl;
    } else {
        std::cout << "ERROR: Files differ!" << std::endl;
    }

    return 0;
}