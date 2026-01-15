# Huffman Coding CLI

Prosty kompresor plików wykorzystujący algorytm Huffmana, napisany w C++.

## Szybki start

```bash
git clone https://github.com/blazejOz/huffman_coding huffman_coding
cd huffman_coding
make
huffman.out -c plik.txt           # Kompresja
huffman.out -d compressed.huff    # Dekompresja
```
## Project Structure

```
HUFFMAN_CODING/
├── src/                     # Pliki źródłowe i nagłówkowe
│   ├── HuffmanCoding.cpp    # Główna logika algorytmu
│   ├── HuffmanCoding.hpp 
│   ├── MyPriorityQueue.hpp  # Implementacja kopca (Min-Heap)
│   └── Node.hpp             # Struktura węzła drzewa
├── documentation/           # Dokumentacja techniczna
│   ├── HuffmanCoding.txt 
│   └── MyPriorityQueue.txt 
├── huffman.cpp              # Punkt wejścia (Main)
├── PriorityQueueSandbox.cpp # Sandbox dla priority queue
├── Makefile                 # Instrukcje budowania
└── README.md                # Dokumentacja projektu
```

