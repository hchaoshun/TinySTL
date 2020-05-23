#include <iostream>

#define Posi(T) ListNode<T>*
typedef int Rank;

template <typename T>
struct ListNode {
    T data;
    Posi(T) pred;
    Posi(T) succ;

    ListNode() {}
    ListNode(T const & d, Posi(T) p = NULL, Posi(T) s = NULL):data(d), pred(p), succ(s) {}
    Posi(T) insertAspred(T const & e);
    Posi(T) insertAssucc(T const & e);
};

template <typename T>
Posi(T) ListNode<T>::insertAspred(T const & e) {
    Posi(T) x = new ListNode(e, pred, this);
    this->pred->succ =x;
    this->pred =x;

    return x;
}

template <typename  T>
Posi(T) ListNode<T>::insertAssucc(T const & e) {
    Posi(T) x = new ListNode(e, this, succ);
    this->succ->pred = x;
    this->succ = x;

    return x;
}
