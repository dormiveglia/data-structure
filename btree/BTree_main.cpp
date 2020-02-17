#include <iostream>
#include "BTree.h"

using namespace std;

int main() {
    BTree<float> bt;
    bt.insert(3.14);
    bt.insert(23.0);
    bt.insert(233.0);
    BTree<float>::BTNodePtr p = bt.search(233.0);
    if (p) {
        std::cout << "found" << std::endl;
    }
}
