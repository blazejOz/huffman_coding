all:
	g++ -std=c++17 Huffman.cpp src/HuffmanCoding.cpp -o Huffman.out

run: all
	./main.out