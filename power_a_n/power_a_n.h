#ifndef POWER_A_N_H_
#define POWER_A_N_H_

#include <cstdint>

uint64_t power2BF(uint64_t n) {
    // T(n) = T(n - 1) + 1
    // T(0) = 1
    // ==> T(n) = O(n)
    return n? power2BF(n - 1) << 1 : 1;
}

uint64_t power2_I(int64_t n) {
    // O(r) = O(logn)
    uint64_t ret = 1;
    for (uint64_t power2k = 2; 0 < n; power2k *= power2k, n >>= 1) {
        if (n & 1) ret *= power2k;
    }
    return ret;
}

uint64_t power(uint64_t a, uint64_t n) {
    // O(r) = O(logn)
    uint64_t ret = 1;
    for (uint64_t power_ak = a; 0 < n; power_ak *= power_ak, n >>= 1)
        if (n & 1)
            ret *= power_ak;
    return ret;
}


#endif
