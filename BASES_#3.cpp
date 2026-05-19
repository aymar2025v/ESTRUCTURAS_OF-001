
// convertir un numero de base cualquiera a base 10

#include <iostream>
using namespace std;

int convertirABaseDecimal(int numeroACombertir, int baseOrigen) {
    int r = 0;
    int b = 1;

    while (numeroACombertir != 0) {
        int digito = numeroACombertir % 10;

        if (digito >= baseOrigen) {
            return -1;  // Código de error
        }

        r = r + digito * b;
        numeroACombertir /= 10;
        b = b * baseOrigen;
    }

    return r;
}

// nose xd
bool validarBaseOrigen(int base) {
    return (base >= 2 && base <= 10);
}

int main() {
    

    int numeroB;
    int baseO;

    cout << "ingrese la base origen: ";
    cin >> baseO;
    cout << "ingrese el numero a convertir: "; 
    cin >> numeroB;

    int resultado = convertirABaseDecimal(numeroB, baseO);

    if (resultado != -1) {
        cout << numeroB << " en base " << baseO << " = " << resultado << " en decimal";
    }
    else {
        cout << "Error: El numero contiene digitos invalidos para base " << baseO;
    }

    return 0;
}
