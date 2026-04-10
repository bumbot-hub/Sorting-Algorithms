#include "../include/Experiment.hpp"
#include <iostream>
#include <fstream>

using namespace std;

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