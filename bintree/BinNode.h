#ifndef BINNODE_H_
#define BINNODE_H_

typedef enum { RB_RED, RB_BLACK } RBColor;

#include "../stack/Stack.h"
#include "../queue/Queue.h"
#include <iostream>

template <class T> class BinTree;

template <class T> class BinNode {
  private:
    friend class BinTree<T>;
    using BinNodeP = BinNode<T>*;
    T _data;
    BinNodeP lc, rc, parent;
    int height;
    int npl;
    RBColor color;

  public:
    BinNode(const T &e, BinNodeP par = nullptr, BinNodeP l = nullptr, BinNodeP r = nullptr,
            int h = 0, int n = 0, RBColor c = RB_RED)
        : _data(e), lc(l), rc(r), parent(par), height(h), npl(n), color(c) {  }
    BinNode() : lc(nullptr), rc(nullptr), parent(nullptr), height(0), npl(0), color(RB_RED) { }

    // query operations
    // all these operations are O(1)
    int size() const; // may not be updated
    BinNodeP succ() const {
        BinNodeP s = this;
        if (rc) {
            s = rc;
            while (s) {
                s->hasLChild();
                s = s->lc;
            }
        } else {
            BinNodeP p = s->parent;
            while (s->isRChild())
                s = p, p = s->parent;
            s = p;
        }
        return s;
    } 
    T& data() { return _data; }
    const T& data() const { return _data; }
    bool isRoot() const { return !this->parent; }
    bool isLChild() const { return hasParent() && this->parent->lc == this; }
    bool isRChild() const { return hasParent() && this->parent->rc == this; }
    bool hasParent() const { return this->parent; }
    bool hasLChild() const { return this->lc; }
    bool hasRChild() const { return this->rc; }
    bool hasChild() const { return hasLChild() || hasRChild(); }
    bool hasBothChild() const { return hasChild() && hasRChild(); }
    bool isLeaf() const { return !hasChild(); }
    BinNodeP sibling() const { return isLChild()? parent->rc : parent->lc; }
    BinNodeP uncle() const { return isRoot()? nullptr : parent->sibling(); }

    // traverse
    // objects of VST are callable
    // the time is depended on the size of the tree rooted at this node
    template <typename VST> void travLevel(const VST &vst) {
        BinNode::travLevel(this, vst);
    }
    
    template <typename VST> void travPre(const VST &vst) {
        BinNode::travPre_I1(this, vst);
    }

    template <typename VST> void travIn(const VST &vst) {
        BinNode::travIn_R(this, vst);
    }

    template <typename VST> void travPost(const VST &vst) {
        BinNode::travPost_R(this, vst);
    }

    template <class VST> static void travLevel(BinNodeP x, const VST &vst) {
        Queue<BinNodeP> q;
        if (x) q.enqueue(x);
        while (!q.empty()) {
            x = q.dequeue();
            if (x->hasLChild()) q.enqueue(x->lc);
            if (x->hasRChild()) q.enqueue(x->rc);
            vst(x->data());
        }
    }

    template <class VST> static void travPre_R(BinNodeP x, const VST &vst) {
        if (!x) return;
        vst(x->data());
        travPre_R(x->lc, vst);
        travPre_R(x->rc, vst);
    }

    template <class VST> static void travPre_I1(BinNodeP x, const VST &vst) {
        Stack<BinNodeP> S;
        if (x) S.push(x);
        while (!S.empty()) {
            x = S.pop();
            if (x->hasRChild()) S.push(x->rc);
            if (x->hasLChild()) S.push(x->lc);
            vst(x->data());
        }
    }

    template <class VST> static void visitAlongLeftBranch(
            BinNodeP x, const VST &vst, Stack<BinNodeP> &s) {
        while (x) {
            vst(x->data());
            s.push(x->rc);
            x = x->lc;
        } 
    }

    template <class VST> static void travPre_I2(BinNodeP x, const VST &vst) {
        Stack<BinNodeP> s;
        if (x) s.push(x);
        while (!s.empty()) {
            x = s.pop();
            visitAlongLeftBranch(x, vst, s);
        }
    }

    template <class VST> static void travPost_R(BinNodeP x, const VST &vst) {
        if (!x) return;
        travPost_R(x->lc, vst);
        travPost_R(x->rc, vst);
        vst(x->data());
    }

    template <class VST> static void travIn_R(BinNodeP x, const VST &vst) {
        if (!x) return;
        travIn_R(x->lc, vst);
        vst(x->data());
        travIn_R(x->rc, vst);
    }

    template <class VST> static void travIn_I(BinNodeP x, const VST &vst) {
        // TODO: debug
        Stack<BinNodeP> s;
        if (x) s.push(x);
        while (!s.empty()) {
            BinNodeP top = s.top();

            std::cout << "top = " << top->data() << std::endl;
            std::cout << top->hasLChild() << std::endl;

            if (top->hasLChild()) {
                s.push(top->lc);
            } else {
                s.pop();
                vst(top->data());
                if (top->hasRChild())
                    s.push(top->rc);
            }
        }
    }

    // insertions
    // O(1) operations
    BinNodeP insertAsLC(const T &e) { return lc = new BinNode(e, this); };
    BinNodeP insertAsRC(const T &e) { return rc = new BinNode(e, this); };

    static int stature(BinNodeP p) { return p? p->height : -1; }
};

#endif
