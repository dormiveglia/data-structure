#ifndef NODE_H_
#define NODE_H_

template <class T> class List;

template <class T>
class Node {
  public:
    friend class List<T>;
    typedef Node *NodeP;
  private:
    T _data;
    NodeP _prev, _next;
  public:
    Node(const T &d, NodeP h = nullptr, NodeP t = nullptr)
        : _data(d), _prev(h), _next(t) { }
    Node(NodeP h = nullptr, NodeP t = nullptr)
        : _data(), _prev(h), _next(t) { }
    const T& data() const { return _data; }
    T& data() { return _data; }
    NodeP prev() const { return _prev; }
    NodeP next() const { return _next; }
    NodeP insertAsPrev(const T &e) {
        NodeP newNode = new Node<T>(e, prev(), this);
        prev()->_next = newNode; 
        this->_prev = newNode;
        return newNode;
    }

    NodeP insertAsNext(const T &e) {
        NodeP newNode = new Node<T>(e, this, next());
        next()->_prev = newNode;
        this->_next = newNode;
        return newNode;
    }
};

#endif
