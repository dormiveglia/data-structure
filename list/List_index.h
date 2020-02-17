#ifndef LIST_INDEX_H_
#define LIST_INDEX_H_

#include "List.h"

template <class T>
typename List<T>::NodeP List<T>::node(Rank r) const {
    if (r < (N >> 1)) {
        NodeP p = head->next();
        while (r--) {
            p = p->next();
        }
        return p;
    } else {
        NodeP p = tail->prev();
        while (++r < N) {
            p = p->prev();
        }
        return p;
    }
}

template <class T>
T& List<T>::operator[](Rank r) const {
    return node(r)->data();
}

template <class T>
typename List<T>::NodeP List<T>::first() const {
    return head->next();
}

template <class T>
typename List<T>::NodeP List<T>::last() const {
    return tail->prev();
}

#endif
