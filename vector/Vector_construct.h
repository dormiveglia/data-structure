#ifndef VECTOR_CONSTRUCT_H_
#define VECTOR_CONSTRUCT_H_

/**
 *
 * Constructors and copy-control member functions of Vector
 *
 */

#include "Vector.h"

template <typename T>
Vector<T>::Vector(Size c, Size s, T v)
        : _capacity(maxSize(c, DEFATLT_CAPACITY)), 
        _size(s), _elem(new T[_capacity]) {
    for (Rank i = 0; i < _size; ++i)
        _elem[i] = v;
}

template <typename T>
Vector<T>::Vector(const T *A, Size n) : Vector(A, 0, n) {}


template <typename T>
Vector<T>::Vector(const T *A, Rank lo, Rank hi) 
    : _capacity((hi - lo) * 2), _size(hi - lo), _elem(new T[_capacity]) { 
        copyFrom(A, lo, hi); 
}

template <typename T>
Vector<T>::Vector(const Vector &v) 
    : Vector(v._elem, 0, v.size()) {}

template <typename T>
Vector<T>::Vector(const Vector &v, Rank lo, Rank hi) 
    : Vector(v._elem, lo, hi) {}

template <typename T>
Vector<T>::Vector(Vector &&v) : _capacity(0), _size(0), _elem(nullptr) {
    _elem = v._elem;
    _capacity = v._capacity;
    _size = v._size;
    v._elem = nullptr;
    v._capacity = 0;
    v._size = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &v) {
    // prevent self-assignment
    if (this == &v) return *this;
    T* newElem = new T[v._capacity];
    if (_elem) delete [] _elem;
    _elem = newElem;
    _capacity = v._capacity;
    _size = v._size;
    copyFrom(v._elem, 0, v.size());

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector &&v) {
    if (this == &v) return *this;
    if (_elem) delete [] _elem;
    _elem = v._elem;
    _capacity = v._capacity;
    _size = v.size();

    v._elem = nullptr;
    v._capacity = v._size = 0;
}

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    for (Rank s = 0, e = 0 + hi - lo; s < e; ++s, ++lo)
        _elem[s] = A[lo];
}

template <typename T>
Vector<T>::~Vector() { 
    if (_elem) delete [] _elem; 
    _elem = nullptr;
}

#endif
