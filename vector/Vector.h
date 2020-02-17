#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdlib>
#include <algorithm>
#include "../fibonacci/Fib.h"


template <typename T>
class Vector {
    public:
        using Rank = int;
        using Size = int; 

        // constructor
        Vector(Size c = DEFATLT_CAPACITY, Size s = 0, T v = 0);
        Vector(const T *A, Rank n);
        Vector(const T *A, Rank lo, Rank hi);
        Vector(const Vector &V);
        Vector(const Vector &V, Rank lo, Rank hi);
        Vector(Vector &&V);
        Vector& operator=(const Vector &);
        Vector& operator=(Vector &&);

        // destructor
        virtual ~Vector();

        // read-only interfaces
        Size size() const; // element count
        bool empty() const; // return true if there is no element.
        int  disordered() const;
        // return the last one element equal to e
        Rank find(const T &e) const;
        Rank find(const T &e, Rank lo, Rank hi) const;
        Rank search(const T &e) const;
        Rank search(const T &e, Rank lo, Rank hi) const;

        T& operator[](Rank r) const; // return a reference to element at rank r
        T remove(Rank r);
        Size remove(Rank lo, Rank hi);
        Rank insert(Rank r, const T &e);
        Rank insert(const T &e);
        void sort(Rank lo, Rank hi);
        void sort();
        // shuffle the sequence
        void unsort(Rank lo, Rank hi);
        void unsort();
        Size deduplicate(); // for unsorted vector
        Size uniquify(); // for sorted vector

        // traverse
        void traverse(void (*)(T &));
        template <typename VST> void traverse(const VST &);
            
        static constexpr int DEFATLT_CAPACITY = 3;
        
        Size _capacity;
        Size _size;
        T    *_elem;

        Rank max(Rank lo, Rank hi) const;

        // memory management
        void expand();
        void shrink();

        // some utilities
        void copyFrom(const T *A, Rank lo, Rank hi);

        // sort operation
        bool bubble(Rank lo, Rank hi);
        void bubbleSort(Rank lo, Rank hi);
        void selectionSort(Rank lo, Rank hi);
        void merge(Rank lo, Rank mi, Rank hi);
        void mergeSort(Rank lo, Rank hi);
        Rank partition(Rank lo, Rank hi);
        void quickSort(Rank lo, Rank hi);
        void heapSort(Rank lo, Rank hi);

        static inline Size maxSize(Size a, Size b) { return a < b? b : a; }
        static Rank binSearch(const T *A, const T &e, Rank lo, Rank hi);
        static Rank binSearch2(const T *A, const T &e, Rank lo, Rank hi);
        static Rank binSearch3(const T *A, const T &e, Rank lo, Rank hi);
        static Rank fibSearch(const T *A, const T &e, Rank lo, Rank hi);
};

#include "Vector_construct.h"
#include "Vector_memory_manage.h"
#include "Vector_size.h"
#include "Vector_find.h"
#include "Vector_search.h"
#include "Vector_insert.h"
#include "Vector_remove.h"
#include "Vector_traverse.h"
#include "Vector_sort.h"
#include "Vector_shuffle.h"
#include "Vector_uniquify.h"
#include "Vector_disordered.h"

#endif
