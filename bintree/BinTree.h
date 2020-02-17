#ifndef BINTREE_H_
#define BINTREE_H_

#include "BinNode.h"

template <class T>
class BinTree {
  public:
    using BinNodeP = BinNode<T>*;
    using BinNodeT = BinNode<T>;

    BinTree() : _size(0), _root(0) {  }

    // O(1)
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodeP root() const { return _root; }

    // insertion
    BinNodeP insertAsRoot(const T &e);
    BinNodeP insertAsLC(BinNodeP x, const T &e);
    BinNodeP insertAsRC(BinNodeP x, const T &e);
    BinNodeP attachAsLC(BinNodeP x, BinTree &t);
    BinNodeP attachAsRC(BinNodeP x, BinTree &t);

    // removal
    int remove(BinNodeP x);
    int removeAt(BinNodeP x);
    BinTree* secede(BinNodeP x);

    // traverse
    template <class VST> void travLevel(const VST &vst) const {
        if (root()) root()->travLevel(vst);
    }
    template <class VST> void travPre(const VST &vst) const {
        if (root()) root()->travPre(vst);
    }
    template <class VST> void travIn(const VST &vst) const {
        if (root()) root()->travIn(vst);
    }
    template <class VST> void travPost(const VST &vst) const {
        if (root()) root()->travPost(vst);
    }

  protected:
    virtual int updateHeight(BinNodeP x);
    void updateHeightAbove(BinNodeP x);


  private:
    int _size;
    BinNodeP _root;
};

#include "BinTree_insert.h"
#include "BinTree_height.h"
#include "BinTree_remove.h"

#endif
