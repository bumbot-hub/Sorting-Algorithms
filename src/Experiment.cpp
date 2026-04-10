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

using namespace std;

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
    string fileName;
    cout << "Podaj nazwe pliku: ";
    cin >> fileName;

    ifstream file(fileName);
    int size;
    if (!(file >> size)) {
        cout << "Blad odczytu rozmiaru!" << endl;
        return;
    }


    T* array = new T[size];
    for(int i=0; i<size; i++) file >> array[i];

    int choice;
    do
    {
        cout << "Wczytano tablice. Wybierz algorytm (1-Heap, 2-Shell, 3-Quick Middle) lub 0. Wyjdź z trybu: ";
        int algChoice; cin >> algChoice;

        if(algChoice == 0) break;

        T* copy = new T[size];
        for (int i=0; i<size; i++) copy[i] = array[i];
        SortingAlgorithm<T>* algo = nullptr;


        if(algChoice == 1) algo = new HeapSort<T>();
        else if(algChoice == 2) algo = new ShellSort<T>(ShellGapType::Knuth);
        else algo = new QuickSort<T>(PivotStrategy::Middle);

        cout << "Przed: "; ShowArray(copy, size);
        algo->Sort(copy, size);
        cout << "Po: "; ShowArray(copy, size);
        cout << "Czy posortowane: " << (algo->IsSorted(copy, size) ? "TAK" : "NIE") << endl;

        delete algo;
        delete[] copy;
    }while (true);

    delete[] array;
}

template <typename T>
void RunExperiment(SortingAlgorithm<T>* algo, const char* distribution, int size) {
    Timer timer;
    double totalTime = 0;
    const int repetitions = 100;

    for (int i = 0; i < repetitions; ++i) {
        T* data = nullptr;

        if (string(distribution) == "random") data = ArrayGenerator<T>::GenerateRandom(size, 0, 100000);
        else if (string(distribution) == "ascending") data = ArrayGenerator<T>::GenerateAscending(size);
        else if (string(distribution) == "descending") data = ArrayGenerator<T>::GenerateDescending(size);
        else if (string(distribution) == "33%_sorted") data = ArrayGenerator<T>::Generate33Sorted(size, 100000);
        else if (string(distribution) == "66%_sorted") data = ArrayGenerator<T>::Generate66Sorted(size, 100000);

        if (!data) continue;

        T* copy = new T[size];
        for(int k = 0; k < size; k++) copy[k] = data[k];

        timer.Start();
        algo->Sort(copy, size);
        double eTime = timer.ElapsedTimeMs();

        if (!algo->IsSorted(copy, size)){
            cerr <<"Błąd sortowania: " << algo->GetName() << " dla " << distribution << endl;
        }

        totalTime += eTime;

        delete[] data;
        delete[] copy;
    }
    double averageTime = totalTime / repetitions;
    ofstream file("wyniki_aizo.csv", ios::app);
    if (file.is_open()) {
        file << algo->GetName() << ";"
             << distribution << ";"
             << size << ";"
             << averageTime << endl;
        file.close();
    }

    cout << "Algorytm: " << algo->GetName()
         << " | Rozmiar: " << size
         << " | Sredni czas: " << averageTime << " ms" << endl;
}

template <typename T>
void RunFullExperiment() {
    const int SIZES[] = {10000, 61667, 113333, 165000, 216667, 268333, 320000};
    const char* DISTRIBUTIONS[] = {"random", "ascending", "descending", "33%_sorted", "66%_sorted"};

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
        delete algos[i];
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- MENU PROJEKTU ---\n";
        cout << "1. Tryb testowy (z pliku)\n";
        cout << "2. Pelny eksperyment (badania)\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
        case 1:
            runTestMode<int>();
            break;
        case 2:
            cout<< "Badanie dla typu int" << endl;
            RunFullExperiment<int>();

            cout<<"Badanie dla typu float" << endl;
            RunFullExperiment<float>();
            break;
        }
    } while (choice != 0);
    return 0;
}