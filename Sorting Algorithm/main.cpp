#include <iostream>
#include <random>
#include "min_max_heap.h"

int main() {
    minMaxHeap<int> mmh;
    std::random_device rd;
    std::default_random_engine e(rd());
    for (int i = 0; i < 100000; i++) {
        mmh.push(e() % 100000);
    }

    while (!mmh.isEmpty()) {
        printf("%d\n", mmh.front());
        mmh.popFront();
    }

    return 0;
}