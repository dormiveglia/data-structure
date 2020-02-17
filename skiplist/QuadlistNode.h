#ifndef QUAD_LIST_NODE_H_
#define QUAD_LIST_NODE_H_

#include "../entry/Entry.h"

template <class T> struct QuadlistNode {
    using QuadlistNodeP = QuadlistNode*;

    T entry;
    QuadlistNodeP pred, succ, above, below; 

    QuadlistNode(const T &e = T(), 
            QuadlistNodeP p = nullptr, QuadlistNodeP s = nullptr, 
            QuadlistNodeP a = nullptr, QuadlistNodeP b = nullptr) :
        entry(e), pred(p), succ(s), above(a), below(b) { }

    QuadlistNodeP insertAsSuccAbove(const T &e, QuadlistNodeP b = nullptr) {
        auto x = new QuadlistNode<T>(e, this, succ, nullptr, b);
        succ->pred = x;
        this->succ = x;

        if (b) 
            b->above = x;

        return x;
    }
};

#endif
