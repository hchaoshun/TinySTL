#include <stack>
#include <queue>

#include "BinTree.hpp"

using namespace std;

template <typename T>
void travPre1(BinNodePosi(T) _root, void (*Visit) ( T &)) {
    if(!_root) return;
    
    Visit(_root->data);
    travPre1(_root->lchild, Visit);
    travPre1(_root->rchild, Visit);
} 

template <typename T>
void travPre2(BinNodePosi(T) _root, void (*Visit) (T &)) {
    stack<BinNodePosi(T)> S;

    while(true) {
        visitAlongLeftBranch(_root, S, Visit);
        if(S.empty())
            break;

        _root = S.top();
        S.pop();
    }

    
}

template <typename T>
void visitAlongLeftBranch(BinNodePosi(T) _root, stack<BinNodePosi(T)> &
        S, void (*Visit) (T &)) {
    while(_root) {
        Visit(_root->data);
        S.push(_root->rchild);
        _root = _root->lchild;
    }
}

template <typename T>
void travIn1(BinNodePosi(T) _root, void (*Visit) (T &)) {
    if(!_root) return;

    travIn1(_root->lchild, Visit);
    Visit(_root->data);
    travIn1(_root->rchild, Visit);
}

template <typename T>
void travIn2(BinNodePosi(T) _root, void (*Visit) (T &)) {
    stack<BinNodePosi(T)> S;

    while(true) {
        goAlongLeftBranch(_root, S);
        if(S.empty())
            break;

        _root = S.top();
        Visit(_root->data);
        S.pop();

        _root = _root->rchild;
    }
}

template <typename T>
void goAlongLeftBranch(BinNodePosi(T) _root, stack<BinNodePosi(T)> & S) {
    while(_root) {
        S.push(_root);
        _root = _root->lchild;
    }
}

template <typename T>
void travPost1(BinNodePosi(T) _root, void (*Visit) (T &)) {
    if(!_root) return;

    travPost1(_root->lchild, Visit);
    travPost1(_root->rchild, Visit);
    Visit(_root->data);
}

template <typename T>
void travPost2(BinNodePosi(T) _root, void (*Visit) (T &)) {
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
void H(stack<BinNodePosi(T)> & S) {
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
void travLevel(BinNodePosi(T) _root, void (*Visit) (T &)) {
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



