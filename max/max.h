#ifndef MAX_H_
#define MAX_H_

template <typename T>
T& maxI(T *A, int l, int r) {
    // find maximum element in A[l, r)
    // l < r is required
    T *p = &A[l];
    while (++l < r) if (*p < A[l]) p = &A[l];
    return *p;
}

template <typename T>
T& max(T &a, T &b) { return a < b? b : a; }

template <typename T>
T& maxR(T *A, int l, int r) {
    return (l + 1 == r)? A[l] : max(A[l], maxR(A, l + 1, r));
}

template <typename T>
T& maxR2(T *A, int l, int r) {
    // O(logn)
    if (l +  1 == r) return A[l];
    int mi = (l + r) >> 1;
    return max(maxR2(A, l, mi), maxR2(A, mi, r));
}


#endif
