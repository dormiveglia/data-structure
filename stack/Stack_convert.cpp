#include <iostream>
#include "Stack.h"
using namespace std;

void convert(Stack<char> &S, int n, int base) {
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
        'B', 'C', 'D', 'E', 'F'
    };

    while (n) {
        S.push(digit[n % base]);
        n /= base;
    }
}

int main() {
    Stack<char> S;
    convert(S, 255, 16);
    while (!S.empty())
        cout << S.pop();
}
