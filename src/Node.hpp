#ifdef NODE_HPP
#define NODE_HPP

struct Node{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    //overloading '<' operator for MyPriorityQueue comparison
    bool operator<(const Node& other) const {
        return this->freq < other.freq;
    }

};

#endif