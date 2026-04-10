#pragma once
#include "SortingAlgorithm.hpp"
#include <string>

enum class ShellGapType { Shell, Knuth };

/**
 * @class ShellSort
 * @brief Implementation of Shell's sort with support for different gap sequences.
 * Features: Original Shell gaps (n/2^k) and Knuth's sequence (3^k-1)/2.
 * Complexity depends on the gap sequence used.
 */
template<typename T>
class ShellSort : public SortingAlgorithm<T> {
    ShellGapType gapType;
public:
    ShellSort(ShellGapType type) : gapType(type) {}

    void Sort(T* array, int size) override {
        if (gapType == ShellGapType::Shell) {
            // Odstępy wg Shella: n/2, n/4, ..., 1
            for (int gap = size / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < size; i++) {
                    T temp = array[i];
                    int j;
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                    }
                    array[j] = temp;
                }
            }
        } else {
            // Odstępy wg Knutha: h = 3h + 1
            int h = 1;
            while (h < size / 3) h = 3 * h + 1;

            while (h >= 1) {
                for (int i = h; i < size; i++) {
                    T temp = array[i];
                    int j;
                    for (j = i; j >= h && array[j - h] > temp; j -= h) {
                        array[j] = array[j - h];
                    }
                    array[j] = temp;
                }
                h /= 3;
            }
        }
    }

    std::string GetName() override {
        return gapType == ShellGapType::Shell ? "Shell (Shell gaps)" : "Shell (Knuth gaps)";
    }
};