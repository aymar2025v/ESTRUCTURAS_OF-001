#include <iostream>
using namespace std;

bool esPrimo(int num, int divisor = 2) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % divisor == 0) return false;
    if (divisor * divisor > num) return true;
    return esPrimo(num, divisor + 1);
}

int main() {
    int n;

    cout << "ingrese el limite del rango (1 hasta n): ";
    cin >> n;

    if (n < 1) {
        cout << "el limite debe ser mayor o igual a 1" << endl;
        return 1;
    }

    cout << "numeros primos en el rango 1-" << n << ": ";

    for (int i = 2; i < n; i++) {
        if (esPrimo(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}