#include <algorithm>

#include "BinTree.hpp"

template <typename T>
class BST: public BinTree<T> {
protected:
    BinNodePosi(T) _hot;

public:
    BST(BinNodePosi(T) r = NULL):BinTree<T>(r) {}

    virtual BinNodePosi(T) search(T const & e);
    virtual BinNodePosi(T) insert(T const & e);
    virtual bool remove(T const & e);
};

template <typename T>
BinNodePosi(T) BST<T>::search(T const & e) {
    return searchIn(this->_root, e, _hot = NULL);
}

template <typename T>
BinNodePosi(T) searchIn(BinNodePosi(T) & v, T const & e, BinNodePosi(T) & hot) {
    if(!v || e == v->data) return v;

    hot = v;

    return searchIn((e < v->data ? v->lchild : v->rchild), e, hot);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(T const & e) {
    BinNodePosi(T) x = search(e);

    if(!x) {
        x = new BinNode<T>(e, _hot);
        this->_size++;
    }

    return x;
}

template <typename T>
bool BST<T>::remove(T const & e) {
    BinNodePosi(T) x = search(e);
    if(!x) return false;
    removeat(x, _hot);
    this->_size--;
    
    return true;    
}

template <typename T>
void removeat(BinNodePosi(T) & x, BinNodePosi(T) & hot) {
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    
    if(!x->lchild) succ = x->rchild;
    else if(!x->rchild) succ = x->lchild;
    else {
        w = w->succ();
        swap(x->data, w->data);
        succ = w->rchild;
    }

    hot = w->parent;
    if(succ) succ->parent = hot;
    delete x;
}














