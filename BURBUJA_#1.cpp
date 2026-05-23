
#include <iostream>

void burbuja(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void imprimirArreglo(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
    
	int arreglo[5] = { 5, 2, 9, 1, 5 };
    int tam = sizeof(arreglo) / sizeof(arreglo[0]);   // cantidad de elementos: 5

	// otra forma de obtener el tamaño del arreglo
    int ultimo_indice = tam - 1;            // 4

	burbuja(arreglo, tam);
	std::cout << "Arreglo ordenado: ";
	imprimirArreglo(arreglo, tam);


    return 0;
}

