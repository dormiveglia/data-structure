#ifndef VECTOR_SHUFFLE_H_
#define VECTOR_SHUFFLE_H_

#include "Vector.h"

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    // Fisher-Yates Shuffle
    T *p = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i)
        std::swap(p[i - 1], p[rand() % i]);
}

template <typename T>
inline void Vector<T>::unsort() { unsort(0, size()); }


#endif
