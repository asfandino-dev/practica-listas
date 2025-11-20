#include <iostream>
#include <stdexcept> // Para usar std::out_of_range

using namespace std;

// ===============================================
// Clase 1: Nodo (La unidad atómica)
// ===============================================
class Nodo {
public:
    int dato;        // Carga útil: el dato que almacena el nodo
    Nodo* puntero;   // El puntero que enlaza al nodo sucesor

    // Constructor
    Nodo(int valor) : dato(valor), puntero(nullptr) {}
};

// ===============================================
// Clase 2: ListaSimple (El administrador de la estructura)
// ===============================================
class ListaSimple {
private:
    Nodo* cabeza; // Puntero al primer nodo (punto de acceso)
    int tamanio;

public:
    // Constructor
    ListaSimple() : cabeza(nullptr), tamanio(0) {}

    // Destructor: Fundamental en C++ para liberar la memoria
    ~ListaSimple() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->puntero;
            delete actual; // Liberar la memoria del nodo actual
            actual = siguiente;
        }
    }

    // --- Operación 1: Inserción al Frente (O(1)) ---
    void insertarAlFrente(int valor) {
        Nodo* nuevo_nodo = new Nodo(valor); // Asignación dinámica de memoria

        // 1. El puntero del nuevo nodo apunta a la cabeza actual.
        nuevo_nodo->puntero = cabeza;

        // 2. La cabeza se reasigna al nuevo nodo.
        cabeza = nuevo_nodo;
        tamanio++;
        cout << "✅ Se insertó " << valor << " como nuevo elemento frontal." << endl;
    }

    // --- Operación 2: Inserción en una Posición k (O(n)) ---
    void insertarEnPosicion(int valor, int k) {
        // Validación de límites
        if (k < 0 || k > tamanio) {
            throw out_of_range("Error: Posición fuera de los límites de la lista.");
        }

        if (k == 0) {
            insertarAlFrente(valor);
            return;
        }

        Nodo* nuevo_nodo = new Nodo(valor);
        Nodo* actual = cabeza;
        int contador = 0;

        // 1. Recorrer hasta el nodo previo (posición k-1)
        while (contador < k - 1) {
            actual = actual->puntero;
            contador++;
        }

        // 2. Re-enlazar: El nuevo nodo apunta al sucesor de 'actual'.
        nuevo_nodo->puntero = actual->puntero;

        // 3. Re-enlazar: 'actual' (el nodo k-1) apunta al nuevo nodo.
        actual->puntero = nuevo_nodo;
        tamanio++;
        cout << "✅ Se insertó " << valor << " en la posición " << k << "." << endl;
    }

    // --- Operación 3: Eliminar por Valor (O(n)) ---
    bool eliminarPorValor(int valor) {
        Nodo* actual = cabeza;
        Nodo* previo = nullptr;

        // Búsqueda: Iterar hasta encontrar el valor o el final (nullptr)
        while (actual != nullptr && actual->dato != valor) {
            previo = actual;
            actual = actual->puntero;
        }

        // Caso A: El valor no existe.
        if (actual == nullptr) {
            cout << "❌ Error: El valor " << valor << " no se localizó." << endl;
            return false;
        }

        // Caso B: Eliminación de la Cabeza (previo es nullptr).
        if (previo == nullptr) {
            cabeza = actual->puntero;
        }
        // Caso C: Eliminación de un nodo intermedio o final.
        else {
            // Bypass: El puntero del nodo previo salta al sucesor del nodo a eliminar.
            previo->puntero = actual->puntero;
        }

        // Liberar la memoria del nodo eliminado
        delete actual; 
        tamanio--;
        cout << "🗑️ Se eliminó correctamente el valor " << valor << "." << endl;
        return true;
    }

    // --- Operación 4: Recorrido e Impresión (O(n)) ---
    void imprimirLista() {
        Nodo* actual = cabeza;
        cout << "\n📜 Estructura Actual (Tamanio: " << tamanio << "): [ ";

        if (actual == nullptr) {
            cout << "Lista Vacia ]" << endl;
            return;
        }

        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->puntero != nullptr) {
                cout << " -> ";
            }
            actual = actual->puntero; // Avance del puntero
        }
        cout << " -> Null ]" << endl;
    }
};

// ===============================================
// Bloque Principal de Demostración
// ===============================================
int main() {
    try {
        ListaSimple lista_universitaria;

        cout << "--- I. Pruebas de Inserción ---" << endl;
        lista_universitaria.insertarAlFrente(30);
        lista_universitaria.insertarAlFrente(20);
        lista_universitaria.insertarAlFrente(10); // Lista: [10 -> 20 -> 30]

        lista_universitaria.imprimirLista();

        // Inserción en una posición específica (k=1)
        lista_universitaria.insertarEnPosicion(15, 1);
        // Inserción al final (k=tamanio)
        lista_universitaria.insertarEnPosicion(40, 4); // Lista: [10 -> 15 -> 20 -> 30 -> 40]

        lista_universitaria.imprimirLista();

        cout << "\n--- II. Pruebas de Eliminación ---" << endl;
        // Eliminar nodo intermedio
        lista_universitaria.eliminarPorValor(20);

        // Eliminar la cabeza
        lista_universitaria.eliminarPorValor(10); 

        // Intentar eliminar un valor que no existe
        lista_universitaria.eliminarPorValor(99); 

        lista_universitaria.imprimirLista();

    } catch (const out_of_range& e) {
        cerr << "Excepción: " << e.what() << endl;
    }

    return 0;
}