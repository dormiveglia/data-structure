#ifndef BTREE_H_
#define BTREE_H_

#include "BTNode.h"
#include <iostream>

template <class T>
class BTree {
public:
    using BTNodePtr = typename BTNode<T>::Ptr;
    
    // constructor
    BTree(int order = 3) : _order(order), _size(0), _root(new BTNode<T>()) {}
    ~BTree() {
//        release(_root);
    }

    const int order() const { return _order; }
    const int size() const { return _size; }
    BTNodePtr & root() { return _root; }
    bool empty() const { return !_root; }

    BTNodePtr search(const T &e) {
        BTNodePtr v = _root;
        _hot = nullptr;

        // start searching
        while (v) {
            // current node exists
            auto r = v->key.search(e);
            if (0 <= r && e == v->key[r]) return v;
            // key isn't in current node
            _hot = v;
            v = v->child[r + 1];
        }

        // if not found 
        return nullptr;
    }

    bool insert(const T &e) {
        BTNodePtr v = search(e);
        if (v) return false; // e exists

        auto r = _hot->key.search(e); // find the position to be inserted
        _hot->key.insert(r + 1, e);
        _hot->child.insert(r + 2, nullptr);
        ++_size;

        // split when neccessary
        solveOverflow(_hot);

        return true;
    }

    bool remove(const T &e) {
        BTNodePtr v = search(e);
        if (!v) return false;

        auto r = v->key.search(e); // r exists
        if (v->child[0]) {
            // v has children
            auto u = v->child[r + 1];
            while (u->child[0])
                u = u->child[0]; // u is the succ of e
            v->key[r] = u->key[0];
            v = u;
            r = 0; // remove u[0]
        }

        v->key.remove(r);
        v->child.remove(r + 1);
        --_size;

        solveUnderflow(v);

        return true;
    }

protected:
    const int _order; // order of B-Tree, >= 3
    int _size; // number of all keys
    BTNodePtr _root;
    BTNodePtr _hot;
    
    void solveOverflow(BTNodePtr v) {
        if (!v || v->child.size() <= order())
            return;


        auto s = order() / 2;

        BTNodePtr u = new BTNode<T>();
        for (auto j = 0; j < order() - s - 1; ++j) {
            u->key.insert(j, v->key.remove(s + 1));
            u->child.insert(j, v->child.remove(s + 1));
        }
        u->child[order() - s - 1] = v->child.remove(s + 1);

        if (u->child[0])
            for (auto j = 0; j < order() - s; ++j)
                u->child[j]->parent = u;

        auto p = v->parent;
        if (!p) { // change to the same status as parent existing
            _root = p = new BTNode<T>();
            p->child[0] = v;
            v->parent = p;
        }

        auto r = 1 + p->key.search(v->key[0]);
        p->key.insert(r, v->key.remove(s));
        p->child.insert(r + 1, u);
        u->parent = p;

        solveOverflow(p);
    }

    void solveUnderflow(BTNodePtr v) {
        if (!v || v->child.size() >= (order() + 1) / 2) return;

        auto p = v->parent;
        if (!p) {
            // v is root
            // check if v is empty and has child
            if (!v->key.size() && v->child[0]) {
                _root = v->child[0];
                _root->parent = nullptr;
                v->child[0] = nullptr;
                delete v;
            }

            return;
        }

        decltype(v->child.size()) r = 0;
        while (p->child[r] != v)
            ++r;

    // 情况1：向左兄弟借关键码
       if ( 0 < r ) { //若v不是p的第一个孩子，则
          BTNodePtr ls = p->child[r - 1]; //左兄弟必存在
          if ( ( _order + 1 ) / 2 < ls->child.size() ) { //若该兄弟足够“胖”，则
             v->key.insert ( 0, p->key[r - 1] ); //p借出一个关键码给v（作为最小关键码）
             p->key[r - 1] = ls->key.remove ( ls->key.size() - 1 ); //ls的最大关键码转入p
             v->child.insert ( 0, ls->child.remove ( ls->child.size() - 1 ) );
             //同时ls的最右侧孩子过继给v
             if ( v->child[0] ) v->child[0]->parent = v; //作为v的最左侧孩子
             return; //至此，通过右旋已完成当前层（以及所有层）的下溢处理
          }
       } //至此，左兄弟要么为空，要么太“瘦”
    // 情况2：向右兄弟借关键码
       if ( p->child.size() - 1 > r ) { //若v不是p的最后一个孩子，则
          BTNodePtr rs = p->child[r + 1]; //右兄弟必存在
          if ( ( _order + 1 ) / 2 < rs->child.size() ) { //若该兄弟足够“胖”，则
             v->key.insert ( v->key.size(), p->key[r] ); //p借出一个关键码给v（作为最大关键码）
             p->key[r] = rs->key.remove ( 0 ); //ls的最小关键码转入p
             v->child.insert ( v->child.size(), rs->child.remove ( 0 ) );
             //同时rs的最左侧孩子过继给v
             if ( v->child[v->child.size() - 1] ) //作为v的最右侧孩子
                v->child[v->child.size() - 1]->parent = v;
             return; //至此，通过左旋已完成当前层（以及所有层）的下溢处理
          }
       } //至此，右兄弟要么为空，要么太“瘦”
        // 情况3：左、右兄弟要么为空（但不可能同时），要么都太“瘦”——合并
       if ( 0 < r ) { //与左兄弟合并
          BTNodePtr ls = p->child[r - 1]; //左兄弟必存在
          ls->key.insert ( ls->key.size(), p->key.remove ( r - 1 ) ); p->child.remove ( r );
          //p的第r - 1个关键码转入ls，v不再是p的第r个孩子
          ls->child.insert ( ls->child.size(), v->child.remove ( 0 ) );
          if ( ls->child[ls->child.size() - 1] ) //v的最左侧孩子过继给ls做最右侧孩子
             ls->child[ls->child.size() - 1]->parent = ls;
          while ( !v->key.empty() ) { //v剩余的关键码和孩子，依次转入ls
             ls->key.insert ( ls->key.size(), v->key.remove ( 0 ) );
             ls->child.insert ( ls->child.size(), v->child.remove ( 0 ) );
             if ( ls->child[ls->child.size() - 1] ) ls->child[ls->child.size() - 1]->parent = ls;
          }
          release ( v ); //释放v
       } else { //与右兄弟合并
          BTNodePtr rs = p->child[r + 1]; //右兄弟必存在
          rs->key.insert ( 0, p->key.remove ( r ) ); p->child.remove ( r );
          //p的第r个关键码转入rs，v不再是p的第r个孩子
          rs->child.insert ( 0, v->child.remove ( v->child.size() - 1 ) );
          if ( rs->child[0] ) rs->child[0]->parent = rs; //v的最左侧孩子过继给ls做最右侧孩子
          while ( !v->key.empty() ) { //v剩余的关键码和孩子，依次转入rs
             rs->key.insert ( 0, v->key.remove ( v->key.size() - 1 ) );
             rs->child.insert ( 0, v->child.remove ( v->child.size() - 1 ) );
             if ( rs->child[0] ) rs->child[0]->parent = rs;
          }
          release ( v ); //释放v
       }
       solveUnderflow ( p ); //上升一层，如有必要则继续分裂——至多递归O(logn)层
       return;

    }

    void release(BTNodePtr v) {
        if (!v) return;
        for (int i = 0; i < v->child.size(); ++i)
            release(v->child[0]);
        delete v;
    }
};

#endif
