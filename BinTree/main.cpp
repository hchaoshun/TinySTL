#include <iostream>

#include "BST.hpp"

using namespace std;

template <typename T>
void print (T &);

int main() {
    BinNodePosi(int) demo = new BinNode<int>(4);
    BinNodePosi(int) p = demo;
    p->insertAsRc(5);
    p = p->insertAsLc(2);
    p->insertAsLc(1);
    p->insertAsRc(3);

    BST<int> t(demo);
    t.travIn2(print);
    cout << endl;
    
    BinNodePosi(int) x = t.search(2);
    cout << x->data << endl;
    
    t.insert(6);
    t.travIn2(print);
    cout << endl;

    // t.remove('b');
    // t.travPre2(print);
    // cout << endl;
    //
    return 0;

}

template <typename T>
void print(T & e) {
    cout << e << "|";
}



