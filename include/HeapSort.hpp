#pragma once
#include "SortingAlgorithm.hpp"

/**
 * @class HeapSort
 * @brief Implementation of the HeapSort algorithm using a binary max-heap.
 * Time Complexity: O(n log n) for all cases (best, average, worst).
 * Space Complexity: O(1) - in-place sorting.
 */
template<typename T>
class HeapSort : public SortingAlgorithm<T> {
    /**
     * @brief Maintains the max-heap property for a subtree.
     * @param n Size of the heap.
     * @param i Root index of the subtree.
     */
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