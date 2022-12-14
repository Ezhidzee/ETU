#include "Pw1.h"

#include <iostream>

using namespace std;

void binaryRepresentation(int x) {
    int m = 1 << (sizeof(int) * 8 - 1);
    for (int i = 0; i < sizeof(int) * 8; i++) {
        cout << ((x & m) ? 1 : 0);
        if (i % 8 == 0) cout << " ";
        x <<= 1;
    }
}

void pw1() {
    cout << "int " << sizeof(int) << endl << "short int " << sizeof(short int) << endl << "long int " << sizeof(long int)
    << endl << "float " << sizeof(float) << endl << "double " << sizeof(double) << endl << "long double " << sizeof(long double)
    << endl << "char " << sizeof(char) << endl << "bool " << sizeof(bool) << endl << endl;

    int x;
    cout << "Enter an integer" << endl;
    cin >> x;
    binaryRepresentation(x);
    cout << endl << endl;

    union {
        int fa;
        float f;
    };
    cout << "Enter float:" << endl;
    cin >> f;
    binaryRepresentation(fa);
    cout << endl << endl;

    union {
        int arr[2];
        double d;
    };
    cout << "Enter double:" << endl;
    cin >> d;
    binaryRepresentation(arr[1]);
    binaryRepresentation(arr[0]);
    cout << endl << endl;
    
    int count;
    cout << "Enter the number of digits for binary shift:" << endl;
    cin >> count;
    x >>= count;
    fa >>= count;
    arr[0] >>= count;
    arr[1] >>= count;
    binaryRepresentation(x);
    cout << endl << endl;
    binaryRepresentation(fa);
    cout << endl << endl;
    binaryRepresentation(arr[1]);
    binaryRepresentation(arr[0]);
    cout << endl << endl;
}
