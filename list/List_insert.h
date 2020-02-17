#ifndef LIST_INSERT_H_
#define LIST_INSERT_H_

#include "List.h"

template <class T>
typename List<T>::NodeP List<T>::insertAsFirst(const T &e) {
    ++N;
    return head->insertAsNext(e);
}

template <class T>
typename List<T>::NodeP List<T>::insertAsLast(const T &e) {
    ++N;
    return tail->insertAsPrev(e);
}

template <class T>
typename List<T>::NodeP List<T>::insertA(const T &e, NodeP p) {
    ++N;
    return p->insertAsNext(e);
}

template <class T>
typename List<T>::NodeP List<T>::insertB(const T &e, NodeP p) {
    ++N;
    return p->insertAsPrev(e);
}

#endif
