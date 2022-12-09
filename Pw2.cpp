#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

int *quickSort(int *, int);

bool binarySearch(int *, int, int);

bool bruteForce(int *, int, int);

void findMinMax(int *, int);

int main() {
    srand(time(0));
    int arrValues[100], arrSorted[100];
    for (int i = 0; i < 100; ++i) arrValues[i] = rand() % (99 + 99 + 1) - 99;
    for (int i = 0; i < 100; ++i) arrSorted[i] = arrValues[i];
    cout << "Array created: ";
    for (int i = 0; i < 20; ++i) cout << " " << arrValues[i];
    cout << "... " << endl;

    while (true) {
        string option;
        cin >> option;
        if (option == "0") {
            return 0;
        } else if (option == "1") {
            for (int i = 0; i < 100; ++i) arrSorted[i] = arrValues[i];

            time_point start = high_resolution_clock::now();
            quickSort(arrSorted, 100);
            time_point end = high_resolution_clock::now();

            cout << "Array sorted: ";
            for (int i = 0; i < 20; ++i) cout << " " << arrSorted[i];
            cout << "... ";

            cout << "Time: " << duration_cast<nanoseconds>(end - start).count() << endl;
        } else if (option == "2") {
            cout << "Original array: ";
            findMinMax(arrValues, 100);

            cout << "Sorted array: ";
            quickSort(arrSorted, 100);
            findMinMax(arrSorted, 100);
        } else if (option == "3") {
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
        } else if (option == "4") {
            int a;
            cout << "Enter a number to compare:";
            cin >> a;

            int counter = 0;
            quickSort(arrSorted, 100);
            for (int i: arrSorted) if (i < a) counter++;

            cout << "Number of values less than entered: " << counter << endl;
        } else if (option == "5") {
            int b;
            cout << "Enter a number to compare:";
            cin >> b;

            int counter = 0;
            quickSort(arrSorted, 100);
            for (int i: arrSorted) if (i > b) counter++;

            cout << "Number of values greater than entered: " << counter << endl;
        } else if (option == "6") {
            int a;
            cout << "Enter a search value:";
            cin >> a;

            quickSort(arrSorted, 100);
            cout << (binarySearch(arrSorted, 100, a) ? "Entered value exists" : "Entered value does not exist") << endl;

            time_point binarySearchStart = high_resolution_clock::now();
            binarySearch(arrSorted, 100, a);
            time_point binarySearchEnd = high_resolution_clock::now();
            cout << "Binary search time: " <<
                 duration_cast<nanoseconds>(binarySearchEnd - binarySearchStart).count() << endl;

            time_point bruteForceStart = high_resolution_clock::now();
            bruteForce(arrValues, 100, a);
            time_point bruteForceEnd = high_resolution_clock::now();
            cout << "Brute force time: " <<
                 duration_cast<nanoseconds>(bruteForceEnd - bruteForceStart).count() << endl;
        } else if (option == "7") {
            int a, b;
            cout << "Enter indexes of elements separated by a space:";
            cin >> a >> b;

            while (!(a >= 0 && a < 100 && b >= 0 && b < 100)) {
                cout << "Wrong index!" << endl << "The index must be between 0 and 99:";
                cin >> a >> b;
            }

            time_point start = high_resolution_clock::now();
            int t = arrValues[a];
            arrValues[a] = arrValues[b];
            arrValues[b] = t;
            time_point end = high_resolution_clock::now();

            cout << "Elements are swapped" << endl << "Time: "
                 << duration_cast<nanoseconds>(end - start).count() << endl;
        } else if (option == "8") {
            int x, arrValuesCopy[100];
            for (int i = 0; i < 100; ++i) arrValuesCopy[i] = arrValues[i];
            cout << "Enter value for decrease: ";
            cin >> x;
            for (int i = 0; i < 100; ++i) if (i % 2 == 0) arrValuesCopy[i] -= x;

            cout << "Values reduced: ";
            for (int i = 0; i < 20; ++i) cout << " " << arrValuesCopy[i];
            cout << "... \n\n";

            int randVal = rand() % (9 - 1 + 1) + 1;
            for (int i = 0; i < 100; ++i) if (i % 2 == 0) arrValuesCopy[i] *= randVal;

            cout << "Each even element was multiplied by a random number equal to " << randVal << ":" << endl;
            for (int i = 0; i < 20; ++i) cout << " " << arrValuesCopy[i];
            cout << "... \n\n";

            int evenCount = 0, oddCount = 0;
            for (int i = 0; i < 100; ++i) {
                if (i % 2 == 0 && arrValuesCopy[i] % 2 == 0) evenCount++;
                if (i % 2 != 0 && arrValuesCopy[i] % 2 != 0) oddCount++;
            }
            cout << "Count of even elements with even indexes: " << evenCount << endl;
            cout << "Count of odd elements with odd indexes: " << oddCount << endl << endl;

            for (int i = 1; i < 10; ++i) {
                int counter = 0;
                for (int j: arrValuesCopy) if (j % i == 0) counter++;
                cout << "Count of values that are evenly divisible by " << i << ": " << counter << endl;
            }
        } else cout << "Such option does not exist!" << endl;
    }
}

int *quickSort(int *arr, int size) {
    double mean = 0;
    for (int i = 0; i < size; ++i) mean += abs(arr[i]);
    mean /= size;
    int refNum = 0, refNumIndex;
    for (int i = 0; i < size; ++i) {
        if (abs(abs(arr[i]) - abs(mean)) < abs(abs(refNum) - abs(mean))) {
            refNum = arr[i];
            refNumIndex = i;
        }
    }
    int countOfLower = 0, countOfHigher = 0;
    for (int i = 0; i < size; ++i) {
        if (i != refNumIndex) {
            if (arr[i] >= refNum) {
                countOfHigher++;
            } else countOfLower++;
        }
    }

    int *lowerValues = new int[countOfLower];
    int *higherValues = new int[countOfHigher];
    int j = 0, k = 0;
    for (int i = 0; i < size; ++i) {
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
    for (int i = countOfLower + 1; i < size; ++i) arr[i] = higherValues[i - countOfLower - 1];
    return arr;
}

bool binarySearch(int *arr, int size, int value) {
    int middleNumIndex = int(ceil(size / 2.0));
    int middleNumValue = arr[middleNumIndex - 1];
    while (size > 2) {
        if (value < middleNumValue) {
            middleNumIndex -= int(ceil(size / 4.0));
            middleNumValue = arr[middleNumIndex - 1];
            size = int(ceil(size / 2.0));
        } else if (value > middleNumValue) {
            middleNumIndex += int(ceil(size / 4.0));
            middleNumValue = arr[middleNumIndex - 1];
            size -= int(ceil(size / 2.0));;
        } else return true;
    }
    if (arr[middleNumIndex - 1] == value) return true;
    return false;
}

bool bruteForce(int *arr, int size, int value) {
    for (int i = 0; i < size; ++i) if (arr[i] == value) return true;
    return false;
}

void findMinMax(int *arr, int size) {
    time_point start = high_resolution_clock::now();
    int min = 999, max = -999;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    time_point end = high_resolution_clock::now();

    cout << "Max value: " << max << " Min value: " << min << " Time: "
         << duration_cast<nanoseconds>(end - start).count() << endl;
}