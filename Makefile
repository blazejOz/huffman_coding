all:
	g++ -std=c++17 main.cpp src/HuffmanCoding.cpp -o main.out

run: all
	./main.out