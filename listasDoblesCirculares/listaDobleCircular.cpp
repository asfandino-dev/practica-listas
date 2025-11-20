#include <iostream>
using namespace std;

// Nodo de la lista doble circular
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

// Clase Lista doble circular
class ListaDobleCircular {
private:
    Nodo* cabeza;

public:
    ListaDobleCircular() : cabeza(nullptr) {}

    // Insertar un nuevo nodo al final
    void insertar(int valor) {
        Nodo* nuevo = new Nodo(valor);

        if (cabeza == nullptr) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            Nodo* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
    }

    // Mostrar los elementos de la lista
    void mostrar() {
        if (cabeza == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }

        Nodo* actual = cabeza;
        cout << "Lista: ";
        do {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        } while (actual != cabeza);
        cout << endl;
    }

    // metodo buscar 
    Nodo* buscar(int valor) const {
        if (cabeza == nullptr) {
            return nullptr;  // lista vacía
        }

        Nodo* actual = cabeza;

        // Recorremos hasta volver a la cabeza
        do {
            if (actual->dato == valor) {
                cout<<"El valor "<< actual->dato <<" fue encontrado"<< endl;
                return actual;  // encontrado
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        cout << "El valor " << valor << " no fue encontrado" << endl;
        return nullptr;  // no se encontró
    }

    // Eliminar un nodo por valor
    void eliminar(int valor) {
        if (cabeza == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }

        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        // Buscar el nodo a eliminar
        do {
            if (actual->dato == valor) {
                if (actual == cabeza && actual->siguiente == cabeza) {
                    // Solo hay un nodo
                    cabeza = nullptr;
                } else {
                    if (actual == cabeza)
                        cabeza = cabeza->siguiente;

                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;
                }

                delete actual;
                cout << "Nodo con valor " << valor << " eliminado." << endl;
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        cout << "No se encontró el valor en la lista." << endl;
    }

    // Destructor para liberar memoria
    ~ListaDobleCircular() {
        if (cabeza == nullptr) return;

        Nodo* actual = cabeza;
        do {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);

        cabeza = nullptr;
    }
};

// Función principal
int main() {
    ListaDobleCircular lista;

    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);

    lista.mostrar();

    lista.eliminar(20);
    lista.mostrar();

    lista.eliminar(10);
    lista.mostrar();

    lista.buscar(30);
    lista.buscar(70);

    return 0;
}
