#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void sumarUnos() {

    int n;
    cout << "ingrese un numero entero mayor que 0: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error, intentalo de nuevo."<<endl;
        return;
    }

    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += 1;

        if (i < n) {
            cout << 1 << " + ";
        }
        else {
            cout << 1;
        }
    }

    cout << " = " << suma;
}

int main()
{

    sumarUnos();

    return 0;
}
