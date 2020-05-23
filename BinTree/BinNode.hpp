#include <iostream>

#define BinNodePosi(T) BinNode<T>*

template <typename T>
struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lchild;
    BinNodePosi(T) rchild;

    BinNode(): parent(NULL), lchild(NULL), rchild(NULL) {};
    BinNode(T d, BinNodePosi(T) p = NULL, BinNodePosi(T) l = NULL, BinNodePosi(T) r = NULL):
        data(d), parent(p), lchild(l), rchild(r) {};
    int size();
    BinNodePosi(T) succ();
    BinNodePosi(T) insertAsLc(T const &);
    BinNodePosi(T) insertAsRc(T const &);

};

template <typename T>
int BinNode<T>::size() {
    int a = 1;

    if(lchild) a+=lchild->size();
    if(rchild) a+=rchild->size();

    return a;
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this;
    if(this->rchild) {
        s = this->rchild;
        while(s->lchild)
            s = s->lchild;
    }
    else {
        while(s->parent) {
            if(s->parent->rchild != s)
                break;
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLc(T const & e) {
    return this->lchild = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(T const & e) {
    return this->rchild = new BinNode(e, this);
}


