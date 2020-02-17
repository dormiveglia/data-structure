#ifndef QUADLIST_H_
#define QUADLIST_H_

#include "QuadlistNode.h"

template <class T>
class Quadlist {
public:
    using QlistNodeP = QuadlistNode<T>*;

    Quadlist() { init(); }
    ~Quadlist() { clear(); delete header; delete tailer; }

    // read-only interfaces
    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    QlistNodeP first() const { return header->succ; }
    QlistNodeP last()  const { return tailer->pred; }
    bool valid(QlistNodeP p) const { 
        return p && (tailer != p) && (header != p); 
    }

    // writable interfaces
    T remove(QlistNodeP p);
    QlistNodeP insertAfterAbove(
            const T &e, QlistNodeP p, QlistNodeP b = nullptr) {
        ++_size;
        return p->insertAsSuccAbove(e, b);
    }

    // traverse
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST &);

private:
    int _size;
    QlistNodeP header, tailer;

protected:
    void init();
    int clear();
};

template <class T>
void Quadlist<T>::init() {
    header = new QuadlistNode<T>();
    tailer = new QuadlistNode<T>();

    header->succ = tailer;
    tailer->pred = header;

    header->pred = header->above = header->below =
    tailer->succ = tailer->above = tailer->below = nullptr;

    _size = 0;
}

template <class T>
int Quadlist<T>::clear() {
    int oldS = _size;
    while (0 < _size) remove(header->succ);
    return oldS;
}

template <class T>
T Quadlist<T>::remove(QlistNodeP p) {
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    --_size;
    T e = p->entry;
    delete p;

    return e;
}

#endif
