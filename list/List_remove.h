#ifndef LIST_REMOVE_H_
#define LIST_REMOVE_H_

#include "List.h"

template <class T>
T List<T>::remove(NodeP p) {
    T e = p->data();
    p->prev()->_next = p->next();
    p->next()->_prev = p->prev();
    delete p;
    --N;
    return e;
}

#endif
