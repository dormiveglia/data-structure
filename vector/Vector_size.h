#ifndef VECTOR_SIZE_H_
#define VECTOR_SIZE_H_

#include "Vector.h"

template <typename T>
inline typename Vector<T>::Size Vector<T>::size() const { return _size; }

template <typename T>
inline bool Vector<T>::empty() const { return !size(); }

template <typename T>
T& Vector<T>::operator[](Rank r) const { return _elem[r]; }

#endif
