#include <iostream>
using namespace std;

double armonico(int n) {

    if (n == 1) {
        return 1.0;
    }

    // H(n) = 1/n + H(n-1)
    return 1.0 / n + armonico(n - 1);
}

int main() {
    int n;
    cout << "Ingrese el valor de n para el numero armonico: ";
    cin >> n;

    if (n < 1) {
        cout << "n debe ser mayor o igual a 1" << endl;
        return 1;
    }

    cout << "H(" << n << ") = " << armonico(n) << endl;

    for (int i = 1; i <= n; i++) {
        cout << "H(" << i << ") = " << armonico(i) << endl;
    }

    return 0;
}