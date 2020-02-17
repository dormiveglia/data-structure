#include <iostream>
#include "Stack.h"
using namespace std;


int main() {
    Stack<int> s;
    s.push(2).push(23).push(233).push(1024);
    auto p = [](const int &e) { cout << e << endl; };
    p(s.size());
    p(s.empty());
    while (!s.empty())
        p(s.pop());
}
