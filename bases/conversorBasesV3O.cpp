#include <iostream>
#include <string>

// ==========================================
// 1. FUNCIONES AUXILIARES DE CARACTERES
// ==========================================

int charAValor(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; 
}

char valorAChar(int v) {
    if (v >= 0 && v <= 9) return '0' + v;
    return 'A' + (v - 10);
}

void invertirCadena(std::string &s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

// ==========================================
// 2. FUNCIÓN DE VALIDACIÓN DE ENTRADAS
// ==========================================
bool validarEntradas(const std::string &num, int bOrigen, int bDestino) {
    if (bOrigen < 2 || bOrigen > 16 || bDestino < 2 || bDestino > 16) {
        std::cout << "\n[ERROR] Las bases deben estar estrictamente entre 2 y 16.\n";
        return false;
    }

    int inicio = (num[0] == '-') ? 1 : 0;
    
    // Validar si solo se ingresó un signo menos sin números
    if (num == "-") {
        std::cout << "\n[ERROR] Debe ingresar un numero valido despues del signo.\n";
        return false;
    }

    for (int i = inicio; i < num.length(); i++) {
        if (num[i] == '.' || num[i] == ',') continue; 
        
        int valorDigito = charAValor(num[i]);
        if (valorDigito == -1 || valorDigito >= bOrigen) {
            std::cout << "\n[ERROR] El digito '" << num[i] << "' no es valido para la base " << bOrigen << ".\n";
            return false;
        }
    }
    return true;
}

// ==========================================
// 3. FUNCIONES DE PROCESAMIENTO Y PARSEO
// ==========================================

std::string extraerParteEntera(const std::string &num, int inicio) {
    std::string enteraStr = "";
    for (int i = inicio; i < num.length(); i++) {
        if (num[i] == '.' || num[i] == ',') break;
        enteraStr += num[i];
    }
    return enteraStr;
}

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
// 4. PASO 1: CONVERSIÓN DE BASE ORIGEN A DECIMAL
// ==========================================

double convertirEnteraADecimal(const std::string &enteraStr, int base) {
    double resultado = 0.0;
    for (int i = 0; i < enteraStr.length(); i++) {
        resultado = resultado * base + charAValor(enteraStr[i]);
    }
    return resultado;
}

double convertirFraccionariaADecimal(const std::string &fracStr, int base) {
    double resultado = 0.0;
    double factorPosicional = 1.0 / base;
    for (int i = 0; i < fracStr.length(); i++) {
        resultado += charAValor(fracStr[i]) * factorPosicional;
        factorPosicional /= base;
    }
    return resultado;
}

// ==========================================
// 5. PASO 2: CONVERSIÓN DE DECIMAL A BASE DESTINO
// ==========================================

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
// 6. FUNCIÓN ORQUESTADORA
// ==========================================
std::string procesarConversion(std::string numero, int baseOrigen, int baseDestino) {
    bool esNegativo = (numero[0] == '-');
    int inicio = esNegativo ? 1 : 0;

    std::string parteEnteraStr = extraerParteEntera(numero, inicio);
    std::string parteFracStr = extraerParteFraccionaria(numero);

    double decimalEntero = convertirEnteraADecimal(parteEnteraStr, baseOrigen);
    double decimalFrac = convertirFraccionariaADecimal(parteFracStr, baseOrigen);
    double valorDecimalCompleto = decimalEntero + decimalFrac;

    long long enteraDecimal = (long long)valorDecimalCompleto;
    double fracDecimal = valorDecimalCompleto - enteraDecimal;

    std::string resEntero = convertirEnteraABaseM(enteraDecimal, baseDestino);
    std::string resFrac = convertirFraccionariaABaseM(fracDecimal, baseDestino);

    std::string resultadoFinal = esNegativo ? "-" : "";
    resultadoFinal += resEntero;
    if (resFrac.length() > 0) {
        resultadoFinal += "." + resFrac;
    }

    return resultadoFinal;
}

// ==========================================
// 7. BLOQUE PRINCIPAL CON BUCLE ININTERRUMPIDO
// ==========================================
int main() {
    std::string numeroOriginal;
    int baseOrigen, baseDestino;
    bool datosValidos = false;

    std::cout << "=== CONVERSOR ITERATIVO ESTRICTO [BASE 2 - 16] ===\n";

    // El bucle se ejecutará hasta que todas las condiciones se cumplan
    while (!datosValidos) {
        std::cout << "\n---------------------------------------------\n";
        std::cout << "Ingresa el numero: ";
        std::cin >> numeroOriginal;
        std::cout << "Base de origen (2-16): ";
        std::cin >> baseOrigen;
        std::cout << "Base de destino (2-16): ";
        std::cin >> baseDestino;

        // Comprobación lógica
        datosValidos = validarEntradas(numeroOriginal, baseOrigen, baseDestino);
        
        if (!datosValidos) {
            std::cout << "Por favor, intente ingresar los datos nuevamente.\n";
        }
    }

    // El flujo solo llega aquí si "datosValidos" es verdadero
    std::string resultado = procesarConversion(numeroOriginal, baseOrigen, baseDestino);
    std::cout << "\n[EXITO] El numero en base " << baseDestino << " es: " << resultado << "\n";

    return 0;
}
