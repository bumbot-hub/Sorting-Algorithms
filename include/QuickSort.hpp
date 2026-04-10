#pragma once
#include "SortingAlgorithm.hpp"
#include <ctime>

enum class PivotStrategy { Left, Right, Middle, Random };

template<typename T>
class QuickSort : public SortingAlgorithm<T> {
    PivotStrategy strategy;

    int Partition(T* array, int low, int high) {
        int pivotIndex;
        if (strategy == PivotStrategy::Left) pivotIndex = low;
        else if (strategy == PivotStrategy::Right) pivotIndex = high;
        else if (strategy == PivotStrategy::Middle) pivotIndex = low + (high - low) / 2;
        else pivotIndex = low + rand() % (high - low + 1);

        std::swap(array[pivotIndex], array[high]); // Przenieś pivot na koniec
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