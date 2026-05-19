
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

#include <iostream>
#include <string>

bool esBaseValida(int base) {
    return base >= 2 && base <= 10;
}

// Convierte parte entera (string, base origen) a decimal.
// Retorna true si hay error (dígito no válido).
bool enteroBaseN_a_Decimal(const std::string& entero, int base, int& resultado) {
    resultado = 0;
    for (int i = 0; i < entero.length(); i++) {
        char c = entero[i];
        if (c < '0' || c > '9' || (c - '0') >= base)
            return true;
        resultado = resultado * base + (c - '0');
    }
    return false;
}

// Convierte parte fraccionaria (string, base origen) a decimal.
// Retorna true si hay error.
bool fraccionBaseN_a_Decimal(const std::string& fraccion, int base, double& resultado) {
    resultado = 0.0;
    for (int i = 0; i < fraccion.length(); i++) {
        char c = fraccion[i];
        if (c < '0' || c > '9' || (c - '0') >= base)
            return true;
        int digito = c - '0';
        resultado = (resultado + digito) / base;
    }
    return false;
}

// Convierte entero decimal positivo a cadena en base destino.
// Construye la cadena ya en orden correcto (sin invertir ni push_back).
std::string enteroDecimal_a_BaseM(int valor, int base) {
    if (valor == 0) return "0";
    std::string resultado;
    while (valor > 0) {
        char digito = '0' + (valor % base);
        resultado = digito + resultado;   // insertar al inicio
        valor /= base;
    }
    return resultado;
}

// Convierte parte fraccionaria decimal a cadena en base destino.
// Se detiene si la fracción es casi 0 o se alcanzan maxDigitos dígitos.
std::string fraccionDecimal_a_BaseM(double fraccion, int base, int maxDigitos = 10) {
    std::string resultado;
    int contador = 0;
    while (fraccion > 1e-9 && contador < maxDigitos) {
        fraccion *= base;
        int digito = (int)fraccion;            // extraemos parte entera
        resultado = resultado + (char)('0' + digito);   // concatenar al final
        fraccion -= digito;
        contador++;
    }
    return resultado;
}

int main() {
    std::string numero;
    int baseOrigen, baseDestino;

    std::cout << "Numero en base origen: ";
    std::cin >> numero;
    std::cout << "Base origen (2-10): ";
    std::cin >> baseOrigen;
    std::cout << "Base destino (2-10): ";
    std::cin >> baseDestino;

    if (!esBaseValida(baseOrigen) || !esBaseValida(baseDestino)) {
        std::cout << "Error: ambas bases deben estar entre 2 y 10." << std::endl;
        return 1;
    }

    // Detectar signo
    bool negativo = false;
    int inicio = 0;
    if (numero.length() > 0 && numero[0] == '-') {
        negativo = true;
        inicio = 1;
    }

    // Buscar el punto decimal manualmente
    int posPunto = -1;
    for (int i = inicio; i < numero.length(); i++) {
        if (numero[i] == '.') {
            posPunto = i;
            break;
        }
    }

    // Construir parte entera (string)
    std::string entero;
    if (posPunto == -1) {
        // No hay punto: todo es parte entera
        for (int i = inicio; i < numero.length(); i++) {
            entero = entero + numero[i];
        }
    }
    else {
        // Hay punto
        if (posPunto == inicio) {
            entero = "0";   // caso ".algo"
        }
        else {
            for (int i = inicio; i < posPunto; i++) {
                entero = entero + numero[i];
            }
        }
    }

    // Construir parte fraccionaria (string)
    std::string fraccion;
    if (posPunto != -1 && posPunto + 1 < numero.length()) {
        for (int i = posPunto + 1; i < numero.length(); i++) {
            fraccion = fraccion + numero[i];
        }
    }

    // Convertir a decimal
    int decEntero;
    if (enteroBaseN_a_Decimal(entero, baseOrigen, decEntero)) {
        std::cout << "Error: parte entera con dígitos no válidos." << std::endl;
        return 1;
    }

    double decFraccion = 0.0;
    if (fraccion.length() > 0) {
        if (fraccionBaseN_a_Decimal(fraccion, baseOrigen, decFraccion)) {
            std::cout << "Error: parte fraccionaria con dígitos no válidos." << std::endl;
            return 1;
        }
    }

    double valorAbs = decEntero + decFraccion;
    if (decEntero == 0 && decFraccion == 0.0) {
        std::cout << "Resultado: 0" << std::endl;
        return 0;
    }

    int parteEntera = valorAbs;           // conversión implícita, trunca decimales
    double parteFracc = valorAbs - parteEntera;

    std::string resEntero = enteroDecimal_a_BaseM(parteEntera, baseDestino);
    std::string resFraccion = fraccionDecimal_a_BaseM(parteFracc, baseDestino);

    // Mostrar resultado
    std::cout << "Resultado: ";
    if (negativo && (parteEntera > 0 || resFraccion.length() > 0))
        std::cout << '-';
    std::cout << resEntero;
    if (resFraccion.length() > 0)
        std::cout << '.' << resFraccion;
    std::cout << std::endl;

    return 0;
}