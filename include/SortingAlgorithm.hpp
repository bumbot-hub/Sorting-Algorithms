#pragma once
#include <string>

template<typename T>
class SortingAlgorithm {
public:
    virtual void Sort(T* array, int size) = 0;
    virtual std::string GetName() = 0;

    virtual ~SortingAlgorithm() {}

    bool IsSorted(T* array, int size) {
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }
        return true;
    }
};