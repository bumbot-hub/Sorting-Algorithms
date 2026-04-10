#pragma once
#include "SortingAlgorithm.hpp"
#include "../include/Experiment.hpp"
#include "../include/ArrayGenerator.hpp"
#include "../include/InsertionSort.hpp"
#include "../include/HeapSort.hpp"
#include "../include/Shell.hpp"
#include "../include/QuickSort.hpp"
#include "../include/Timer.hpp"
#include <iostream>
#include <fstream>
#include <string>

/**
 * @brief Displays the content of the array to the standard output.
 * Used for visual verification of smaller arrays in test mode.
 */
template <typename T>
void ShowArray(T* array, int size);

/**
 * @brief Handles the manual testing mode.
 * Allows loading data from a file and verifying sorting correctness visually for QuickSort, Shell sort and Heap sort.
 */
template <typename T>
void runTestMode();


/**
 * @brief Runs the performance experiment for a specific algorithm and distribution.
 * Performs 100 repetitions and averages the results to minimize measurement error.
 */
template <typename T>
void RunExperiment(SortingAlgorithm<T>* algo, const char* distribution, int size);

/**
 * @brief Orchestrates the full benchmarking process.
 * Iterates through all algorithms, data distributions, and array sizes.
 */
template <typename T>
void RunFullExperiment();

template <typename T>
void ShowArray(T* array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;
}

template <typename T>
void runTestMode() {
    std::string fileName;
    std::cout << "Podaj nazwe pliku: ";
    std::cin >> fileName;

    // Load array size and data from a text file
    std::ifstream file(fileName);
    int size;
    if (!(file >> size)) {
        std::cout << "Blad odczytu rozmiaru!" << std::endl;
        return;
    }


    T* array = new T[size];
    for(int i=0; i<size; i++) file >> array[i];

    do
    {
        std::cout << "Wczytano tablice. Wybierz algorytm (1-Heap, 2-Shell, 3-Quick Middle) lub 0. Wyjdź z trybu: ";
        int algChoice; std::cin >> algChoice;

        if(algChoice == 0) break;

        // Use a copy to test different algorithms on the same dataset
        T* copy = new T[size];
        for (int i=0; i<size; i++) copy[i] = array[i];
        SortingAlgorithm<T>* algo = nullptr;


        if(algChoice == 1) algo = new HeapSort<T>();
        else if(algChoice == 2) algo = new ShellSort<T>(ShellGapType::Knuth);
        else algo = new QuickSort<T>(PivotStrategy::Middle);

        std::cout << "Przed: "; ShowArray(copy, size);
        algo->Sort(copy, size);
        std::cout << "Po: "; ShowArray(copy, size);
        std::cout << "Czy posortowane: " << (algo->IsSorted(copy, size) ? "TAK" : "NIE") << std::endl;

        // Clean up temporary variables
        delete algo;
        delete[] copy;
    }while (true);

    delete[] array; // Clean up original data
}

template <typename T>
void RunExperiment(SortingAlgorithm<T>* algo, const char* distribution, int size) {
    Timer timer;
    double totalTime = 0;
    const int repetitions = 100;

    for (int i = 0; i < repetitions; ++i) {
        T* data = nullptr;

        // Data generation based on requested distribution
        if (std::string(distribution) == "random") data = ArrayGenerator<T>::GenerateRandom(size, 0, 100000);
        else if (std::string(distribution) == "ascending") data = ArrayGenerator<T>::GenerateAscending(size);
        else if (std::string(distribution) == "descending") data = ArrayGenerator<T>::GenerateDescending(size);
        else if (std::string(distribution) == "33%_sorted") data = ArrayGenerator<T>::Generate33Sorted(size, 100000);
        else if (std::string(distribution) == "66%_sorted") data = ArrayGenerator<T>::Generate66Sorted(size, 100000);

        if (!data) continue;

        T* copy = new T[size];
        for(int k = 0; k < size; k++) copy[k] = data[k];

        timer.Start();
        algo->Sort(copy, size);
        double eTime = timer.ElapsedTimeMs();

        // Safety check for algorithm correctness during benchmarks
        if (!algo->IsSorted(copy, size)){
            std::cerr <<"Błąd sortowania: " << algo->GetName() << " dla " << distribution << std::endl;
        }

        totalTime += eTime;

        delete[] data;
        delete[] copy;
    }

    // Average time calculation and CSV export for report charts
    double averageTime = totalTime / repetitions;
    std::ofstream file("wyniki_aizo.csv", std::ios::app);
    if (file.is_open()) {
        file << algo->GetName() << ";"
             << distribution << ";"
             << size << ";"
             << averageTime << std::endl;
        file.close();
    }

    std::cout << "Algorytm: " << algo->GetName()
         << " | Rozmiar: " << size
         << " | Sredni czas: " << averageTime << " ms" << std::endl;
}

template <typename T>
void RunFullExperiment() {
    // Array sizes chosen to ensure measurement in milliseconds
    const int SIZES[] = {10000, 61667, 113333, 165000, 216667, 268333, 320000};
    const char* DISTRIBUTIONS[] = {"random", "ascending", "descending", "33%_sorted", "66%_sorted"};

    // Initialize all required algorithms for testing
    SortingAlgorithm<T>* algos[8];
    algos[0] = new InsertionSort<T>();
    algos[1] = new HeapSort<T>();
    algos[2] = new ShellSort<T>(ShellGapType::Shell);
    algos[3] = new ShellSort<T>(ShellGapType::Knuth);
    algos[4] = new QuickSort<T>(PivotStrategy::Left);
    algos[5] = new QuickSort<T>(PivotStrategy::Middle);
    algos[6] = new QuickSort<T>(PivotStrategy::Right);
    algos[7] = new QuickSort<T>(PivotStrategy::Random);

    for (int i = 0; i < 8; i++) {
        std::cout << "\nBadanie: " << algos[i]->GetName() << std::endl;
        for (int j = 0; j < 5; j++) {
            std::cout << "  Dystrybucja: " << DISTRIBUTIONS[j] << std::endl;
            for (int s = 0; s < 7; s++) {
                RunExperiment<T>(algos[i], DISTRIBUTIONS[j], SIZES[s]);
            }
        }
        delete algos[i]; // Memory management for algorithm objects
    }
}
