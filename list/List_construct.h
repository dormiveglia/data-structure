#ifndef List_CONSTRUCT_H_
#define List_CONSTRUCT_H_

#include "List.h"

template <class T>
List<T>::List() { init(); }

template <class T>
List<T>::List(const List &B) {
    copyNodes(B.first(), B.size());     
}

template <class T>
List<T>::List(NodeP p, int n) {
    copyNodes(p, n);
}

template <class T>
List<T>::List(const List &B, Rank off, int n) {
    copyNodes(B[off], n);
}

template <class T>
void List<T>::init() {
    head = new Node<T>();
    tail = new Node<T>();
    head->_next = tail;
    tail->_prev = head;
    N = 0;
}

template <class T>
void List<T>::copyNodes(NodeP p, int n) {
    init();
    while (n--) {
        insertAsLast(p->data());
        p = p->next();
    }
}


#endif
