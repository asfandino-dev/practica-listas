#include <iostream>
using namespace std;

// Estructura del Nodo
struct Nodo {
    int dato;
    Nodo* anterior;
    Nodo* siguiente;

    Nodo(int valor) {
        dato = valor;
        anterior = nullptr;
        siguiente = nullptr;
    }
};


class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

public:

    ListaDoble() {
        cabeza = nullptr;
        cola = nullptr;
    }


    void añadir(int valor) {
        Nodo* nuevoNodo = new Nodo(valor);

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }

        cout << "Elemento " << valor << " anadido." << endl;

    }


    void eliminar(int valor) {
        if (cabeza == nullptr) {
            cout << "La lista está vacía." << endl;
            return;
        }

        Nodo* actual = cabeza;


        while (actual != nullptr && actual->dato != valor) {
            actual = actual->siguiente;
        }

        if (actual == nullptr) {
            cout << "Elemento " << valor << " no encontrado." << endl;
            return;
        }


        if (actual == cabeza && actual == cola) {

            cabeza = nullptr;
            cola = nullptr;
        } else if (actual == cabeza) {

            cabeza = cabeza->siguiente;
            cabeza->anterior = nullptr;
        } else if (actual == cola) {

            cola = cola->anterior;
            cola->siguiente = nullptr;
        } else {

            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
        }

        delete actual;
        cout << "Elemento " << valor << " eliminado." << endl;
    }


    void mostrar() {
        if (cabeza == nullptr) {
            cout << "La lista esta vacia." << endl;
            return;
        }

        Nodo* actual = cabeza;
        cout << "Elementos en la lista: ";
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }


    bool buscar(int valor) {
        Nodo* actual = cabeza;

        while (actual != nullptr) {
            if (actual->dato == valor) {
                cout << "Elemento " << valor << " en la lista" << endl;
                return true;
            }
            actual = actual->siguiente;
        }
        cout << "Elemento " << valor << " no encontrado" << endl;
        return false;
    }


    ~ListaDoble() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};


int main() {
    ListaDoble lista;





    lista.añadir(10);
    lista.añadir(20);
    lista.añadir(30);
    lista.añadir(40);


    lista.mostrar();


    lista.buscar(10);
    lista.buscar(80);



    lista.eliminar(20);
    lista.mostrar();
    lista.eliminar(80);
    lista.eliminar(10);
    lista.mostrar();

    lista.eliminar(40);
    lista.mostrar();

    lista.eliminar(30);
    lista.mostrar();


}