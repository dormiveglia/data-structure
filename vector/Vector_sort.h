#ifndef VECTOR_SORT_H_
#define VECTOR_SORT_H_

#include "Vector.h"

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    bubbleSort(lo, hi);
}

template <typename T>
inline void Vector<T>::sort() { sort(0, size()); }

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--)) {}
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    for (Rank i = lo + 1; i < hi; ++i) {
        if (_elem[i] < _elem[i - 1]) {
            std::swap(_elem[i], _elem[i - 1]);
            sorted = false;
        }
    }
    return sorted;
}


#endif
