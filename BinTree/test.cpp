#include <iostream>
#include <vector>

#include "buildtree.hpp"

using namespace std;

template <typename T>
void print (T &);

int main() {
    char a[] = {'a', 'b', 'd', 'e', 'f', 'c', 'g', 'h', 'i'};
    char b[] = {'d', 'e', 'b', 'f', 'a', 'g', 'c', 'i', 'h'};

    vector<char> pre(a, a + 9);
    vector<char> In(b, b + 9);
    BinNodePosi(char) root = BuildTree1(pre, In);

    BinTree<char> t(root);
    t.travIn2(print);

    return 0;
}

template <typename T>
void print(T & e) {
    cout << e << "|";
}


