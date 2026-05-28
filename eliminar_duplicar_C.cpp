#include <iostream>

// Función para ordenar usando Burbuja Estándar
void ordenarBurbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

// Función para eliminar duplicados de un arreglo ordenado
int eliminarDuplicados(int arr[], int n) {
    if (n == 0 || n == 1) return n;

    int nuevoTamano = 0;
    for (int i = 0; i < n; i++) {
        if (i == n - 1 || arr[i] != arr[i + 1]) {
            arr[nuevoTamano] = arr[i];
            nuevoTamano++;
        }
    }
    return nuevoTamano;
}

// Función para imprimir el arreglo
void imprimirArreglo(int arr[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int n1, n2;

    // --- ENTRADA DEL CONJUNTO 1 ---
    std::cout << "Ingrese la cantidad de elementos del Conjunto 1: ";
    std::cin >> n1;
    int conjunto1[n1]; // Arreglo de tamaño dinámico en tiempo de ejecución (VLA)
    
    std::cout << "Ingrese los " << n1 << " numeros del Conjunto 1:\n";
    for (int i = 0; i < n1; i++) {
        std::cin >> conjunto1[i];
    }

    // --- ENTRADA DEL CONJUNTO 2 ---
    std::cout << "\nIngrese la cantidad de elementos del Conjunto 2: ";
    std::cin >> n2;
    int conjunto2[n2];
    
    std::cout << "Ingrese los " << n2 << " numeros del Conjunto 2:\n";
    for (int i = 0; i < n2; i++) {
        std::cin >> conjunto2[i];
    }

    // --- PROCESAMIENTO DEL CONJUNTO 1 ---
    ordenarBurbuja(conjunto1, n1);
    int tamanoLimpio1 = eliminarDuplicados(conjunto1, n1);

    // --- PROCESAMIENTO DEL CONJUNTO 2 ---
    ordenarBurbuja(conjunto2, n2);
    int tamanoLimpio2 = eliminarDuplicados(conjunto2, n2);

    // --- SALIDA DE RESULTADOS ---
    std::cout << "\n================ RESULTADOS ================\n";
    std::cout << "Conjunto 1 ordenado y sin duplicados: ";
    imprimirArreglo(conjunto1, tamanoLimpio1);

    std::cout << "Conjunto 2 ordenado y sin duplicados: ";
    imprimirArreglo(conjunto2, tamanoLimpio2);

    return 0;
}
