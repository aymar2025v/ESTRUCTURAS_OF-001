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
    int n, contador = 0;

    cout << "Ingrese cuantos numeros primos desea generar: ";
    cin >> n;

    if (n < 1) {
        cout << "Debe ser un numero positivo" << endl;
        return 1;
    }

    cout << "Los primeros " << n << " numeros primos son: ";

    for (int i = 2; contador < n; i++) {
        if (esPrimo(i)) {
            cout << i << " ";
            contador++;
        }
    }
    cout << endl;

    return 0;
}