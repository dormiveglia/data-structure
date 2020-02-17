#ifndef BINNODE_REMOVE_H_
#define BINNODE_REMOVE_H_

#include "BinTree.h"

template <class T>
int BinTree<T>::remove(BinNodeP x) {
    if (x->parent) {
        if (x->parent->lc == x)
            x->parent->lc = nullptr;
        else
            x->parent->rc = nullptr;
        updateHeightAbove(x->parent);
    }
    
    int n = removeAt(x);
    _size -= n;

    return n;
}

template <class T>
int BinTree<T>::removeAt(BinNodeP x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    delete x;

    return n;
}

template <class T>
BinTree<T>* BinTree<T>::secede(BinNodeP x) {
    if (x->parent) {
        ((x->parent->lc == x)? x->parent->lc : x->parent->rc) = nullptr;
        updateHeightAbove(x->parent);
        x->parent = nullptr;
    }
    BinTree *newT = new BinTree();
    newT->_root = x;
    newT->_size = x->size();
    _size -= newT->_size;
    return newT;
}

#endif
