#include "ListNode.h"

template <typename T>
class List {
private:
    Posi(T) header;
    Posi(T) tailer;
    Rank _size;
public:
    List() { init(); }
    List(Posi(T) p, int n);
    ~List();

    void init();
    T operator[] (Rank r) const ;
    Posi(T) first();
    Posi(T) last();
    void copyNodes(Posi(T) p, int n);

    Posi(T) insertBefore(Posi(T) p, T const & e);
    Posi(T) insertAfter(Posi(T) p, T const & e);
    Posi(T) insertAsfirst(T const & e);
    Posi(T) insertAslast(T const & e);

    T remove(Posi(T) p);
    Posi(T) search(T const & e, int n, Posi(T) p);

    void insertSort(Posi(T) p, int n);
    void selectSort(Posi(T) p, int n);
    Posi(T) selectMax(Posi(T) p, int n);

    void traverse(void (*visit) (T &));
};

template <typename T>
List<T>::List(Posi(T) p, int n) {
    copyNodes(p, n);
}

template <typename T>
List<T>::~List<T>() {
    while(0 < _size)
        remove(header->succ);
    delete header;
    delete tailer;
}

template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    tailer = new ListNode<T>;

    header->succ = tailer; header->pred = NULL;
    tailer->pred = header; tailer->succ = NULL;

    _size =0;
}

template <typename T>
T List<T>::operator[] (Rank r) const {
    Posi(T) p = first();
    while(0 < r--)
        p = p->succ;

    return p->data;
}

template <typename T>
Posi(T) List<T>::first() {
    return header->succ;
}

template <typename T>
Posi(T) List<T>::last() {
    return tailer->pred;
}

template <typename T>
void List<T>::copyNodes(Posi(T) p, int n) {
    init();
    while(0 < n--) {
        insertAslast(p->data);
        p = p->succ;
    }

}

template <typename T>
Posi(T) List<T>::insertAsfirst(T const & e) {
    _size++;
    return header->insertAssucc(e);
}

template <typename T>
Posi(T) List<T>::insertAslast(T const & e) {
    _size++;
    return tailer->insertAspred(e);
}

template <typename T>
Posi(T) List<T>::insertBefore(Posi(T) p, T const & e) {
    _size++;
    return p->insertAspred(e);
}

template <typename T>
Posi(T) List<T>::insertAfter(Posi(T) p, T const & e) {
    _size++;
    return p->insertAssucc(e);
}

template <typename T>
T List<T>::remove(Posi(T) p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    _size--;
    
    delete p;
    return e;
}

template <typename T>
Posi(T) List<T>::search(T const & e, int n, Posi(T) p) {
    while(0 <= n--)
        if((p = p->pred)->data <= e)
            break;

    return p;
}

template <typename T>
void List<T>::insertSort(Posi(T) p, int n) {
    Rank r;
    for(r = 0; r < n; r++) {
        insertAfter(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectSort(Posi(T) p, int n) {
    Posi(T) head = p->pred;
    Posi(T) tail = p;
    for(int i = 0; i < n; i++)
        tail = tail->succ;

    while(1 < n) {
        insertBefore(tail, remove( selectMax( head->succ, n ) ) );
        tail = tail->pred;
        n--;
    }
}

template <typename T>
Posi(T) List<T>::selectMax(Posi(T) p, int n) {
    Posi(T) Max = p;
    for(Posi(T) cur = p; 1 < n; n--)
        if(Max->data < ((cur = cur->succ)->data))
            Max = cur;

    return Max;
}

template <typename T>
void List<T>::traverse(void (*visit) (T &)) {
    Posi(T) p = header;
    while(( p = p->succ ) != tailer)
        visit(p->data);
}

