#ifndef VECTOR_TRAVERSE_H_
#define VECTOR_TRAVERSE_H_

#include "Vector.h"

template <typename T>
void Vector<T>::traverse(void (*vst)(T &)) {
    for (Rank i = 0; i < size(); ++i)
        vst(_elem[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(const VST &vst) {
    for (Rank i = 0; i < size(); ++i)
        vst(_elem[i]);
}


#endif
