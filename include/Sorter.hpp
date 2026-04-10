#pragma once

template <typename T>
class Sorter {
public:
    virtual void sort(T* array, int size) = 0;
    virtual std::string getName() = 0;
    virtual ~Sorter() {}
};