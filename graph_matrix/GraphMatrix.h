#ifndef GRAPH_MATRIX_H_
#define GRAPH_MATRIX_H_

#include <climits>
#include <iostream>
#include "../graph/Graph.h"
#include "../vector/Vector.h"
#include "../queue/Queue.h"

template <class Tv> struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime; // timestamp
    int parent;
    int priority;

    Vertex(const Tv &d = static_cast<Tv>(0))
        : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
          dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) { }
};

template <class Te> struct Edge {
    Te data;
    int weight;
    EType type;

    Edge(const Te &d, int w = 0) : data(d), weight(w), type(UNDETERMINED) {  }
};

template <class Tv, class Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    using GraphT = Graph<Tv, Te>;
    using VertexT = Vertex<Tv>;
    using EdgeT = Edge<Te>;

    Vector<VertexT> V;
    Vector< Vector< EdgeT* > > E;
public:
    GraphMatrix() { this->n = this->e = 0; }
    ~GraphMatrix() {
        for (int i = 0; i < this->n; ++i) {
            for (int j = 0; j < this->n; ++j) {
                if (E[i][j]) {
                    delete E[i][j];
                }        
            }
        }
    }

    // query operations of vertices
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return this->nextNbr(i, this->n); }
    virtual int nextNbr(int i, int j) {
        while (-1 < j && !this->exists(i, --j)) {
        }
        return j;
    }
    virtual VStatus& status(int i) { return this->V[i].status; }
    virtual int& dTime(int i) { return this->V[i].dTime; }
    virtual int& fTime(int i) { return this->V[i].fTime; }
    virtual int& parent(int i) { return this->V[i].parent; }
    virtual int& priority(int i) { return this->V[i].priority; }

    // dynamical operations for vertices
    virtual int insert(const Tv &newV) {
        for (int i = 0; i < this->n; ++i)
            E[i].insert(nullptr);
        ++this->n;
        E.insert(Vector<EdgeT*>(this->n, this->n, nullptr));
        return V.insert(VertexT(newV));
    }

    virtual Tv remove(int i) {
        // all out edges
        for (int j = 0; j < this->n; ++j)
            if (this->exists(i, j)) {
                delete E[i][j];
                --V[j].inDegree;
            }
        E.remove(i);
        --this->n;

        // E[i] has been removed
        // make positions of vertices coninsistent
        Tv vBak = this->vertex(i);
        V.remove(i);

        // all in edges
        for (int j = 0; j < this->n; ++j)
            if (this->exists(j, i)) {
                delete E[j][i];
                E[j].remove(i);
                --V[j].outDegree;
            }

        return vBak;
    }

    void print() {
        std::cout << "  ";
        for (int i = 0; i < this->n; ++i)
            std::cout << this->V[i].data << ' ';
        std::cout << std::endl;
        for (int i = 0; i < this->n; ++i) {
            std::cout << this->V[i].data << ' ';
            for (int j = 0; j < this->n; ++j) {
                if (exists(i, j))
                    std::cout << E[i][j]->data << ' ';
                else
                    std::cout << "*" << ' ';
            }
            std::cout << std::endl;
        }
    }

    // query operations for edges
    virtual bool exists(int i, int j) {
        return (0 <= i) && (i < this->n) 
            && (0 <= j) && (j < this->n) && E[i][j] != nullptr;
    }

    virtual EType& type(int i, int j) { return E[i][j]->type; }
    virtual Te& edge(int i, int j) { return E[i][j]->data; }
    virtual int& weight(int i, int j) { return E[i][j]->weight; }

    virtual void insert(const Te &edge, int i, int j, int w = 0) {
        if (exists(i, j)) return;
        E[i][j] = new EdgeT(edge, w);
        ++this->e;
        ++this->V[i].outDegree;
        ++this->V[j].inDegree;
    }

    virtual Te remove(int i, int j) {
        Te eBak = edge(i, j);
        delete E[i][j];
        --this->e;
        --this->V[i].outDegree;
        --this->V[j].inDegree;

        return eBak;
    }

    void bfs(int s) {
        this->reset();
        int clock = 0;
        int v = s;
        do 
            if (UNDISCOVERED == this->status(v))
                this->BFS(v, clock);
        while (s != (v = (++v % this->n)));
    }

    void dfs(int s) {
        this->reset();
        int clock = 0;
        int v = s;
        do
            if (UNDISCOVERED == this->status(v))
                this->DFS(v, clock);
        while (s != (v  = (++v % this->n)));
    }

protected:
    void BFS(int v, int &clock) {
        Queue<int> q;
        status(v) = DISCOVERED;
        q.enqueue(v);

        while (!q.empty()) {
            int u = q.dequeue();
            dTime(u) = ++clock;

            for (auto v = firstNbr(u); -1 < v; v = nextNbr(u, v)) {
                if (status(v) == UNDISCOVERED) {
                    status(v) = DISCOVERED;
                    q.enqueue(v);
                    type(u, v) = TREE;
                    parent(v) = u;
                } else {
                    type(u, v) = CROSS;
                }
            }

            status(u) = VISITED;
        }
    }

    void DFS(int v, int &clock) {
        status(v) = DISCOVERED;
        dTime(v) = ++clock;

        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            switch (status(u)) {
                case UNDISCOVERED:
                    parent(u) = v;
                    type(v, u) = TREE;
                    DFS(u, clock);
                    break;
                case DISCOVERED:
                    type(v, u) = BACKWARD;
                    break;
                default:
                    type(v, u) = (dTime(v) < dTime(u))? FORWARD : CROSS;
                    break;
            }
        }
        status(v) = VISITED;
        fTime(v) = ++clock;
    }

};

#endif
