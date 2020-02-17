#ifndef LIST_UNIQUIFY_H_
#define LIST_UNIQUIFY_H_

#include "List.h"

template <class T>
int List<T>::deduplicate() {
    NodeP p = head;
    Rank  r = 0;
    Size  n = N;
    while ((p = p->next()) != tail) {
        NodeP q = find(p->data(), r, p);
        if (q)
            remove(q);
        else
            ++r;
    }
    return n - N;
}

template <class T>
int List<T>::uniquify() {
    if (size() < 2) return 0;
    Size n = N;
    NodeP p = head->next(), q = p->next();
    while (q != tail) {
        if (p->data() == q->data())
            remove(q);
        else
            p = q;
        q = p->next();
    }

    return n - N;
}

#endif
