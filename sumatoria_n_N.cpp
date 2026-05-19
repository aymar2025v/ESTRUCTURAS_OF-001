// 1 + 1 + 1 + 1 + 1 = 5

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void sumarNaturales() {

    int n;
    cout << "ingrese un numero mayor que 0: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error, intente de nuevo." << endl;
        return;
    }

    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;

        if (i < n) {
            cout << i << " + ";
        }
        else {
            cout << i;
        }
    }

    cout << " = " << suma;
}

int main()
{

    sumarNaturales();

    return 0;
}
