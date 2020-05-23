#include <iostream>
#include <algorithm>

typedef int Rank;
#define DEFAULT 5

//using namespace std;

template <typename T>
class Vector {
private:
    T *_elem;
    Rank _size;
    int _capacity;

public:
    Vector(int c = DEFAULT);
    Vector(Vector<T> const & V, Rank lo, Rank hi);
    Vector(Vector<T> const & V);
    Vector(T const *A, Rank lo, Rank hi);
    ~Vector();
    
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
    int size() { return _size; }

    T & operator[] (Rank r) const;
    Rank insert(Rank r, T const & e);
    int remove(Rank lo, Rank hi);
    T remove(Rank r);
    Rank find(T const & e, Rank lo, Rank hi);
    void traverse(void (*visit) (T &));

    int disordered();
    int uniquify();
    Rank binSearch(T const & e, Rank lo, Rank hi);

    void bubbleSort1(Rank lo, Rank hi);
    bool sort1(Rank lo, Rank hi);
    void bubbleSort2(Rank lo, Rank hi);
    Rank sort2(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void Merge(Rank lo, Rank mi, Rank hi);
    void quickSort(Rank lo, Rank hi);
    Rank Partition(Rank lo, Rank hi);
};

template<typename T>
Vector<T>::Vector(int c) {
    _elem = new T[_capacity = c];
    _size = 0;
}

template<typename T>
Vector<T>::Vector(Vector<T> const & V, Rank lo, Rank hi) {
    copyFrom(V._elem, lo, hi);
}

template <typename T>
Vector<T>::Vector(Vector<T> const & V) {
    copyFrom(V._elem, 0, V._size);
}

template <typename T>
Vector<T>::Vector(T const *A, Rank lo, Rank hi ) {
    copyFrom(A, lo, hi);
}

template<typename T> Vector<T>::~Vector() {
    delete []_elem;
    _size = 0;
}

template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand() {
    _capacity = max(DEFAULT, _capacity);

    T *oldelem = _elem;
    _elem = new T[_capacity <<= 1];

    for(int i = 0; i < _size; i++) 
        _elem[i] = oldelem[i];

    delete []oldelem;
}

template <typename T>
T & Vector<T>::operator[] (Rank r) const {
    return _elem[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const & e) {
    expand();
    for(int i = _size; i > r; i--)
        _elem[i] = _elem[i -1];
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if(lo == hi) return 0;
    while(hi < _size) 
        _elem[lo++] = _elem[hi++];

    _size = lo;

    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::find(T const & e, Rank lo, Rank hi) {
    while(_elem[hi] != e && lo <= hi--)
        ;

    return hi;
}

template <typename T>
void Vector<T>::traverse(void (*visit) (T &)) {
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() {
    int n = 0;
    for(int i = 1; i < _size; i++)
        n += (_elem[i - 1] > _elem[i]);
    
    return n;
}

template <typename T>
int Vector<T>::uniquify() {
    int i, j;
    for(i = 0, j = 1; j < _size; j++)
        if(_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    
    return j - i;
}

template <typename T>
Rank Vector<T>::binSearch(T const & e, Rank lo, Rank hi) {
    
    while(lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if(e < _elem[mi]) hi = mi;
        else if(_elem[mi] < e) lo = mi + 1;
        else return mi;
    }

    return -1;
}

template <typename T>
void Vector<T>::bubbleSort1(Rank lo, Rank hi) {
    while(!sort1(lo, hi--));
}

template <typename T>
bool Vector<T>::sort1(Rank lo, Rank hi) {
    bool sorted = true;

    while(++lo < hi)
        if(_elem[lo - 1] > _elem[lo]) {
            swap(_elem[lo - 1], _elem[lo]);
            sorted = false;
        }

    return sorted;
}

template <typename T>
void Vector<T>::bubbleSort2(Rank lo, Rank hi) {
    while(lo < (hi = sort2(lo, hi)));
}

template <typename T>
Rank Vector<T>::sort2(Rank lo, Rank hi) {
    Rank last = lo;
    while(++lo < hi)
        if(_elem[lo - 1] >  _elem[lo]) {
            swap(_elem[lo - 1], _elem[lo]);
            last = lo;
        }

    return last;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if(hi - lo < 2) return;
    
    Rank mi = (lo + hi) >> 1;

    mergeSort(lo, mi);
    mergeSort(mi, hi);
    Merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::Merge(Rank lo, Rank mi, Rank hi) {
    T *B = _elem + lo;
    int la = mi - lo;
    T *A = new T[la];

    for(int i = 0; i < la; i++)
        A[i] = B[i];

    int lc = hi - mi;
    T *C = _elem + mi;

    for(int a = 0, b = 0, c = 0; a < la || c < lc; ) {
        if(a < la && (A[a] <= C[c] || lc <= c)) B[b++] = A[a++];
        if(c < lc && (C[c] < A[a] || la <= a)) B[b++] = C[c++];
    }

    delete []A;
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    if((hi - lo) < 2) return;

    Rank mi = Partition(lo, hi);
    quickSort(lo, mi);
    quickSort(mi + 1, hi);
}

template <typename T>
Rank Vector<T>::Partition(Rank lo, Rank hi) {
    swap(_elem[lo], _elem[lo + rand()%(hi - lo)]);

    T pivot = _elem[lo];
    while(lo < hi) {
        while(lo < hi && (pivot <= _elem[hi])) hi--;
        _elem[lo] = _elem[hi];
        while(lo < hi && (_elem[lo] <= pivot)) lo++;
        _elem[hi] = _elem[lo];
    }
    _elem[lo] = pivot;
    return lo;
}
