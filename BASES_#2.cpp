
// de base 10 a culaquier base

#include <iostream>
using namespace std;

int convertirDecimalABaseN(int numero, int base) {
    int digitos[32];
    int i = 0;

    while (numero > 0) {
        digitos[i] = numero % base;
        numero /= base;
        i++;
    }

    int resultado = 0;

    for (int j = i - 1; j >= 0; j--) {
        resultado = resultado * 10 + digitos[j];
    }

    return resultado;
}

int main() {
    int numero = 77;
    int base = 3;

    int resultado = convertirDecimalABaseN(numero, base);

    cout << "El numero " << numero << " en base " << base << " es: " << resultado;

    return 0;
}