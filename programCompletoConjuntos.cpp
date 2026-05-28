
// Programa que elimina duplicados y los ordena usando el metodo Burbuja
// Ademas realiza las operaciones: 
// -unión, intersección, diferencia A-B y B-A.
// considerando como conjunto universal A U B, 
// imprime el complemento de A y el complemento de B.

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void ordenarBurbuja(int arreglo[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                int aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
}

int eliminarDuplicados(int arreglo[], int tam) {
    if (tam == 0 || tam == 1) 
        return tam;
    
    int nuevoTam = 0;
    for (int i = 0; i < tam; i++) {
        if (i == tam - 1 || arreglo[i] != arreglo[i + 1]) {
            arreglo[nuevoTam] = arreglo[i];
            nuevoTam++;
        }
    }
    return nuevoTam;
}

void imprimirArreglo(int arreglo[], int tam) {
    if (tam == 0) {
        cout << "{}" << endl;
        return;
    }
    cout << "{";
    for (int i = 0; i < tam; i++) {
        if (i < tam - 1)
            cout << arreglo[i] << ", ";
        else
            cout << arreglo[i] << "}" << endl;
    }
}

int operarUnion(int conjuntoA[], int tamA, int conjuntoB[], int tamB, int resultado[]) {
    int indiceA = 0, indiceB = 0, indiceResultado = 0;
    
    while (indiceA < tamA && indiceB < tamB) {
        if (conjuntoA[indiceA] < conjuntoB[indiceB]) {
            resultado[indiceResultado++] = conjuntoA[indiceA++];
        } else if (conjuntoB[indiceB] < conjuntoA[indiceA]) {
            resultado[indiceResultado++] = conjuntoB[indiceB++];
        } else {
            resultado[indiceResultado++] = conjuntoA[indiceA++];
            indiceB++; 
        }
    }
    while (indiceA < tamA) 
        resultado[indiceResultado++] = conjuntoA[indiceA++];
        
    while (indiceB < tamB) 
        resultado[indiceResultado++] = conjuntoB[indiceB++];
    
    return indiceResultado;
}

int operarInterseccion(int conjuntoA[], int tamA, int conjuntoB[], int tamB, int resultado[]) {
    int indiceA = 0, indiceB = 0, indiceResultado = 0;
    
    while (indiceA < tamA && indiceB < tamB) {
        if (conjuntoA[indiceA] < conjuntoB[indiceB]) {
            indiceA++;
        } else if (conjuntoB[indiceB] < conjuntoA[indiceA]) {
            indiceB++;
        } else {
            resultado[indiceResultado++] = conjuntoA[indiceA++];
            indiceB++;
        }
    }
    return indiceResultado;
}

int operarDiferencia(int conjuntoA[], int tamA, int conjuntoB[], int tamB, int resultado[]) {
    int indiceA = 0, indiceB = 0, indiceResultado = 0;
    
    while (indiceA < tamA && indiceB < tamB) {
        if (conjuntoA[indiceA] < conjuntoB[indiceB]) {
            resultado[indiceResultado++] = conjuntoA[indiceA++];
        } else if (conjuntoB[indiceB] < conjuntoA[indiceA]) {
            indiceB++;
        } else {
            indiceA++;
            indiceB++;
        }
    }
    while (indiceA < tamA) 
        resultado[indiceResultado++] = conjuntoA[indiceA++];
    
    return indiceResultado;
}

int main() {
    
    int n1, n2;

    // ENTRADA DE DATOS
    cout << "\nIngrese el tamaño del conjunto A: ";
    cin >> n1;
    int conjuntoA[n1]; 
    cout << "Ingrese los " << n1 << " números de A: ";
    for (int i = 0; i < n1; i++) cin >> conjuntoA[i];

    cout << "\nIngrese el tamaño del conjunto B: ";
    cin >> n2;
    int conjuntoB[n2];
    cout << "Ingrese los " << n2 << " números de B: ";
    for (int i = 0; i < n2; i++) cin >> conjuntoB[i];


    ordenarBurbuja(conjuntoA, n1);
    int tA = eliminarDuplicados(conjuntoA, n1);

    ordenarBurbuja(conjuntoB, n2);
    int tB = eliminarDuplicados(conjuntoB, n2);

    int maxTam = tA + tB;
    int resultadoUnion[maxTam];
    int resultadoInterseccion[maxTam];
    int resultadoDifAB[maxTam];
    int resultadoDifBA[maxTam];

    int tUnion = operarUnion(conjuntoA, tA, conjuntoB, tB, resultadoUnion);
    int tInterseccion = operarInterseccion(conjuntoA, tA, conjuntoB, tB, resultadoInterseccion);
    int tDifAB = operarDiferencia(conjuntoA, tA, conjuntoB, tB, resultadoDifAB);
    int tDifBA = operarDiferencia(conjuntoB, tB, conjuntoA, tA, resultadoDifBA);

    cout << "\n================== RESULTADOS =====================\n" << endl;
    cout << "===== conjuntos ordenados y sin duplicado =====\n";
    cout << "A = "; imprimirArreglo(conjuntoA, tA);
    cout << "B = "; imprimirArreglo(conjuntoB, tB);
    
    cout << "\n=== operaciones ===\n";
    cout << "A U B = "; imprimirArreglo(resultadoUnion, tUnion);
    cout << "A o B = "; imprimirArreglo(resultadoInterseccion, tInterseccion);
    cout << "A - B = "; imprimirArreglo(resultadoDifAB, tDifAB);
    cout << "B - A = "; imprimirArreglo(resultadoDifBA, tDifBA);
    
    cout << "\n=== complementos ===\n";
    cout << "A' = "; imprimirArreglo(resultadoDifBA, tDifBA);
    cout << "B' = "; imprimirArreglo(resultadoDifAB, tDifAB);

    return 0;
}
