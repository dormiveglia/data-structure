#ifndef VECTOR_REMOVE_H_
#define VECTOR_REMOVE_H_

#include "Vector.h"

template <typename T>
typename Vector<T>::Size Vector<T>::remove(Rank lo, Rank hi) {
    if (hi <= lo) return 0;
    while (hi < _size) _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}


#endif
