#include <stack>
#include <queue>

#include "BinNode.hpp"

using namespace std;

template <typename T>
class BinTree {
protected:
    int _size;
    BinNodePosi(T) _root;

public:
    BinTree(): _size(0), _root(NULL) {}
    BinTree(BinNodePosi(T) r = NULL);

    int size() const {return _size;}
    bool Empty() const {return !_root;}
    BinNodePosi(T) root() const {return _root;}

    BinNodePosi(T) insertLc(BinNodePosi(T) x, T const & e);
    BinNodePosi(T) insertRc(BinNodePosi(T) x, T const & e);

    void travPre1(BinNodePosi(T) x, void (*Visit) ( T &)); 
    void travPre2(void (*Visit) (T &));
    void visitAlongLeftBranch(stack<BinNodePosi(T)> & S, void (*Visit) (T &));

    void travIn1(BinNodePosi(T) x, void (*Visit) (T &));
    void travIn2(void (*Visit) (T &));
    void goAlongLeftBranch(stack<BinNodePosi(T)> & S);

    void travPost1(BinNodePosi(T) x, void (*Visit) (T &));
    void travPost2(void (*Visit) (T &));
    void H(stack<BinNodePosi(T)> & S);

    void travLevel(void (*Visit) (T &));

};

template <typename T>
BinTree<T>::BinTree(BinNodePosi(T) r) {
    _root = r;
    if(!_root)
        _size = 0;
    else
        _size = r->size();
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertLc(BinNodePosi(T) x, T const & e) {
    _size++;
    return x->insertAsLc(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertRc(BinNodePosi(T) x, T const & e) {
    _size++;
    return x->insertAsRc(e);
}


template <typename T>
void BinTree<T>::travPre1(BinNodePosi(T) x, void (*Visit) ( T &)) {
    if(!x) return;
    
    Visit(x->data);
    travPre1(x->lchild, Visit);
    travPre1(x->rchild, Visit);
} 

template <typename T>
void BinTree<T>::travPre2(void (*Visit) (T &)) {
    stack<BinNodePosi(T)> S;

    while(true) {
        visitAlongLeftBranch(S, Visit);
        if(S.empty())
            break;

        _root = S.top();
        S.pop();
    }
}

template <typename T>
void BinTree<T>::visitAlongLeftBranch(stack<BinNodePosi(T)> & S, void (*Visit) (T &)) {
    while(_root) {
        Visit(_root->data);
        S.push(_root->rchild);
        _root = _root->lchild;
    }
}

template <typename T>
void BinTree<T>::travIn1(BinNodePosi(T) x, void (*Visit) (T &)) {
    if(!x) return;

    travIn1(x->lchild, Visit);
    Visit(x->data);
    travIn1(x->rchild, Visit);
}

template <typename T>
void BinTree<T>::travIn2(void (*Visit) (T &)) {
    stack<BinNodePosi(T)> S;

    while(true) {
        goAlongLeftBranch(S);
        if(S.empty())
            break;

        _root = S.top();
        Visit(_root->data);
        S.pop();

        _root = _root->rchild;
    }
}

template <typename T>
void BinTree<T>::goAlongLeftBranch(stack<BinNodePosi(T)> & S) {
    while(_root) {
        S.push(_root);
        _root = _root->lchild;
    }
}

template <typename T>
void BinTree<T>::travPost1(BinNodePosi(T) x, void (*Visit) (T &)) {
    if(!x) return;

    travPost1(x->lchild, Visit);
    travPost1(x->rchild, Visit);
    Visit(x->data);
}

template <typename T>
void BinTree<T>::travPost2(void (*Visit) (T &)) {
    stack<BinNodePosi(T)> S;
    S.push(_root);

    while(!S.empty()) {
        if(S.top() != _root->parent)
            H(S);
        _root = S.top();
        Visit(_root->data);
        S.pop();
    }
}

template <typename T>
void BinTree<T>::H(stack<BinNodePosi(T)> & S) {
    BinNodePosi(T) _root;
    while((_root = S.top()))
        if(_root->lchild) {
            if(_root->rchild)
                S.push(_root->rchild);
            S.push(_root->lchild);
        }
        else
            S.push(_root->rchild);

    S.pop();
}

template <typename T>
void BinTree<T>::travLevel(void (*Visit) (T &)) {
    queue<BinNodePosi(T)> Q;
    Q.push(_root);

    while(!Q.empty()) {
        _root = Q.front();
        Visit(_root->data);
        Q.pop();

        if(_root->lchild) Q.push(_root->lchild);
        if(_root->rchild) Q.push(_root->rchild);
    }
}



