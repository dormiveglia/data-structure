#ifndef COUNT_ONES_H_
#define COUNT_ONES_H_

#include <cstdint>

int countOnes1(unsigned n) { 
    // O(I) where I is the number of ones
    int ones = 0;
    while (0 < n) {
        ++ones;
        n = n & (n - 1); // eliminate the last 1
    }
    return ones;
}

#define POW(c) (1 << (c))
#define MASK(c) (((uint32_t) -1) / (POW(POW(c)) + 1))
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))

int countOnes2(uint32_t n) {
    // O(log2W) W = O(log2n)
    n = ROUND(n, 0);
    n = ROUND(n, 1);
    n = ROUND(n, 2);
    n = ROUND(n, 3);
    n = ROUND(n, 4);

    return n;
}

#endif
