#ifndef INC_7662_MIN_MAX_HEAP_H
#define INC_7662_MIN_MAX_HEAP_H
#include <cmath>
#include <limits>
#define MAX_SIZE 1048576

template<typename T>
class minMaxHeap {
private:
    int size;
    T* heap;

    static bool min(T a, T b) {
        return a < b;
    }

    static bool max(T a, T b) {
        return a > b;
    }

    int level(int i) {
        return (int)(log(i)/log(2));
    }

    bool isMin(int i) {
        return (level(i) % 2 == 0);
    }

    void pushDown(int i) {
        pushDownImpl(i, this->isMin(i));
    }

    void smallestChild(T* s, int* si, int start, int cnt, bool(*compare)(T, T)) {
        for (int j = 0; j < cnt; j++) {
            if (compare(this->heap[start], *s) && start <= this->size) {
                *s = this->heap[start];
                *si = start;
            }
            start++;
        }
    }

    int smallestChild(int i, bool isMin) {
        bool(*compare)(T, T) = isMin ? min : max;
        T s = isMin ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
        int si = -1;
        int i2 = i*2;
        int i4 = i*4;
        smallestChild(&s, &si, i2, 2, compare);
        smallestChild(&s, &si, i4, 4, compare);
        return si;
    }

    void pushDownImpl(int i, bool isMin) {
        if (i*2 <= this->size) {
            bool(*compare)(T, T) = isMin ? min : max;
            int child = smallestChild(i, isMin);
            if (level(child) - level(i) == 2 && child != -1) {
                if (compare(this->heap[child], this->heap[i])) {
                    std::swap(this->heap[child], this->heap[i]);
                    int parent = child / 2;
                    if (compare(this->heap[parent], this->heap[child]))
                        std::swap(this->heap[parent], this->heap[child]);
                    pushDownImpl(child, isMin);
                }
            }
            else if (compare(this->heap[child], this->heap[i])) {
                std::swap(this->heap[child], this->heap[i]);
            }
        }
    }

    void pushUp(int i) {
        if (this->size >= 1)
            pushUpImpl(i, isMin(i));
    }

    void pushUpImpl(int i, bool isMin) {
        int parent = i/2;
        bool(*compare)(T, T) = isMin ? min : max;
        if (compare(this->heap[parent], this->heap[i])) {
            std::swap(this->heap[parent], this->heap[i]);
            this->pushUpImplImpl(parent, !isMin);
        }
        else
            this->pushUpImplImpl(i, isMin);
    }

    void pushUpImplImpl(int i, bool isMin) {
        bool (*compare)(T, T) = isMin ? min : max;
        int grandparent = i / 2 / 2;
        if (grandparent >= 1) {
            if (compare(this->heap[i], this->heap[grandparent])) {
                std::swap(this->heap[i], this->heap[grandparent]);
                pushUpImplImpl(grandparent, isMin);
            }
        }
    }

public:
    minMaxHeap() : size(0), heap(new T[MAX_SIZE]) {
    }

    ~minMaxHeap() {
        delete [] heap;
    }

    void push(T n) {
        int newlyAppended = this->size + 1;
        this->heap[newlyAppended] = n;
        this->pushUp(newlyAppended);
        this->size++;
    }

    T front() {
        return this->heap[1];
    }

    T back() {
        int backIndex = this->size == 1 ? 1 : 2;
        if (this->size >= 3)
            backIndex = this->heap[2] > this->heap[3] ? 2 : 3;
        int back = this->heap[backIndex];
        return back;
    }

    void popFront() {
        this->heap[1] = this->heap[this->size];
        this->pushDown(1);
        this->size--;
    }

    void popBack() {
        int poppedIndex = (this->size == 1) ? 1 : 2;
        if (this->size >= 3)
            poppedIndex = (this->heap[2] > this->heap[3] ? 2 : 3);
        this->heap[poppedIndex] = this->heap[this->size];
        this->pushDown(poppedIndex);
        this->size--;
    }

    bool isEmpty() const {
        return !this->size;
    }
};
#endif