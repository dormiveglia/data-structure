#ifndef QUEUE_H_
#define QUEUE_H_

#include "../list/List.h"

template <class T>
class Queue : List<T> {
    public:
        using List<T>::size;
        using List<T>::empty;
        
        void enqueue(const T &e) {
            List<T>::insertAsLast(e);
        }

        T dequeue() {
            return this->remove(this->first());
        }

        T& front() const {
            return List<T>::first()->data();
        }
};

#endif
