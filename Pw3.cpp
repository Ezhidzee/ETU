#include <iostream>
#include <thread>
#include <iomanip>

using namespace std;

void printMatrix(int **, int, bool = 1);

void clearMatrix(int **, int);

void spiralMatrix(int **, int);

void snakeMatrix(int **, int);

void rotateMatrix(int **, int, char);

void sortMatrix(int **, int);

void increaseMatrix(int **, int, int);

int main() {
    srand(time(0));
    int N;
    cout << "Enter N(6, 8 or 10):" << "\n";
    cin >> N;
    while (N != 6 && N != 8 && N != 10) {
        cout << "Wrong N value, try again" << "\n";
        cin >> N;
    }
    int **matrix = new int *[N];
    for (int **cur = matrix, **end = cur + N - 1; cur <= end; cur++) *cur = new int[N];
    string fillType;
    cout << "Choose how to fill the array(a or b):" << endl;
    cin >> fillType;
    while (fillType != "a" && fillType != "b") {
        cout << "Wrong value, try again(a, b)" << endl;
        cin >> fillType;
    }
    clearMatrix(matrix, N);
    if (fillType == "a") {
        spiralMatrix(matrix, N);
    } else snakeMatrix(matrix, N);

    string rotateOption;
    cout << "Choose how to rotate matrix(a, b, c, d):" << endl;
    cin >> fillType;
    while (fillType != "a" && fillType != "b" && fillType != "c" && fillType != "d") {
        cout << "Wrong value, try again(a, b)" << endl;
        cin >> fillType;
    }
    cout << "Rotated matrix: " << '\n';
    rotateMatrix(matrix, N, fillType[0]);
    cout << '\n' << "Sorted matrix: " << '\n';
    sortMatrix(matrix, N);
    cout << '\n' << "Enter a value to increase matrix elements: ";
    int k;
    cin >> k;
    increaseMatrix(matrix, N, k);
    system("Pause");
}

void printMatrix(int **matrix, int N, bool clear) {
    if (clear) system("cls");
    for (int **curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int *curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            cout << setw(3) << *curj;
            if (curj != endj) cout << " ";
        }
        cout << "\n";
    }
    std::this_thread::sleep_for(0.1s);
}

void clearMatrix(int **matrix, int N) {
    for (int **curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int *curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj = 0;
}

void spiralMatrix(int **matrix, int N) {
    printMatrix(matrix, N);
    int lineNum = 0;
    for (int j = 0; j < N / 2; ++j) {
        for (int *curi = *(matrix + lineNum) + lineNum, *endi = curi + N - 2 * lineNum; curi < endi; curi++) {
            *curi = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
        for (int **curi = matrix + lineNum + 1, **endi = matrix + N - 2 - lineNum; curi <= endi; curi++) {
            *(*curi + N - lineNum - 1) = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
        for (int *curi = *(matrix + N - lineNum - 1) + N - lineNum - 1, *endi = curi - N + 1 + 2 * lineNum; curi > endi; curi--) {
            *curi = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
        for (int **curi = matrix + N - 1 - lineNum, **endi = matrix + lineNum + 1; curi >= endi; curi--) {
            *(*curi + lineNum) = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
        lineNum++;
    }
}

void snakeMatrix(int **matrix, int N) {
    printMatrix(matrix, N);
    for (int lineNum = 0; lineNum < N / 2; ++lineNum) {
        for (int **curi = matrix, **endi = matrix + N - 1; curi <= endi; curi++) {
            *(*curi + lineNum * 2) = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
        for (int **curi = matrix + N - 1, **endi = matrix; curi >= endi; curi--) {
            *(*curi + lineNum * 2 + 1) = rand() % N * N + 1;
            printMatrix(matrix, N);
        }
    }
}

void rotateMatrix(int **matrix, int N, char option) {
    int **a = new int *[N / 2], **b = new int *[N / 2], **c = new int *[N / 2], **d = new int *[N / 2], ***arr = new int **[4];
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
    for (int ***i = arr, ***iEnd = arr + 3; i <= iEnd; i++)
        for (int **cur = *i, **end = cur + N / 2 - 1; cur <= end; cur++) *cur = new int[N / 2];

    for (int **curi = matrix, **endi = curi + N / 2 - 1, **curArray = a; curi <= endi; curi++, curArray++)
        for (int *curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int **curi = matrix, **endi = curi + N / 2 - 1, **curArray = b; curi <= endi; curi++, curArray++)
        for (int *curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int **curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = c; curi <= endi; curi++, curArray++)
        for (int *curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    for (int **curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = d; curi <= endi; curi++, curArray++)
        for (int *curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curArrayJ = *curj;

    int **pa, **pb, **pc, **pd;
    if (option == 'a') {
        pa = c; pb = a; pc = d; pd = b;
    } else if (option == 'b') {
        pa = d; pb = c; pc = b; pd = a;
    } else if (option == 'c') {
        pa = c; pb = d; pc = a; pd = b;
    } else pa = b; pb = a; pc = d; pd = c;
    for (int **curi = matrix, **endi = curi + N / 2 - 1, **curArray = pa; curi <= endi; curi++, curArray++)
        for (int *curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int **curi = matrix, **endi = curi + N / 2 - 1, **curArray = pb; curi <= endi; curi++, curArray++)
        for (int *curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int **curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = pc; curi <= endi; curi++, curArray++)
        for (int *curj = *curi, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    for (int **curi = matrix + N / 2, **endi = curi + N / 2 - 1, **curArray = pd; curi <= endi; curi++, curArray++)
        for (int *curj = *curi + N / 2, *endj = curj + N / 2 - 1, *curArrayJ = *curArray; curj <= endj; curj++, curArrayJ++)
            *curj = *curArrayJ;

    printMatrix(matrix, N, 0);
}

void sortMatrix(int **matrix, int N) {
    int *arr = new int [N * N];
    int i = 0;
    for (int **curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int *curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            *(arr + i) = *curj;
            i++;
        }
    }
    bool isChanged = 1;
    while (isChanged) {
        isChanged = 0;
        for (int *j = arr, *jEnd = j + (N * N) - 2; j <= jEnd; j++) {
                if (*j > *(j + 1)) {
                    isChanged = 1;
                    int t = *(j + 1);
                    *(j + 1) = *j;
                    *j = t;
                }
        }
    }

    i = 0;
    for (int **curi = matrix, **endi = curi + N - 1; curi <= endi; curi++) {
        for (int *curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) {
            *curj = *(arr + i);
            i++;
        }
    }
    printMatrix(matrix, N, 0);
}

void increaseMatrix(int **matrix, int N, int k) {
    for (int **curi = matrix, **endi = curi + N - 1; curi <= endi; curi++)
        for (int *curj = *curi, *endj = curj + N - 1; curj <= endj; curj++) *curj += k;
    printMatrix(matrix, N, 0);
}