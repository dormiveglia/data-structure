#ifndef VECTOR_DISORDERED_H_
#define VECTOR_DISORDERED_H_

#include "Vector.h"

template <typename T>
int Vector<T>::disordered() const {
    int count = 0;
    for (Rank i = 1; i < size(); ++i)
        if (_elem[i] < _elem[i - 1])
            ++count;
    return count;
}


#endif
