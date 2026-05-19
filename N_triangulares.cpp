#include <iostream>
using namespace std;

int triangular(int n) {
    
    if (n == 1) {
        return 1;
    }
    // T(n) = n + T(n-1)
    return n + triangular(n - 1);
}

int main() {
    int n;
    cout << "Ingrese un numero para calcular el numero triangular: ";
    cin >> n;

    if (n < 1) {
        cout << "El numero debe ser positivo" << endl;
        return 1;
    }

    int resultado = triangular(n);
    cout << "El numero triangular T(" << n << ") = " << resultado << endl;

    return 0;
}