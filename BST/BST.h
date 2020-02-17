#ifndef BST_H_
#define BST_H_

#include "../bintree/BinTree.h"

template <class T> class BST : public BinTree<T> {
public:
    using BinNodeP = BinNode<T>*;
    using BinNodeT = BinNode<T>;
protected:
};

#endif
