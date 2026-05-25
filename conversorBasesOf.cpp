

#include <iostream>
#include <string>

// ==========================================
// 1. FUNCIONES AUXILIARES DE CONVERSIÓN DE CARACTERES
// ==========================================

// Convierte un carácter alfanumérico a su valor entero equivalente
int charAValor(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

// Convierte un valor numérico entero a su carácter equivalente
char valorAChar(int v) {
    if (v >= 0 && v <= 9) return '0' + v;
    return 'A' + (v - 10);
}

// Invierte una cadena de texto de forma manual mediante punteros/índices
void invertirCadena(std::string &s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

// ==========================================
// 2. FUNCIONES DE PROCESAMIENTO Y PARSEO
// ==========================================

// Extrae la parte entera de una cadena saltando el signo si existe
std::string extraerParteEntera(const std::string &num, int inicio) {
    std::string enteraStr = "";
    for (int i = inicio; i < num.length(); i++) {
        if (num[i] == '.' || num[i] == ',') break;
        enteraStr += num[i];
    }
    return enteraStr;
}

// Extrae la parte fraccionaria de una cadena si existe el punto decimal
std::string extraerParteFraccionaria(const std::string &num) {
    std::string fracStr = "";
    bool puntoEncontrado = false;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '.' || num[i] == ',') {
            puntoEncontrado = true;
            continue;
        }
        if (puntoEncontrado) {
            fracStr += num[i];
        }
    }
    return fracStr;
}

// ==========================================
// 3. PASO 1: CONVERSIÓN DE BASE N A DECIMAL
// ==========================================

// Convierte la parte entera de Base N a Decimal usando multiplicación acumulativa
double convertirEnteraADecimal(const std::string &enteraStr, int base) {
    double resultado = 0.0;
    for (int i = 0; i < enteraStr.length(); i++) {
        resultado = resultado * base + charAValor(enteraStr[i]);
    }
    return resultado;
}

// Convierte la parte fraccionaria de Base N a Decimal dividiendo progresivamente
double convertirFraccionariaADecimal(const std::string &fracStr, int base) {
    double resultado = 0.0;
    double factorPosicional = 1.0 / base;
    for (int i = 0; i < fracStr.length(); i++) {
        resultado += charAValor(fracStr[i]) * factorPosicional;
        factorPosicional /= base; // Simula potencias negativas sin pow()
    }
    return resultado;
}

// ==========================================
// 4. PASO 2: CONVERSIÓN DE DECIMAL A BASE M
// ==========================================

// Convierte la parte entera decimal a Base M usando divisiones sucesivas
std::string convertirEnteraABaseM(long long valorEntero, int base) {
    if (valorEntero == 0) return "0";
    
    std::string resultado = "";
    while (valorEntero > 0) {
        int residuo = valorEntero % base;
        resultado += valorAChar(residuo);
        valorEntero /= base;
    }
    invertirCadena(resultado);
    return resultado;
}

// Convierte la parte fraccionaria decimal a Base M usando multiplicaciones sucesivas
std::string convertirFraccionariaABaseM(double valorFrac, int base, int precision = 4) {
    std::string resultado = "";
    while (valorFrac > 0.00001 && precision > 0) {
        valorFrac *= base;
        int digito = (int)valorFrac;
        resultado += valorAChar(digito);
        valorFrac -= digito;
        precision--;
    }
    return resultado;
}

// ==========================================
// 5. FUNCIÓN ORQUESTADORA PRINCIPAL
// ==========================================
std::string procesarConversion(std::string numero, int baseOrigen, int baseDestino) {
    // Detectar signo
    bool esNegativo = (numero[0] == '-');
    int inicio = esNegativo ? 1 : 0;

    // Segmentar sub-cadenas
    std::string parteEnteraStr = extraerParteEntera(numero, inicio);
    std::string parteFracStr = extraerParteFraccionaria(numero);

    // Convertir todo a Base 10 (Decimal)
    double decimalEntero = convertirEnteraADecimal(parteEnteraStr, baseOrigen);
    double decimalFrac = convertirFraccionariaADecimal(parteFracStr, baseOrigen);
    double valorDecimalCompleto = decimalEntero + decimalFrac;

    // Separar partes del decimal unificado
    long long enteraDecimal = (long long)valorDecimalCompleto;
    double fracDecimal = valorDecimalCompleto - enteraDecimal;

    // Convertir de Base 10 a la Base Destino
    std::string resEntero = convertirEnteraABaseM(enteraDecimal, baseDestino);
    std::string resFrac = convertirFraccionariaABaseM(fracDecimal, baseDestino);

    // Ensamblar respuesta final
    std::string resultadoFinal = esNegativo ? "-" : "";
    resultadoFinal += resEntero;
    if (resFrac.length() > 0) {
        resultadoFinal += "." + resFrac;
    }

    return resultadoFinal;
}

int main() {
    std::string numeroOriginal;
    int baseOrigen, baseDestino;

    std::cout << "=== CONVERSOR MODULAR DE BASE N A BASE M ===\n";
    std::cout << "Ingresa el numero: ";
    std::cin >> numeroOriginal;
    std::cout << "Base de origen (2-16): ";
    std::cin >> baseOrigen;
    std::cout << "Base de destino (2-16): ";
    std::cin >> baseDestino;

    std::string resultado = procesarConversion(numeroOriginal, baseOrigen, baseDestino);

    std::cout << "\nResultado en base " << baseDestino << ": " << resultado << "\n";

    return 0;
}
