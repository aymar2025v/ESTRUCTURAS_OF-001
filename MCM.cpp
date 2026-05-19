#include <iostream>
using namespace std;

int MCD(int x, int y) {

    if (x < y) {
        int aux = x;
        x = y;
        y = aux;
    }

    if (y == 0) {
        return x;
    }

    return MCD(y, x % y);
}

// funcion para el MCM
int MCM(int x, int y) {
    return (x * y) / MCD(x, y);
}

int main() {

    int x, y;

    cout << "Ingrese dos numeros: ";
    cin >> x >> y;

    cout << "MCM = " << MCM(x, y);

    return 0;
}