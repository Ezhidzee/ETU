#include <iostream>
#include <conio.h>

#include "Pw1.h"
#include "Pw2.h"
#include "Pw3.h"
#include "Pw4.h"

using namespace std;

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_ESC = 27;

void updateMenu(int option) {
    system("cls");
    cout << "Practical work No. 1" << (option == 1 ? " <-" : "") << endl;
    cout << "Practical work No. 2" << (option == 2 ? " <-" : "") << endl;
    cout << "Practical work No. 3" << (option == 3 ? " <-" : "") << endl;
    cout << "Practical work No. 4" << (option == 4 ? " <-" : "") << endl;
}

void executeOption(int option) {
    system("cls");
    switch (option) {
        case 1:
            pw1();
            break;
        case 2:
            pw2();
            break;
        case 3:
            pw3();
            break;
        case 4:
            pw4();
            break;
    }
}

int main() {
    int key_code = 0, currentMenuItem = 1;
    updateMenu(currentMenuItem);
    while (1) {
        switch ((key_code = _getch())) {
            case KEY_UP:
                if (currentMenuItem != 1) updateMenu(--currentMenuItem);
                break;
            case KEY_DOWN:
                if (currentMenuItem != 4) updateMenu(++currentMenuItem);
                break;
            case KEY_ESC:
                return 0;
                break;
            case KEY_ENTER:
                executeOption(currentMenuItem);
                updateMenu(currentMenuItem);
                break;
        }
    }
}