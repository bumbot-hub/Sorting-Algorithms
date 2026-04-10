#pragma once
#include <cstdlib>
#include <type_traits>
#include <fstream>
#include <string>
#include <iostream>
#include<random>

template <typename T>
class ArrayGenerator {
public:
    static T* GenerateRandom(int size, T minValue, T maxValue) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = RandomValue(minValue, maxValue);
        }

        return array;
    }

    static T* GenerateAscending(int size) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }

        return array;
    }

    static T* GenerateDescending(int size) {
        T* array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = size - i;
        }

        return array;
    }

    // Comment how partially sorted array works
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