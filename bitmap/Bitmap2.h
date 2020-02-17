#ifndef BITMAP2_H_
#define BITMAP2_H_

class Bitmap2 {
    public:
        typedef int Rank;
    private:
        Rank N;
        Rank top;
        Rank *T; 
        Rank *F; 
    protected:
        inline bool erased(Rank k) {
            return (0 <= F[k]) && (F[k] < top) && (-1 - k == T[F[k]]);
        }
    public:
        Bitmap2(Rank n = 8) 
            : N(n), top(0), T(new Rank[N]), F(new Rank[N]) {}
        ~Bitmap2() { delete [] F; delete [] T; }

        void  set(Rank k) {
            if (test(k)) return; // cannot insert twice
            if (!erased(k))
                F[k] = top++, T[F[k]] = k;
            else
                T[F[k]] = k;
        }

        void clear(Rank k) {
            if (test(k))
                T[F[k]] = -1 - k;
        }

        inline bool test(Rank k) {
            return (0 <= F[k]) && (F[k] < top) && (k == T[F[k]]);
        }
};


#endif
