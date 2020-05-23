#include "Vector.hpp"
#include <cstdlib>

using namespace std;

void print(int & e);

int main() {
    int a[10];
    for(int i =0; i < 10; i++)
        a[i] = rand()%10;
    Vector<int> v(a, 0, 10);
    v.traverse(print);
    cout << endl;
    
    v.mergeSort(0, 10);
    v.traverse(print);
    cout << endl;

    return 0;
}

void print(int & e) {
    cout << e << ",";
}
