
#include <iostream>
#include <string>

using namespace std;

bool esBaseValida(int base) {
    return base >= 2 && base <= 10;
}

bool enteroBaseN_a_Decimal(const string& entero, int base, int& resultado) {
    resultado = 0;
    for (int i = 0; i < entero.length(); i++) {
        int digito = entero[i] - '0';
        if (digito < 0 || digito >= base)
        {
            return true;
        }
        resultado = resultado * base + digito;
    }
    return false;
}

bool fraccionBaseN_a_Decimal(const string& fraccion, int base, double& resultado) {
    resultado = 0.0;
    for (int i = 0; i < fraccion.length(); i++) {
        int digito = fraccion[i] - '0';
        if (digito < 0 || digito >= base)
            return true;
        resultado = (resultado + digito) / base;
    }
    return false;
}

string enteroDecimal_a_BaseM(int valor, int base) {
    if (valor == 0) {
        return "0";
    }
    string resultado;
    while (valor > 0) {
        char digito = '0' + (valor % base);
        resultado = digito + resultado;
        valor /= base;
    }
    return resultado;
}

string fraccionDecimal_a_BaseM(double fraccion, int base, int maxDigitos = 10) {
    string resultado;
    for (int i = 0; i < maxDigitos; i++) {
        fraccion *= base;
        int digito = (int)fraccion;
        resultado = resultado + (char)('0' + digito);
        fraccion -= digito;
        if (fraccion == 0.0)
            break;
    }
    return resultado;
}

int main() {
    string numero;
    int baseOrigen, baseDestino;

    cout << "Numero en base origen: ";
    cin >> numero;
    cout << "Base origen (2-10): ";
    cin >> baseOrigen;
    cout << "Base destino (2-10): ";
    cin >> baseDestino;

    if (!esBaseValida(baseOrigen) || !esBaseValida(baseDestino)) {
        cout << "Error: ambas bases deben estar entre 2 y 10." << endl;
        return 1;
    }

    bool negativo = false;
    int inicio = 0;
    if (numero.length() > 0 && numero[0] == '-') {
        negativo = true;
        inicio = 1;
    }

    int posPunto = -1;
    for (int i = inicio; i < numero.length(); i++) {
        if (numero[i] == '.') {
            posPunto = i;
            break;
        }
    }

    string entero;
    if (posPunto == -1) {
        for (int i = inicio; i < numero.length(); i++) {
            entero = entero + numero[i];
        }
    }
    else {
        if (posPunto == inicio) {
            entero = "0";
        }
        else {
            for (int i = inicio; i < posPunto; i++) {
                entero = entero + numero[i];
            }
        }
    }

    string fraccion;
    if (posPunto != -1 && posPunto + 1 < numero.length()) {
        for (int i = posPunto + 1; i < numero.length(); i++) {
            fraccion = fraccion + numero[i];
        }
    }

    int decEntero;
    if (enteroBaseN_a_Decimal(entero, baseOrigen, decEntero)) {
        cout << "Error: parte entera con dígitos no válidos." << endl;
        return 1;
    }

    double decFraccion = 0.0;
    if (fraccion.length() > 0) {
        if (fraccionBaseN_a_Decimal(fraccion, baseOrigen, decFraccion)) {
            cout << "Error: parte fraccionaria con dígitos no válidos." << endl;
            return 1;
        }
    }

    double valorAbs = decEntero + decFraccion;
    if (decEntero == 0 && decFraccion == 0.0) {
        cout << "Resultado: 0" << endl;
        return 0;
    }

    int parteEntera = valorAbs;
    double parteFracc = valorAbs - parteEntera;

    string resEntero = enteroDecimal_a_BaseM(parteEntera, baseDestino);
    string resFraccion = fraccionDecimal_a_BaseM(parteFracc, baseDestino);

    cout << "Resultado: ";
    if (negativo && (parteEntera > 0 || resFraccion.length() > 0))
        cout << '-';
    cout << resEntero;
    if (resFraccion.length() > 0)
        cout << '.' << resFraccion;

    return 0;
}