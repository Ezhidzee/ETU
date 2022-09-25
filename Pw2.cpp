#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std;

int *quickSort(int*, const int);

bool binarySearch(int*, const int, int);

bool bruteForce(int*, const int, int);

void findMinMax(int*, const int);

int main() {
    srand(time(0));
    int arrValues[100], arrSorted[100];
    for (int i = 0; i < 100; ++i) arrValues[i] = rand() % (99 + 99 + 1) - 99;
    for (int i = 0; i < 100; ++i) arrSorted[i] = arrValues[i];
    cout << "Array created: ";
    for (int i = 0; i < 10; ++i) cout << " " << arrValues[i];
    cout << "... " << endl;

    while (true) {
        int k;
        cin >> k;
        if (k == 0) {
            return 0;
        } else if (k == 1) {
            for (int i = 0; i < 100; ++i) arrSorted[i] = arrValues[i];
            chrono::time_point start = std::chrono::high_resolution_clock::now();
            quickSort(arrSorted, 100);
            chrono::time_point end = std::chrono::high_resolution_clock::now();
            cout << "Array sorted: ";
            for (int i = 0; i < 10; ++i) cout << " " << arrSorted[i];
            cout << "... ";
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
        } else if (k == 2) {
            cout << "Original array: ";
            findMinMax(arrValues, 100);
            cout << "Sorted array: ";
            quickSort(arrSorted, 100);
            findMinMax(arrSorted, 100);
        } else if (k == 3) {
            quickSort(arrSorted, 100);
            int mean = round((arrSorted[0] + arrSorted[99]) / 2);
            cout << "Mean of min & max: " << mean << endl;
            cout << "Indices of values equal to the mean: ";
            int counter = 0;
            for (int i = 0; i < 100; ++i) {
                if (arrValues[i] == mean) {
                    cout << i << " ";
                    counter++;
                }
            }
            cout << endl << "Count: " << counter << endl;
        } else if (k == 4) {
            int a;
            cout << "Enter a number to compare:";
            cin >> a;
            int counter = 0;
            quickSort(arrSorted, 100);
            for (int i: arrSorted) if (i < a) counter++;
            cout << "Number of values less than entered: " << counter << endl;
        } else if (k == 5) {
            int b;
            cout << "Enter a number to compare:";
            cin >> b;
            int counter = 0;
            quickSort(arrSorted, 100);
            for (int i: arrSorted) if (i > b) counter++;
            cout << "Number of values greater than entered: " << counter << endl;
        } else if (k == 6) {
            int a;
            cout << "Enter a search value:";
            cin >> a;
            quickSort(arrSorted, 100);
            cout << (binarySearch(arrSorted, 100, a) ? "Entered value exists" : "Entered value does not exist") << endl;
            chrono::time_point binarySearchStart = std::chrono::high_resolution_clock::now();
            binarySearch(arrSorted, 100, a);
            chrono::time_point binarySearchEnd = std::chrono::high_resolution_clock::now();
            cout << "Binary search time: " <<
                 chrono::duration_cast<chrono::microseconds>(binarySearchEnd - binarySearchStart).count() << endl;
            chrono::time_point bruteForceStart = std::chrono::high_resolution_clock::now();
            bruteForce(arrValues, 100, a);
            chrono::time_point bruteForceEnd = std::chrono::high_resolution_clock::now();
            cout << "Brute force time: " <<
                 chrono::duration_cast<chrono::microseconds>(bruteForceEnd - bruteForceStart).count() << endl;
        } else if (k == 7) {
            int a, b;
            cout << "Enter indexes of elements separated by a space:";
            cin >> a >> b;
            while (!(a >= 0 && a < 100 && b >= 0 && b < 100)) {
                cout << "Wrong index!" << endl << "The index must be between 0 and 99:";
                cin >> a >> b;
            }
            chrono::time_point start = std::chrono::high_resolution_clock::now();
            int t = arrValues[a];
            arrValues[a] = arrValues[b];
            arrValues[b] = t;
            chrono::time_point end = std::chrono::high_resolution_clock::now();
            cout << "Elements are swapped" << endl << "Time: "
                 << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
        } else cout << "Such option does not exist!" << endl;
    }
}

int *quickSort(int *arr, const int SIZE) {
    double mean = 0;
    for (int i = 0; i < SIZE; ++i) mean += abs(arr[i]);
    mean /= SIZE;
    int refNum = 0, refNumIndex;
    for (int i = 0; i < SIZE; ++i) {
        if (abs(abs(arr[i]) - abs(mean)) < abs(abs(refNum) - abs(mean))) {
            refNum = arr[i];
            refNumIndex = i;
        }
    }
    int countOfLower = 0, countOfHigher = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (i != refNumIndex) {
            if (arr[i] >= refNum) {
                countOfHigher++;
            } else countOfLower++;
        }
    }

    int lowerValues[countOfLower];
    int higherValues[countOfHigher];
    int j = 0, k = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (i != refNumIndex) {
            if (arr[i] >= refNum) {
                higherValues[j] = arr[i];
                j++;
            } else {
                lowerValues[k] = arr[i];
                k++;
            }
        }
    }
    if (countOfLower > 2) {
        quickSort(lowerValues, countOfLower);
    } else if (countOfLower == 2) {
        if (lowerValues[0] > lowerValues[1]) {
            int t = lowerValues[0];
            lowerValues[0] = lowerValues[1];
            lowerValues[1] = t;
        }
    }
    if (countOfHigher > 2) {
        quickSort(higherValues, countOfHigher);
    } else if (countOfHigher == 2) {
        if (higherValues[0] > higherValues[1]) {
            int t = higherValues[0];
            higherValues[0] = higherValues[1];
            higherValues[1] = t;
        }
    }
    for (int i = 0; i < countOfLower; ++i) arr[i] = lowerValues[i];
    arr[countOfLower] = refNum;
    for (int i = countOfLower + 1; i < SIZE; ++i) arr[i] = higherValues[i - countOfLower - 1];
    return arr;
}

bool binarySearch(int *arr, const int SIZE, int value) {
    int s = int(ceil(SIZE / 2.0));
    int middleNum = arr[s - 1];
    int len = SIZE;
    while (len > 2) {
        if (value < middleNum) {
            s -= int(ceil(len / 4.0));
            middleNum = arr[s - 1];
            len = int(ceil(len / 2.0));
        } else if (value > middleNum) {
            s += int(ceil(len / 4.0));
            middleNum = arr[s - 1];
            len -= int(ceil(len / 2.0));;
        } else return true;
    }
    for (int i = s - len; i < s + len; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool bruteForce(int *arr, const int SIZE, int value) {
    for (int i = 0; i < SIZE; ++i) if (arr[i] == value) return true;
    return false;
}

void findMinMax(int *arr, const int SIZE) {
    chrono::time_point start = std::chrono::high_resolution_clock::now();
    int min = 999, max = -999;
    for (int i = 0; i < SIZE; ++i) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    chrono::time_point end = std::chrono::high_resolution_clock::now();
    cout << "Max value: " << max << " Min value: " << min << " Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
}