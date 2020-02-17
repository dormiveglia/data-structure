#ifndef LIST_FIND_H_
#define LIST_FIND_H_

#include "List.h"

template <class T>
typename List<T>::NodeP List<T>::find(const T &e) const {
    return find(e, N, tail);
}

template <class T>
typename List<T>::NodeP List<T>::find(const T &e, int n, NodeP p) const {
    while (n-- && (p = p->prev()) != head)
        if (e == p->data())
            return p;
    return nullptr;
}

#endif
