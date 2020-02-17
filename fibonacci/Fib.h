#ifndef FIB_H_
#define FIB_H_

class Fib {
    public:
        Fib(int n = 0) : pre(0), cur(1) {
            while (cur < n) {
                int t = cur;
                cur = pre + cur;
                pre = t;
            }
        }

        inline int get() { return cur; }

        void prev() {
            int t = pre;
            pre = cur - pre;
            cur = t;
        }

        void next() {
            int t = cur;
            cur += pre;
            pre = t;
        }

    private:
        int pre;
        int cur;
};


#endif
