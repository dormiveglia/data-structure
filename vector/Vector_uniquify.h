#ifndef VECTOR_UNIQUIFY_H_
#define VECTOR_UNIQUIFY_H_

#include "Vector.h"

template <typename T>
int Vector<T>::deduplicate() {
    Rank cur = 1, nxt = 1;
    while (nxt < size()) {
        if (find(0, cur) < 0) {
            _elem[cur++] = _elem[nxt];
        }
        ++nxt;
    }
    Size ret = size() - cur;
    _size = cur;
    return ret;
}

template <typename T>
int Vector<T>::uniquify() {
    Rank tail = 0, nxt = 1;
    while (nxt < size()) {
        if (_elem[nxt] != _elem[tail]) {
            _elem[++tail] = _elem[nxt];
        }
        ++nxt;
    }
    _size = ++tail;
    shrink();
    return nxt - _size;
}


#endif
