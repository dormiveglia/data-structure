#include <iostream>
#include "BinTree.h"

using namespace std;

int main() {
    BinTree<float> T;
    auto r = T.insertAsRoot(23.0);
    T.insertAsRC(r, 24.0);
    auto l = T.insertAsLC(r, 25.0);
    T.insertAsLC(l, 26.0);
    T.insertAsRC(l, 27.0);

    T.travIn([] (const float &v) { cout << v << endl;  });
    cout << T.size() << endl;
}
