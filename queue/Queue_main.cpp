#include <iostream>
#include "Queue.h"
using namespace std;


int main() {
    Queue<float> q;
    q.enqueue(2.3);
    q.enqueue(3.1415);
    q.enqueue(0.618);
    while (!q.empty()) {
        cout << q.front() << ' ';
        cout << q.dequeue() << endl;
    }
}
