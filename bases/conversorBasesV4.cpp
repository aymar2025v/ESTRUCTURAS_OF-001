#include <iostream>
#include <string>

using namespace std;

int charAValor(char c) {
    
    if (c >= '0' && c <= '9') 
        return c - '0';
    if (c >= 'A' && c <= 'F') 
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') 
        return c - 'a' + 10;
    
    return -1; 
}

char valorAChar(int v) {
    
    if (v >= 0 && v <= 9) 
        return '0' + v;
        
    return 'A' + (v - 10);
}

void invertirCadena(string &s) {
    
    int n = s.length();
    
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

bool validarEntradas(const string &num, int bOrigen, int bDestino) {
    
    if (bOrigen < 2 || bOrigen > 16 || bDestino < 2 || bDestino > 16) {
        cout << "\n[ERROR] Las bases deben estar entre 2 y 16.\n";
        return false;
    }

    int inicio = (num[0] == '-') ? 1 : 0;
    
    if (num == "-") {
        cout << "\n[ERROR] Debe ingresar un numero valido despues del signo.\n";
        return false;
    }

    for (int i = inicio; i < num.length(); i++) {
        
        if (num[i] == '.' || num[i] == ',') 
            continue; 
        
        int valorDigito = charAValor(num[i]);
        
        if (valorDigito == -1 || valorDigito >= bOrigen) {
            cout << "\n[ERROR] El digito '" << num[i] << "' no es valido para la base " << bOrigen << endl;
            return false;
        }
    }
    return true;
}

string extraerParteEntera(const string &num, int inicio) {
    
    string enteraStr = "";
    
    for (int i = inicio; i < num.length(); i++) {
        if (num[i] == '.' || num[i] == ',') break;
        enteraStr += num[i];
    }
    return enteraStr;
}

string extraerParteFraccionaria(const string &num) {
    
    string fracStr = "";
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

double convertirEnteraADecimal(const string &enteraStr, int base) {
    
    double resultado = 0.0;
    
    for (int i = 0; i < enteraStr.length(); i++) {
        resultado = resultado * base + charAValor(enteraStr[i]);
    }
    return resultado;
}

double convertirFraccionariaADecimal(const string &fracStr, int base) {
    
    double resultado = 0.0;
    double factorPosicional = 1.0 / base;
    
    for (int i = 0; i < fracStr.length(); i++) {
        resultado += charAValor(fracStr[i]) * factorPosicional;
        factorPosicional /= base;
    }
    return resultado;
}

string convertirEnteraABaseM(long long valorEntero, int base) {
    
    if (valorEntero == 0) 
        return "0";
    
    string resultado = "";
    
    while (valorEntero > 0) {
        int residuo = valorEntero % base;
        resultado += valorAChar(residuo);
        valorEntero /= base;
    }
    
    invertirCadena(resultado);
    return resultado;
}

string convertirFraccionariaABaseM(double valorFrac, int base, int precision = 4) {
    
    string resultado = "";
    
    while (valorFrac > 0.00001 && precision > 0) {
        valorFrac *= base;
        int digito = (int)valorFrac;
        resultado += valorAChar(digito);
        valorFrac -= digito;
        precision--;
    }
    return resultado;
}

string procesarConversion(string numero, int baseOrigen, int baseDestino) {
    
    bool esNegativo = (numero[0] == '-');
    int inicio = esNegativo ? 1 : 0;

    string parteEnteraStr = extraerParteEntera(numero, inicio);
    string parteFracStr = extraerParteFraccionaria(numero);

    double decimalEntero = convertirEnteraADecimal(parteEnteraStr, baseOrigen);
    double decimalFrac = convertirFraccionariaADecimal(parteFracStr, baseOrigen);
    double valorDecimalCompleto = decimalEntero + decimalFrac;

    long long enteraDecimal = (long long)valorDecimalCompleto;
    double fracDecimal = valorDecimalCompleto - enteraDecimal;

    string resEntero = convertirEnteraABaseM(enteraDecimal, baseDestino);
    string resFrac = convertirFraccionariaABaseM(fracDecimal, baseDestino);

    string resultadoFinal = esNegativo ? "-" : "";
    resultadoFinal += resEntero;
    
    if (resFrac.length() > 0) {
        resultadoFinal += "." + resFrac;
    }

    return resultadoFinal;
}

int main() {
    
    string numeroOriginal;
    int baseOrigen;
    int baseDestino;
    bool datosValidos = false;

    cout << "=== CONVERSOR BASE 2 - 16 ===" << endl;

    while (!datosValidos) {
        cout << "\n---------------------------------------------\n";
        cout << "ingresa el numero: ";
        cin >> numeroOriginal;
        cout << "base de origen (2-16): ";
        cin >> baseOrigen;
        cout << "base de destino (2-16): ";
        cin >> baseDestino;

        datosValidos = validarEntradas(numeroOriginal, baseOrigen, baseDestino);
        
        if (!datosValidos) {
            std::cout << "intente ingresar los datos nuevamente." << endl;
        }
    }

    string resultado = procesarConversion(numeroOriginal, baseOrigen, baseDestino);
    cout << "\n[EXITO] El numero en base " << baseDestino << " es: " << resultado << endl;

    return 0;
}