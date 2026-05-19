#include <iostream>
using namespace std;

int MCD(int x, int y) {

    // si x < y entonces intercambia
    if (x < y) {
        int aux = x;
        x = y;
        y = aux;
    }

    // caso base
    if (y == 0) {
        return x;
    }

    // r = x mod y
    int r = x % y;

    // llamada recursiva
    return MCD(y, r);
}

int main() {

    int x, y;

    cout << "Ingrese dos numeros: ";
    cin >> x >> y;

    cout << "MCD = " << MCD(x, y);

    return 0;
}