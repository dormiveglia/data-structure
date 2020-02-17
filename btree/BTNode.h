#ifndef BTNODE_H_
#define BTNODE_H_

#include "../vector/Vector.h"

template <class T> struct BTNode {
    // type of pointers to BTNodes
    using Ptr = BTNode*;

    Ptr parent;
    Vector<T> key;
    Vector<BTNode<T>*> child;

    BTNode() : parent(nullptr) { child.insert(0, nullptr);  }
    BTNode(const T &e, Ptr lc = nullptr, Ptr rc = nullptr) 
        : parent(nullptr) {
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

#endif
