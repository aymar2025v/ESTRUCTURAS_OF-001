#include <iostream>

bool esBaseValida(int base) {
    return base >= 2 && base <= 10;
}

// Convierte la parte entera (cadena en base origen) a decimal.
// Devuelve true si hay error (dígito inválido).
bool enteroBaseN_a_Decimal(const char* entero, int baseOrigen, int& resultado) {
    resultado = 0;
    for (int i = 0; entero[i] != '\0'; i++) {
        char c = entero[i];
        if (c < '0' || c > '9' || (c - '0') >= baseOrigen)
            return true;
        int digito = c - '0';
        resultado = resultado * baseOrigen + digito;
    }
    return false;
}

// Convierte la parte fraccionaria (cadena en base origen) a decimal.
// Devuelve true si hay error.
bool fraccionBaseN_a_Decimal(const char* fraccion, int baseOrigen, double& resultado) {
    resultado = 0.0;
    for (int i = 0; fraccion[i] != '\0'; i++) {
        char c = fraccion[i];
        if (c < '0' || c > '9' || (c - '0') >= baseOrigen)
            return true;
        int digito = c - '0';
        resultado = (resultado + digito) / baseOrigen;
    }
    return false;
}

// Convierte un entero decimal (positivo) a cadena en baseDestino.
// La cadena queda en orden correcto (sin invertir después).
void enteroDecimal_a_BaseM(int valor, int baseDestino, char* resultado) {
    int i = 0;
    if (valor == 0) {
        resultado[i++] = '0';
    }
    else {
        char temp[32];
        int j = 0;
        while (valor > 0) {
            temp[j++] = '0' + (valor % baseDestino);
            valor /= baseDestino;
        }
        // Invertir
        for (int k = j - 1; k >= 0; k--) {
            resultado[i++] = temp[k];
        }
    }
    resultado[i] = '\0';
}

// Convierte la parte fraccionaria decimal a cadena en baseDestino.
// Se detiene cuando la parte fraccionaria es casi 0 o se alcanzan maxDigitos.
void fraccionDecimal_a_BaseM(double fraccion, int baseDestino, char* resultado, int maxDigitos = 10) {
    int i = 0;
    while (fraccion > 1e-9 && i < maxDigitos) {
        fraccion *= baseDestino;
        int digito = (int)fraccion;
        resultado[i++] = '0' + digito;
        fraccion -= digito;
    }
    resultado[i] = '\0';
}

int main() {
    char numero[64];
    int baseOrigen, baseDestino;

    std::cout << "Numero en base origen: ";
    std::cin >> numero;
    std::cout << "Base origen (2-10): ";
    std::cin >> baseOrigen;
    std::cout << "Base destino (2-10): ";
    std::cin >> baseDestino;

    // Validar bases
    if (!esBaseValida(baseOrigen) || !esBaseValida(baseDestino)) {
        std::cout << "Error: ambas bases deben estar entre 2 y 10." << std::endl;
        return 1;
    }

    // Detectar signo
    bool negativo = false;
    int inicio = 0;
    if (numero[0] == '-') {
        negativo = true;
        inicio = 1;
    }

    // Localizar el punto decimal
    int posPunto = -1;
    for (int i = inicio; numero[i] != '\0'; i++) {
        if (numero[i] == '.') {
            posPunto = i;
            break;
        }
    }

    // Separar parte entera
    char entero[64];
    int iEnt = 0;
    if (posPunto == inicio) { // caso ".algo"
        entero[iEnt++] = '0';
    }
    else {
        int i = inicio;
        while (i < posPunto && numero[i] != '\0') {
            entero[iEnt++] = numero[i++];
        }
    }
    entero[iEnt] = '\0';

    // Separar parte fraccionaria
    char fraccion[64];
    int iFrac = 0;
    if (posPunto != -1) {
        int i = posPunto + 1;
        while (numero[i] != '\0') {
            fraccion[iFrac++] = numero[i++];
        }
    }
    fraccion[iFrac] = '\0';

    // Convertir a decimal
    int decimalEntero;
    if (enteroBaseN_a_Decimal(entero, baseOrigen, decimalEntero)) {
        std::cout << "Error: parte entera contiene digitos no validos." << std::endl;
        return 1;
    }

    double decimalFraccion;
    if (fraccionBaseN_a_Decimal(fraccion, baseOrigen, decimalFraccion)) {
        std::cout << "Error: parte fraccionaria contiene digitos no validos." << std::endl;
        return 1;
    }

    // Caso especial: cero exacto
    if (decimalEntero == 0 && decimalFraccion == 0.0) {
        std::cout << "Resultado: 0" << std::endl;
        return 0;
    }

    double valorAbs = decimalEntero + decimalFraccion;
    int parteEntera = (int)valorAbs;
    double parteFracc = valorAbs - parteEntera;

    // Convertir a la base destino
    char resEntero[64], resFraccion[64];
    enteroDecimal_a_BaseM(parteEntera, baseDestino, resEntero);
    fraccionDecimal_a_BaseM(parteFracc, baseDestino, resFraccion);

    // Mostrar resultado
    std::cout << "Resultado: ";
    if (negativo && (parteEntera > 0 || resFraccion[0] != '\0'))
        std::cout << '-';
    std::cout << resEntero;
    if (resFraccion[0] != '\0')
        std::cout << '.' << resFraccion;
    std::cout << std::endl;

    return 0;
}