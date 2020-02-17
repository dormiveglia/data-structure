#include <iostream>
#include "GraphMatrix.h"

int main() {
    GraphMatrix<char, float> g;
    g.insert('S'); // 0
    g.insert('A'); // 1
    g.insert('B'); // 2
    g.insert('C'); // 3
    g.insert('D'); // 4
    g.insert('E'); // 5
    g.insert('F'); // 6
    g.insert('G'); // 7

    g.insert(1.0, 0, 1);
    g.insert(1.0, 0, 3);
    g.insert(1.0, 0, 4);
    g.insert(2.0, 1, 3);
    g.insert(2.0, 1, 5);
    g.insert(2.0, 3, 2);
    g.insert(2.0, 4, 2);
    g.insert(2.0, 5, 6);
    g.insert(2.0, 5, 7);
    g.insert(2.0, 7, 2);
    g.insert(2.0, 7, 6);

    g.print();
    g.bfs(0);
}
