#include <iostream>
#include "List.h"

void visit(int &e) {
    std::cout << e << std::endl;
}

void testFind(List<int> &l, int v) {
    List<int>::NodeP p = l.find(v);
    if (nullptr != p)
        std::cout << p->data() << std::endl;
}

int main() {
    List<int> list;
    list.insertAsLast(233);
    list.insertAsLast(23);
    list.insertAsFirst(2343);
    list.traverse(visit);
    const List<int> &L = list;
    std::cout << L.size() << std::endl;

    testFind(list, 23);
}
