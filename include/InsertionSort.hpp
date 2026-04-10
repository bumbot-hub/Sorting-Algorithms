#pragma once
#include "SortingAlgorithm.hpp"
#include <string>

template<typename T>
class InsertionSort : public SortingAlgorithm<T> {
public:
    void Sort(T* array, int size) override {
        for (int i = 1; i < size; i++) {
            T key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = key;
        }
    }
    std::string GetName() override { return "Insertion Sort"; }
};