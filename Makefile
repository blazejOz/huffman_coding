all:
	g++ -std=c++17 huffman.cpp src/MyPriorityQueue.cpp src/HuffmanCoding.cpp -o huffman.out

Sandbox:
	g++ -std=c++17 PriorityQueueSandbox.cpp src/MyPriorityQueue.cpp -o sandbox.out
