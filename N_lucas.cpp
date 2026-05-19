#include <iostream>
using namespace std;

int fibonaci(int n) {
    
    if (n == 0) {
        return 2;  
    }
    if (n == 1) {
        return 1;  
    }

    // L(n) = L(n-1) + L(n-2)
    return fibonaci(n - 1) + fibonaci(n - 2);
}

int main() {
    int n;
    cout << "Ingrese el indice n para el numero de Lucas: ";
    cin >> n;

    if (n < 0) {
        cout << "El indice debe ser no negativo" << endl;
        return 1;
    }

    cout << "L(" << n << ") = " << fibonaci(n) << endl;

    for (int i = 0; i <= n; i++) {
        cout << fibonaci(i);
        if (i < n) cout << ", ";
    }
    cout << endl;

    return 0;
}