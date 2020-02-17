#ifndef LIST_H_
#define LIST_H_

#include <cstdint>
#include <typeinfo>
#include "Node.h"

template <typename T>
class List {
  public:
    typedef int32_t Rank;
    typedef int32_t Size;
    typedef Node<T> NodeT;
    typedef Node<T> *NodeP;

    List();
    ~List();
    List(const List &);
    List(const List &, Rank off, int n);
    List(NodeP, int);

    Size  size() const { return N; }
    bool  empty() const { return 0 == size(); }
    NodeP first() const;
    NodeP last() const;
    T&    operator[](Rank r) const;
    NodeP find(const T &e) const;
    NodeP find(const T &e, int n, NodeP p) const;
    void  traverse(void (*visit)(T &e));

    NodeP insertAsFirst(const T &e);
    NodeP insertAsLast(const T &e);
    NodeP insertA(const T &e, NodeP p);
    NodeP insertB(const T &e, NodeP p);
    T     remove(NodeP p);
    int   deduplicate();
    int   uniquify();

  protected:
    NodeP node(Rank r) const;
    void  init();
    int   clear();
    void  copyNodes(NodeP, int);
    void  merge(NodeP, int, List &, NodeP, int);
    void  mergeSort(NodeP, int);
    void  selectionSort(NodeP, int);
    void  insertionSort(NodeP, int);

  private:
    Size  N;
    NodeP head;
    NodeP tail;
};

#include "List_construct.h"
#include "List_index.h"
#include "List_insert.h"
#include "List_traverse.h"
#include "List_find.h"
#include "List_remove.h"
#include "List_destruct.h"
#include "List_uniquify.h"

#endif
