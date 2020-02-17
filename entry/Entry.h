#ifndef ENTRY_H_
#define ENTRY_H_

template <class K, class V>
struct Entry {
    K k;
    V v;

    Entry() : k(), v() { }
    Entry(const K &k_, const V &v_) : k(k_), v(v_) { }
    Entry(const Entry &e) : k(e.k), v(e.v) { }

    bool operator<(const Entry &e) { return k < e.k; }
    bool operator>(const Entry &e) { return k > e.k; }
    bool operator==(const Entry &e) { return k == e.k; }
    bool operator!=(const Entry &e) { return k != e.k; }
};

#endif
