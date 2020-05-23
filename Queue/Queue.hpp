#include "List.h"

template<typename T>
class Queue: public List<T> {
    void enqueue(T const & e) {this->insertAslast(e);}
    T dequeue() { return this->remove(this->first()); }
    T & front() { return this->first->data; }
};
