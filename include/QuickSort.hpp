#pragma once
#include "SortingAlgorithm.hpp"
#include <ctime>

enum class PivotStrategy { Left, Right, Middle, Random };

/**
 * @class QuickSort
 * @brief Advanced QuickSort implementation with multiple pivot selection strategies.
 * Average Complexity: O(n log n). Worst case: O(n^2).
 * Optimized with tail recursion to minimize stack depth.
 */
template<typename T>
class QuickSort : public SortingAlgorithm<T> {
    PivotStrategy strategy;

    /**
     * @brief Partitions the array into two halves based on the selected pivot strategy.
     * @return Final index of the pivot.
     */
    int Partition(T* array, int low, int high) {
        int pivotIndex;
        if (strategy == PivotStrategy::Left) pivotIndex = low;
        else if (strategy == PivotStrategy::Right) pivotIndex = high;
        else if (strategy == PivotStrategy::Middle) pivotIndex = low + (high - low) / 2;
        else pivotIndex = low + rand() % (high - low + 1);

        std::swap(array[pivotIndex], array[high]);
        T pivot = array[high];
        int i = low;

        for (int j = low; j < high; j++) {
            if (array[j] < pivot) {
                std::swap(array[i], array[j]);
                i++;
            }
        }
        std::swap(array[i], array[high]);
        return i;
    }

    /**
     * @brief Internal recursive function with tail-call optimization.
     */
    void SortInternal(T* array, int low, int high)
    {
        while (low < high) {
            int pi = Partition(array, low, high);

            if (pi - low < high - pi) {
                SortInternal(array, low, pi - 1);
                low = pi + 1;
            } else {
                SortInternal(array, pi + 1, high);
                high = pi - 1;
            }
        }
    }

public:
    QuickSort(PivotStrategy s) : strategy(s)
    {
        static bool seeded = false;
        if (!seeded) {
            srand(time(NULL));
            seeded = true;
        }
    }
    void Sort(T* array, int size) override { SortInternal(array, 0, size - 1); }
    std::string GetName() override {
        switch(strategy) {
        case PivotStrategy::Left: return "QuickSort (Left)";
        case PivotStrategy::Right: return "QuickSort (Right)";
        case PivotStrategy::Middle: return "QuickSort (Middle)";
        case PivotStrategy::Random: return "QuickSort (Random)";
        }
        return "QuickSort";
    }
};