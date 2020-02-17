#ifndef BINNODE_INSERT_H_
#define BINNODE_INSERT_H_

#include "BinTree.h"

template <class T>
typename BinTree<T>::BinNodeP BinTree<T>::insertAsRoot(const T &e) {
    ++_size;
    return _root = new BinNodeT(e);
}

template <class T>
typename BinTree<T>::BinNodeP BinTree<T>::insertAsLC(BinNodeP x, const T &e) {
    ++_size;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template <class T>
typename BinTree<T>::BinNodeP BinTree<T>::insertAsRC(BinNodeP x, const T &e) {
    ++_size;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <class T>
typename BinTree<T>::BinNodeP BinTree<T>::attachAsLC(BinNodeP x, BinTree &t) {
    if (x->lc = t.root()) 
        x.lc->parent = x;
    _size += t._size;
    updateHeightAbove(x);
    t._root = nullptr;
    t._size = 0;

    return x;
}

template <class T>
typename BinTree<T>::BinNodeP BinTree<T>::attachAsRC(BinNodeP x, BinTree &t) {
    if (x->rc = t.root()) 
        x.rc->parent = x;
    _size += t._size;
    updateHeightAbove(x);
    t._root = nullptr;
    t._size = 0;

    return x;
}

#endif
