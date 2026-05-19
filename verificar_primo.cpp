#include <iostream>
using namespace std;

bool esPrimo(int n, int divisor = 2) {
    
    if (n <= 1) {
        return false;  
    }
    if (n == 2) {
        return true;   
    }
    if (n % divisor == 0) {
        return false;  
    }
    if (divisor * divisor > n) {
        return true;   
    }

    return esPrimo(n, divisor + 1);
}

int main() {
    int numero;
    cout << "Ingrese un numero para verificar si es primo: ";
    cin >> numero;

    if (esPrimo(numero)) {
        cout << numero << " ES primo" << endl;
    }
    else {
        cout << numero << " NO es primo" << endl;
    }

    return 0;
}