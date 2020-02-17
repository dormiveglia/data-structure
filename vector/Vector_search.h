#ifndef VECTOR_SEARCH_H_
#define VECTOR_SEARCH_H_

#include "Vector.h"

template <typename T>
typename Vector<T>::Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return binSearch3(_elem, e, lo, hi);
}

template <typename T>
inline typename Vector<T>::Rank Vector<T>::search(const T &e) const {
    return size() <= 0? -1 : search(e, 0, size());
}

template <typename T>
typename Vector<T>::Rank Vector<T>::binSearch(
        const T *A, const T &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = lo + ((hi - lo) >> 1);
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }
    return -1;
}

template <typename T>
typename Vector<T>::Rank Vector<T>::binSearch2(
        const T *A, const T &e, Rank lo, Rank hi) {
    while (lo + 1 < hi) {
        Rank mi = lo + ((hi - lo) >> 1);
        (e < A[mi])? hi = mi : lo = mi;
    }
    return (e == A[lo])? lo : -1;
}

template <typename T>
typename Vector<T>::Rank Vector<T>::binSearch3(
        const T *A, const T &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = lo + ((hi - lo) >> 1);
        (e < A[mi])? hi = mi : lo = mi + 1;
    }
    return --lo;
}

template <typename T>
typename Vector<T>::Rank Vector<T>::fibSearch(
        const T *A, const T &e, Rank lo, Rank hi) {
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }

    return -1;
}



#endif
