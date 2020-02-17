#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include "../list/List.h"
#include "../entry/Entry.h"
#include "../dictionary/Dictionary.h"
#include "QuadlistNode.h"
#include "Quadlist.h"

#include <cstdlib>


template <typename K, typename V>
class SkipList 
        : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*> {
public:
    using EntryT     = Entry<K, V>;
    using QNode      = QuadlistNode<Entry<K, V>>;
    using QNodeP     = QNode*;
    using QList      = Quadlist<EntryT>;
    using QListP     = QList*;
    using NodeQListP = Node<QListP>;
    using ListT      = List<QListP>;

    int size() const {
        return this->empty()? 0 : this->last()->data()->size();
    }

    int level() const { return List<Quadlist<Entry<K, V>> *>::size(); }

    bool put(K, V);
    V* get(K k);
    bool remove(K k);

protected:
    bool skipSearch(
            NodeQListP &qlist,
            QNodeP &p,
            const K &k);
};

template <typename K, typename V>
V* SkipList<K, V>::get(K k) {
    if (this->empty()) return nullptr;
    // firstQList must exist
    NodeQListP firstQlist = this->first();
    QNodeP p = firstQlist->data()->first();
    return skipSearch(firstQlist, p, k)? &(p->entry.value) : nullptr; 
}

template <class K, class V>
bool SkipList<K, V>::skipSearch(NodeQListP &qlist, QNodeP &p, const K &k) {
    while (true) {
        while (p->succ && /* p->succ != nullptr */ p->entry.key <= k) {
            // p is not tailer
            p = p->succ;
        }
        // p->succ == nullptr means p points to tailer in current qlist now
        p = p->pred;
        if (p->pred /* p is not header */ && k == p->entry.key /* found */)
            return true; 
        qlist = qlist->next();
        if (!qlist->next()) // qlist points to tailer
            return false;
        // p <- the data node in next level
        p = (p->pred)? p->below : qlist->data()->first();
    }
}

template <class K, class V>
bool SkipList<K, V>::put(K k, V v)  {
    EntryT e = EntryT(k, v);
    if (this->empty()) // S[0]
        this->insertAsFirst(new QList);

    NodeQListP &qlist = this->first();
    QNodeP p = qlist->data()->first();

    if (skipSearch(qlist, p, k))
        while (p->below) 
            p = p->below;
    qlist = this->last(); // S[0], bottom level
    auto *b = qlist->data()->insertAfterAbove(e, p);

    while (rand() & 1) {
        while (qlist->data()->valid(p) && !p->above)
            p = p->prd;
        if (!qlist->data()->valid(p)) {
            if (qlist == this->first()) // now it is in top level
                this->insertAsFirst(new QList);
                // pointers  may be changed
            p = qlist->prev()->data()->first()->prev();
        } else {
            p = p->above;
        }

        qlist = qlist->prev(); // previous level
        b = qlist->data()->insertAfterAbove(e, p, b);
    }
    return true;
}

template <class K, class V>
bool SkipList<K, V>::remove(K k) {
    if (this->empty()) return false;

    NodeQListP qlist = this->first();
    QNodeP p = qlist->data()->first();

    if (!skipSearch(qlist, p, k)) // not found
        return false;

    do {
        QNodeP lower = p->below;
        qlist->data()->remove(p);
        p = lower;
        qlist = qlist->next();
    } while (qlist->next());

    while (!this->empty() && this->first()->data()->empty()) {
        // remove empty level
        this->remove(this->first());
    }

    return true;
}

#endif
