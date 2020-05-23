#include "List.h"

using namespace std;

void Icrease(int &);

int main() {
    List<int> lst;

    int e;
    cout << "input first listnode:" << endl;
    cin >> e;
    while(e != -1) {
        lst.insertAslast(e);
        cout << "input next listnode:" << endl;
        cin >> e;
    }

    lst.selectSort(lst.first(), 5);
    lst.traverse(Icrease);
    
    return 0;
    
}

void Icrease(int & e) {
    e = e + 1;
    cout << e << "|";
}
