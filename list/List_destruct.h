#ifndef LIST_DESTRUCT_H_
#define LIST_DESTRUCT_H_

#include "List.h"

template <class T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}

template <class T>
int List<T>::clear() {
    Size ret = N;
    while (N--)
        remove(head->next());
    return ret;
}

#endif
