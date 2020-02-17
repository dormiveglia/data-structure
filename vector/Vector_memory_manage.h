#ifndef VECTOR_MEMORY_MANAGE_H_
#define VECTOR_MEMORY_MANAGE_H_

#include "Vector.h"

template <typename T>
void Vector<T>::expand() {
    if (size() < _capacity)
        return;
    // alloc a larger block of memory
    Size newCapacity 
        = (_capacity < DEFATLT_CAPACITY)? DEFATLT_CAPACITY : _capacity;
    newCapacity <<= 1;
    T *newElem = new T[newCapacity];

    // copy the elements
    for (Rank i = 0; i < size(); ++i)
        newElem[i] = _elem[i];
    
    // update the status of object
    delete [] _elem;
    _elem = newElem;
    _capacity = newCapacity;
}

template <class T>
void Vector<T>::shrink() {
    if (size() << 2 < _capacity || _capacity < DEFATLT_CAPACITY)
        return;

    Size newCapacity = _capacity >> 1;
    T *newElem = new T[newCapacity];
    for (Rank i = 0; i < size(); ++i)
        newElem[i] = _elem[i];

    delete [] _elem;
    _elem = newElem;
    _capacity = newCapacity;
}

#endif
