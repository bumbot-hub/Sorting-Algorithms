#pragma once
#include <string>

/**
 * @class Sorter
 * @brief Alternative interface for sorting classes.
 * Defines the contract for any sorting implementation in the system.
 */
template <typename T>
class Sorter {
public:
    /** @brief Pure virtual method to be implemented by specific algorithms. */
    virtual void sort(T* array, int size) = 0;

    /** @brief Returns the human-readable name of the algorithm. */
    virtual std::string getName() = 0;

    /** @brief Virtual destructor to ensure proper cleanup of derived objects. */
    virtual ~Sorter() {}
};