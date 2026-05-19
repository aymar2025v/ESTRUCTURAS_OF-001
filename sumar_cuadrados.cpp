#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void sumarCuadrados() {

    int n;
    cout << "ingrese un numero mayor que 0: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error, intentalo de nuevo." << endl;
        return;
    }

    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i * i;

        if (i < n) {
            cout << i << "² + ";
        }
        else {
            cout << i;
        }
    }

    cout << "² = " << suma;
}

int main()
{

    sumarCuadrados();

    return 0;
}
