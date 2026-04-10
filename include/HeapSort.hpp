#pragma once
#include "SortingAlgorithm.hpp"

template<typename T>
class HeapSort : public SortingAlgorithm<T> {
    void Heapify(T* array, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && array[l] > array[largest]) largest = l;
        if (r < n && array[r] > array[largest]) largest = r;
        if (largest != i) {
            std::swap(array[i], array[largest]);
            Heapify(array, n, largest);
        }
    }
public:
    void Sort(T* array, int size) override {
        for (int i = size / 2 - 1; i >= 0; i--) Heapify(array, size, i);
        for (int i = size - 1; i > 0; i--) {
            std::swap(array[0], array[i]);
            Heapify(array, i, 0);
        }
    }
    std::string GetName() override { return "Heap Sort"; }
};