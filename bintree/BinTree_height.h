#ifndef BINNODE_HEIGHT_H_
#define BINNODE_HEIGHT_H_

#include "BinTree.h"

static inline int max(const int &a, const int &b) {
    return a < b? b : a;
}

template <class T>
int BinTree<T>::updateHeight(BinNodeP x) {
    return x->height = 1 + max(x->stature(x->lc), x->stature(x->rc));
}

template <class T>
void BinTree<T>::updateHeightAbove(BinNodeP x) {
    while (x) {
        int oldH = x->height;
        if (oldH == updateHeight(x))
            break;
        x = x->parent;
    }
}

#endif
