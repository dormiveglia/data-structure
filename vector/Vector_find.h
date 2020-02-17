#ifndef VECTOR_FIND_H_
#define VECTOR_FIND_H_

#include "Vector.h"

template <typename T>
typename Vector<T>::Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while (lo < hi-- && e != _elem[hi]) {}
    return hi;
}

template <typename T>
inline typename Vector<T>::Rank Vector<T>::find(const T &e) const { 
    return find(e, 0, size()); 
}


#endif
