#ifndef HANOI_H_
#define HANOI_H_

#include <iostream>

void move(int n, char f, char t) { 
    std::cout << "move " << n << " from " << f << " to " << t << std::endl; 
}
void hanoi(int n, char a, char b, char c) {
    // O(2^n)
    if (n <= 0) return;
    hanoi(n - 1, a, c, b);
    move(n, a, c);
    hanoi(n - 1, b, a, c);
}


#endif
