#pragma once
#include <string>

/**
 * @class SortingAlgorithm
 * @brief Abstract base class (interface) for all sorting implementations.
 * Uses templates to support various data types (int, float, etc.).
 */
template<typename T>
class SortingAlgorithm {
public:
    virtual void Sort(T* array, int size) = 0;
    virtual std::string GetName() = 0;

    virtual ~SortingAlgorithm() {}

    /**
     * @brief Integrity check to verify if the array is actually sorted.
     * Required for preliminary algorithm verification.
     */
    bool IsSorted(T* array, int size) {
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }
        return true;
    }
};