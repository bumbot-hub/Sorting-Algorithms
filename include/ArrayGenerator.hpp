#pragma once
#include <type_traits>
#include <fstream>
#include <string>
#include <iostream>
#include<random>

/**
 * @class ArrayGenerator
 * @brief Utility class for generating various data distributions for sorting benchmarks.
 */
template <typename T>
class ArrayGenerator {
public:
    /**
     * @brief Generates a random array using Mersenne Twister (mt19937).
     * Solves the RAND_MAX limitation of standard rand(). - dopisać że to jest lepsze dla rozmiarów typu 32k el.
     */
    static T* GenerateRandom(int size, T minValue, T maxValue) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = RandomValue(minValue, maxValue);
        }

        return array;
    }

    /** @brief Generates an array sorted in ascending order. */
    static T* GenerateAscending(int size) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }

        return array;
    }

    /** @brief Generates an array sorted in descending order. */
    static T* GenerateDescending(int size) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = size - i;
        }

        return array;
    }

    /**
     * @brief Generates an array where the first 33% of elements are already sorted.
     * The initial segment is filled with zeros to satisfy
     * the partial sorting requirement while maintaining consistency for testing.
     */
    static T* Generate33Sorted(int size, T maxValue) {
        T* array = new T[size];
        int sortedSize = size * 0.33;

        for (int i=0; i<size; i++) {
            if (i<sortedSize) {
                array[i] = 0;
            }else {
                array[i] = RandomValue(1, maxValue);
            }
        }

        return array;
    }

    /**
     * @brief Generates an array where the first 66% of elements are already sorted.
     * Works same as method with 33% sorted
     */
    static T* Generate66Sorted(int size, T maxValue) {
        T* array = new T[size];
        int sortedSize = size * 0.66;

        for (int i=0; i<size; i++) {
            if (i<sortedSize) {
                array[i] = 0;
            }else {
                array[i] = RandomValue(1, maxValue);
            }
        }

        return array;
    }

    /** @brief Uploads array data from a text file as per project requirements. */
    static T* UploadFromFile(const std::string& fileName, int size) {
        T* array = new T[size];
        std::fstream file(fileName, std::ios::in);

        if (!file.is_open()) {
            std::cout<<"Could not open file "<<fileName<<std::endl;
            delete [] array;

            return nullptr;
        }

        for (int i=0; i<size; i++) {
            if (!file >> array[i])
            {
                std::cout<<"File does not have enough data"<<std::endl;
                delete[] array;

                return nullptr;
            }
        }

        return array;
    }

private:
    /** @brief Internal helper for high-quality random number generation. */
    static T RandomValue(T minValue, T maxValue) {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(minValue, maxValue);
            return dist(gen);
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(minValue, maxValue);
            return dist(gen);
        }
    }
};