#ifndef VECTOR_INSERT_H_
#define VECTOR_INSERT_H_

#include "Vector.h"

template <typename T>
typename Vector<T>::Rank Vector<T>::insert(Rank r, const T &e) {
    expand();
    for (Rank i = size(); i > r; --i)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    ++_size;

    return r;
}

template <typename T>
inline typename Vector<T>::Rank Vector<T>::insert(const T &e) {
    return insert(size(), e);
}


#endif
