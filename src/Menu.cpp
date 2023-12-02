#include <iostream>

using namespace std;

void opcion1() {
    cout << "Has seleccionado la Opción 1." << endl;
}

void opcion2() {
    cout << "Has seleccionado la Opción 2." << endl;
}

void opcion3() {
    cout << "Has seleccionado la Opción 3." << endl;
}

int main() {
    int opcion;

    do {
        // Mostrar el menú
        cout << "Menú:" << endl;
        cout << "1. Opción 1" << endl;
        cout << "2. Opción 2" << endl;
        cout << "3. Opción 3" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";

        // Obtener la opción del usuario
        cin >> opcion;

        // Procesar la opción seleccionada
        switch (opcion) {
            case 1:
                opcion1();
                break;
            case 2:
                opcion2();
                break;
            case 3:
                opcion3();
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, selecciona una opción válida." << endl;
                break;
        }

    } while (opcion != 4);

    return 0;
}
