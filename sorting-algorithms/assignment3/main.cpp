#include "SortPointers.hpp"
#include <iostream>
#include <random>
#include <chrono>

using namespace sort_pointers;
using namespace std;

int main() {

    while(true){
    int choice;

    cout << "Do you want to get random numbers (1) or you want to input them yourself (2)?" << endl;

    cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 2) {
        std::cout << "Invalid input! Please, enter your choice (1 or 2): ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> choice;
    }

    int N;

    if (choice == 1) {
        cout << "How many numbers (with value between 0 and 200) do you want to be generated? (Enter a number): ";
    } else if (choice == 2) {
        cout << "How many numbers (with value between 0 and 200) do you want to input? (Enter a number): ";
    }

    cin >> N;
    while (std::cin.fail()) {
        std::cout << "Invalid input! Please, enter a number: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> N;
    }

    auto **arr = new const unsigned *[N];
    int number;

    if (choice == 2) {
        for (int i = 0; i < N; i++) {
            cout << "Give me number " << i + 1 << " (with value between 0 and 200): ";

            cin >> number;

            while (std::cin.fail() || number < 0 || number > 200) {
                std::cout << "Invalid input! Please, enter a number between 0 and 200: ";
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> number;
            }
            arr[i] = new unsigned(number);
        }

        cout << "Unsorted numbers: " << endl;

        cout << "[";
        for (int i = 0; i < N; i++) {
            std::cout << *arr[i];
            if (i != N - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    int alg;
    cout << "Select algorithm to use for sorting:" << endl;
    cout << "1 for Merge Sort (with WC: O(N*log(N))" << endl;
    cout << "2 for Quick Sort (with WC: O(N^2))" << endl;
    cout << "3 for Introspective (Intro) Sort (with WC: O(N*log(N))" << endl;
    

    std::cin >> alg;
    while (std::cin.fail() || alg < 1 || alg > 3) {
        std::cout << "Invalid input! Please, enter a number between 1 and 5: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> alg;
    }

    if (choice == 1) {
        // Get the time in nanos to use it as a seed for generation of "random" numbers
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto seed = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        std::mt19937 rng(seed);
        std::uniform_int_distribution<unsigned> dstr(0, 200);

        cout << "Unsorted numbers: " << endl;

        cout << "[";
        for (int i = 0; i < N; i++) {
            arr[i] = new unsigned(dstr(rng));
            std::cout << *arr[i];
            if (i != N - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    switch (alg) {
        case 1:
            mergesort(arr, arr + N);
            break;
        case 2:
            quicksort(arr, arr + N);
            break;
        case 3:
            introsort(arr, arr + N);
            break;
        default:
            break;
    }

    cout << "Sorted numbers: " << endl;

    cout << "[";
    for (int i = 0; i < N; i++) {
        std::cout << *arr[i];
        if (i != N - 1) {
            cout << ", ";
        }
        delete arr[i];
    }
    cout << "]" << endl;

    delete[] arr;

    int end;

    cout << "Do you want to continue testing / experimenting? [1 for Yes/ 0 for No]" << endl;

    std::cin >> end;

    while (std::cin.fail() || end < 0 || end > 1) {
        std::cout << "Invalid input! Please, enter a number between 0 and 1: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> end;
    }

    if (!end) {
        cout << "Thanks for testing!" << endl;
        break;
    }
    }
    return 0;
}
