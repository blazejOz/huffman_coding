all:
	g++ -std=c++17 huffman.cpp src/HuffmanCoding.cpp -o huffman.out

run: all
	./main.out