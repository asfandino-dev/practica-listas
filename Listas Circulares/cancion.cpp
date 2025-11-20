//listas enlazadas:
//listas enlazadas circularmente: el último nodo apunta al primero-genera un bucle
#include <iostream> //controla entradas y salidas
#include <string> //manejo de cadenas de texto
using namespace std;// Forma sencilla de manejar datos evita conlocar st::cout


struct Cancion {
    string nombre;        // Nombre de la canción
    Cancion* siguiente;   // Puntero a la siguiente canción

    // Constructor-creacion de canciones
    Cancion(string n) : nombre(n), siguiente(nullptr) {}
};



//Lista Circular de Canciones 
class ListaCanciones {
private://nada fuera de la clase puede acceder a estos datos
    Cancion* ultima;   // Apunta a la última canción

public:
    // Constructor: lista vacía
    ListaCanciones(): ultima(nullptr) {}

    // Verifica si la lista está vacía
    bool estaVacia() {//declaracion de funcion que devuelve un valor booleano
        return ultima == nullptr;//Retorna true o false dependiendo de la "condicion"
    }



    // Agregar una nueva canción al final
    void agregarCancion(string nombre) {//Funcion que no devuelve valor
        Cancion* nueva = new Cancion(nombre); //devuelve la direccion de memoria de la nueva cancion

        if (estaVacia()) {
            // Si la lista está vacía, el primer nodo apunta a sí mismo
            ultima = nueva;
            nueva->siguiente = nueva;//Dentro de l objeto que nueva apunta, se guardara direccion de nueva
        } else {
            // Inserta la nueva canción al final y actualiza punteros

            nueva->siguiente = ultima->siguiente;  // Apunta a la primera
            ultima->siguiente = nueva;             // La última apunta a la nueva
            ultima = nueva;                        // Actualizamos "última"
        }

        cout << "Cancion agregada: " << nombre << endl;
    }



    // Mostrar todas las canciones una vez
    void mostrarLista() {
        if (estaVacia()) {
            cout << "La lista de canciones esta vacia." << endl;
            return;
        }

        Cancion* actual = ultima->siguiente; // Empezamos desde la primera canción

        cout << "\n Lista de canciones:" << endl;
        do {
            cout << "- " << actual->nombre << endl;
            actual = actual->siguiente;//el valor de actual se va actualizado para que apunte a la siguiente cancion
        } while (actual != ultima->siguiente);
    }



    // Simular reproducción infinita (modo loop)
    void reproducirLoop(int repeticiones) {
        if (estaVacia()) {
            cout << "No hay canciones para reproducir." << endl;
            return;
        }

        Cancion* actual = ultima->siguiente; // Empezamos desde la primera
        cout << "\nReproduciendo en modo loop..." << endl;

        for (int i = 0; i < repeticiones; i++) {
            cout << "Reproduciendo...: " << actual->nombre << endl;
            actual = actual->siguiente; // Pasa a la siguiente canción
        }
    
    }

    int contarCanciones() {
        if (estaVacia()) {
            return 0;
        }

        int contador = 0;//declaramos la varible contador
        Cancion* actual = ultima->siguiente;//iniciammos desde el puntero de la primera cancion

        do {//Ayuda a recorrer toda la lista
            contador++;
            actual = actual->siguiente;
        } while (actual != ultima->siguiente);

        return contador;
    }


    void agregar_posicion(string nombre, int posicion) {
        if (posicion <= 0) {
            cout << "Posicion invalida.Es posible que halla ingresado un valor negativo o en su defecto 0" << endl;
            return;
        }
        posicion--;//para sea en terminos humano no interpretados
        Cancion* nueva = new Cancion(nombre);

        if (estaVacia()) {
            if (posicion == 0) {
                ultima = nueva;
                nueva->siguiente = nueva;

                cout << "Cancion agregada en posicion " << posicion+1 << ": " << nombre << endl;
            } else {
                cout << "Es una lista vacia sollo se puede colocar en la posicion 0." << endl;
                delete nueva;
            }

            return;
        }

        if (posicion == 0) {
            nueva->siguiente = ultima->siguiente;//-> esto significa campo siguiente a 
            ultima->siguiente = nueva;
            cout << "Cancion agregada en posicion " << posicion+1 << ": " << nombre << endl;
            return;
        }

        Cancion* actual = ultima->siguiente;
        for (int i = 0; i < posicion - 1; i++) {
            if (actual == ultima) {
                
                cout << "Posicion invalida.Posiblemente agregaste una posicion demasiado alta para la cantidad de canciones actuales:"<< contarCanciones()<< endl;
                delete nueva;
                return;
            }
            actual = actual->siguiente;//si no ha llegado al nodo correcto avanza de posicicón
        }

        nueva->siguiente = actual->siguiente;
        actual->siguiente = nueva;//nodo actual ahora apunta a la nueva cancion

        if (actual == ultima) {
            ultima = nueva; // Actualiza última si se agrega al final
        }

        cout << "Cancion agregada en posicion " << posicion+1 << ": " << nombre << endl;
    }

    void buscar_por_posicion(int posicion) {
        if (estaVacia() || posicion < 0) {
            cout << "No se encuentra la canción en dicha posicion.Posicion invalida o la lista esta vacia." << endl;
            return;
        }
        posicion--;//ajuste para empezar desde 1

        Cancion* actual = ultima->siguiente;
        for (int i = 0; i < posicion; i++) {
            if (actual == ultima) {
                cout << "No se encuentra cancion en dicha posicion. fuera de rango." << endl;
                return;
            }
            actual = actual->siguiente;
        }

        cout << "Cancion en posicion " << posicion+1 << ": " << actual->nombre << endl;
    }
    void eliminar_por_posicion(int posicion) {
        if (estaVacia() || posicion <= 0) {
            cout << "Posicion invalida o la lista esta vacia." << endl;
            return;
        }

        posicion--;  // Ajuste humano

        Cancion* actual = ultima->siguiente; // Primera canción
        Cancion* anterior = ultima;//Requerimos este para  controlar los punteros anteriores al que se va a eliminar

        
        if (posicion == 0) {//Eliminar la primera cancion
            // Si solo hay un nodo
            if (actual == ultima) {
                delete actual;
                ultima = nullptr;
            } else {
                anterior->siguiente = actual->siguiente;
                delete actual;
            }

            cout << "Cancion eliminada en posicion 1." << endl;
            return;
        }

        // Recorrer hasta encontrar la posición
        for (int i = 0; i < posicion; i++) {
            anterior = actual;
            actual = actual->siguiente;

            // Si damos la vuelta sin encontrar la posición → está fuera de rango
            if (anterior == ultima) {
                cout << "Posicion fuera de rango. Solo hay " << contarCanciones() << " canciones." << endl;
                return;
            }
        }

        // Caso 2: eliminar la última canción
        if (actual == ultima) {
            anterior->siguiente = actual->siguiente;
            delete actual;
            ultima = anterior;
            cout << "Cancion eliminada en posicion " << posicion+1 << "." << endl;
            return;
        }

        // Caso 3: eliminar una canción del medio
        anterior->siguiente = actual->siguiente;
        delete actual;

        cout << "Cancion eliminada en posicion " << posicion+1 << "." << endl;
    }


    // Destructor: liberar memoria, funcion especial, se ejecuta cuando el programa termina.
    ~ListaCanciones() {
        if (!estaVacia()) {
            Cancion* actual = ultima->siguiente;
            ultima->siguiente = nullptr; //Rompe el circulo ya que el puntero que apuntaba a la primera ahora apunta a null

            while (actual != nullptr) {
                Cancion* temp = actual;
                actual = actual->siguiente;
                cout << " Eliminando: " << temp->nombre << endl;
                delete temp;
            }
        }
    }
};



//Función principal
int main() {
    ListaCanciones lista;// automaticamente llama al constructor
    cout <<"--------- LISTAS CIRCULARES-----------"<< endl;
    cout << endl;


    cout <<"--------------------"<< endl;
    cout <<"METODO AGREGAR CANCIONES AL FINAL DE LA LISTA"<< endl;
    cout <<"--------------------"<< endl;
    cout << endl;
    lista.agregarCancion("Primeras veces - Morat");
    lista.agregarCancion("Arroyito - Fonseca");
    lista.agregarCancion("Golden Hour - jvke");
    lista.agregarCancion("Shape of You - Ed Sheeran");


    lista.mostrarLista();
    cout << endl;
    cout << endl;
    

    // Simulamos que el reproductor toca 10 canciones seguidas (loop circular)
    cout <<"--------------------"<< endl;
    cout <<"METODO REPRODUCIR EN LOOP CANCIONES"<< endl;
    cout <<"--------------------"<< endl;
    cout << endl;

    lista.reproducirLoop(10);
    cout << endl;
    cout << endl;

    cout <<"--------------------"<< endl;
    cout <<"METODO AGREGAR POR POSICION CANCIONES"<< endl;
    cout <<"--------------------"<< endl;
    cout << endl;
    lista.agregar_posicion("Soda pop - SajaBoys", 2);
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.agregar_posicion("Se me ocurre - Silvana Estrada", 1);//agrega al inicio
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.agregar_posicion("the door - Teddy Swims", 10); // Posición inválida
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.agregar_posicion(" - Silvana Estrada", 0);//POSION INVALIDA 0
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.agregar_posicion(" - Silvana Estrada", -60);//POSION INVALIDA 0
    lista.mostrarLista();
    cout << endl;
    cout << endl;


    cout <<"--------------------"<< endl;
    cout <<"METODO BUSCAR POR POSICION CANCIONES"<< endl;
    cout <<"--------------------"<< endl;

    lista.buscar_por_posicion(3);
    cout << endl;
    cout << endl;
    lista.buscar_por_posicion(10);
    cout << endl;
    cout << endl;
    lista.buscar_por_posicion(-5);//posicion invalida
    cout << endl;
    cout << endl;

    cout <<"--------------------"<< endl;
    cout <<"METODO ELIMINAR POR POSICION CANCIONES"<< endl;
    cout <<"--------------------"<< endl;
    lista.eliminar_por_posicion(1);//elimina la primera cancion
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.eliminar_por_posicion(4);//elimina una cancion del medio
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    lista.eliminar_por_posicion(10);//posicion fuera de rango
    lista.mostrarLista();
    cout << endl;
    cout << endl;
    cout <<"--------------------"<< endl;
    cout <<"DESTRUCTOR- ELIMINA LAS CANCIONES"<< endl;
    cout <<"--------------------"<< endl;
    return 0;// le indica al programa que todo fue un exito
}
