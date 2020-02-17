#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>

template <typename Ptr>
void show_seq(Ptr beg, Ptr end) {
    std::cout << "[ ";
    while (beg < end) {
        std::cout << *beg++ << ' ';
    }
    std::cout << "]" << std::endl;
}

#endif
