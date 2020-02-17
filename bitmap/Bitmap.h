#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <cstring>

class Bitmap {
    private:
        uint32_t N;  // number of allocted bytes 
        uint8_t *B; // memory of bits
    public:
        Bitmap(int nBits = 8)
            : N((nBits + 7) / sizeof(uint8_t)), B(new uint8_t[N]) {
                memset(B, 0, N);
        }

        ~Bitmap() { delete [] B; N = 0; }

        void set(uint32_t k) {
            expand(k);
            B[k >> 3] |= (0x80u >> (k & 0x07u));
        }

        void clear(uint32_t k) {
            expand(k);
            B[k >> 3] &= ~(0x80u >> (k & 0x70u));
        }

        bool test(uint32_t k) {
            expand(k);
            return B[k >> 3] & (0x80u >> (k & 0x70u));
        }

    protected:
        void expand(uint32_t k) {
            if (k * 8 < N) return;
            uint8_t *newB = new uint8_t[N << 1];
            memcpy(newB, B, N);
            memset(newB + N, 0, N);
            B = newB;
            N <<= 1;
        }
};


#endif
