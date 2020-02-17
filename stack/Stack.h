#ifndef STACK_H_
#define STACK_H_

#include "../vector/Vector.h"

template <class T>
class Stack : protected Vector<T> {
  public: 
    using Vector<T>::size;
    using Vector<T>::empty;
    
    Stack& push(const T &e) {
        Vector<T>::insert(size(), e);   
        return *this;
    }

    T pop() { 
        return Vector<T>::remove(size() - 1); 
    }

    T& top() const {
        return (*this)[size() - 1];
    }
};

#endif
