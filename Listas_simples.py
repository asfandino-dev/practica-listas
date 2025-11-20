## Clase 1: Nodo
class Nodo:
    """
    Entidad fundamental de la lista enlazada.
    Almacena el dato (carga útil) y el puntero al sucesor.
    """
    def __init__(self, dato):
        self.dato = dato      # El dato almacenado en el elemento
        self.puntero = None   # Referencia al siguiente Nodo (el sucesor)

## Clase 2: ListaSimple (Estructura de Datos)
class ListaSimple:
    """
    Implementación de la Lista Simplemente Enlazada.
    Gestiona la secuencia de Nodos a través de la referencia 'cabeza'.
    """
    def __init__(self):
        # El único punto de acceso a la lista.
        self.cabeza = None 
        # Contador interno para mantener un registro del tamaño.
        self.tamanio = 0
# --- Operación 1: Inserción al Inicio ---
    def insertar_al_frente(self, dato):
        """
        Complejidad: O(1). 
        El tiempo de ejecución es constante, sin importar el tamaño de la lista.
        """
        nuevo_nodo = Nodo(dato)
        
        # 1. El nuevo nodo apunta a la actual cabeza.
        nuevo_nodo.puntero = self.cabeza
        
        # 2. La cabeza se reasigna al nuevo nodo.
        self.cabeza = nuevo_nodo
        self.tamanio += 1
        print(f"✅ Se insertó '{dato}' como nuevo elemento frontal (Cabeza).")


    # --- Operación 2: Inserción en una Posición k ---
    def insertar_en_posicion(self, dato, k):
        """
        Complejidad: O(k) o O(n) en el peor caso.
        Requiere recorrer hasta el nodo (k-1).
        """
        if k < 0 or k > self.tamanio:
            raise IndexError("Índice de posición fuera de los límites de la lista.")

        if k == 0:
            self.insertar_al_frente(dato)
            return

        nuevo_nodo = Nodo(dato)
        actual = self.cabeza
        contador = 0

        # 1. Recorrer hasta la posición anterior (k-1)
        while contador < k - 1:
            actual = actual.puntero
            contador += 1
        
        # 2. Re-enlazar: El nuevo nodo apunta al sucesor de 'actual'.
        nuevo_nodo.puntero = actual.puntero
        
        # 3. Re-enlazar: 'actual' (el nodo k-1) apunta al nuevo nodo.
        actual.puntero = nuevo_nodo
        self.tamanio += 1
        print(f"✅ Se insertó '{dato}' en la posición {k}.")


    # --- Operación 3: Eliminación por Valor ---
    def eliminar_por_valor(self, valor):
        """
        Complejidad: O(n). 
        En el peor caso (elemento al final o no existe), se recorre la lista completa.
        """
        actual = self.cabeza
        previo = None

        # 1. Búsqueda: Iterar hasta encontrar el valor o el final (None)
        while actual and actual.dato != valor:
            previo = actual
            actual = actual.puntero # Avance del puntero
        
        # Caso A: El valor no existe.
        if actual is None:
            print(f"❌ Error: El valor '{valor}' no se localizó en la lista.")
            return False

        # Caso B: Eliminación de la Cabeza (previo es None).
        if previo is None:
            self.cabeza = actual.puntero
        # Caso C: Eliminación de un nodo intermedio o final.
        else:
            # Bypass: El puntero del nodo previo salta al sucesor del nodo a eliminar.
            previo.puntero = actual.puntero

        self.tamanio -= 1
        print(f"🗑️ Se eliminó el elemento con el valor '{valor}'.")
        return True


    # --- Operación 4: Representación de la Lista (Método de Traversal) ---
    def __str__(self):
        """
        Implementación formal del método __str__ para impresión.
        Complejidad: O(n). Recorrido completo de la estructura.
        """
        actual = self.cabeza
        if actual is None:
            return "Lista vacía: []"

        elementos = []
        while actual:
            elementos.append(str(actual.dato))
            actual = actual.puntero # Avance del puntero

        return f"Tamaño: {self.tamanio} | Estructura: [ " + " -> ".join(elementos) + " -> Null ]"
# --- DEMOSTRACIÓN Y PRUEBA DE FUNCIONALIDAD ---

lista_universitaria = ListaSimple()

print("\n--- I. Pruebas de Inserción ---")
lista_universitaria.insertar_al_frente(30) # Lista: [30]
lista_universitaria.insertar_al_frente(20) # Lista: [20 -> 30]
lista_universitaria.insertar_al_frente(10) # Lista: [10 -> 20 -> 30]

print(lista_universitaria)

# Inserción en una posición específica (k=1)
lista_universitaria.insertar_en_posicion(15, 1) # Lista: [10 -> 15 -> 20 -> 30]
# Inserción al final (k=tamanio)
lista_universitaria.insertar_en_posicion(40, 4) # Lista: [10 -> 15 -> 20 -> 30 -> 40]

print(lista_universitaria)

print("\n--- II. Pruebas de Eliminación ---")
# Eliminar nodo intermedio
lista_universitaria.eliminar_por_valor(20) # Lista: [10 -> 15 -> 30 -> 40]

# Eliminar la cabeza
lista_universitaria.eliminar_por_valor(10) # Lista: [15 -> 30 -> 40]

# Intentar eliminar un valor que no existe
lista_universitaria.eliminar_por_valor(99) 

print(lista_universitaria)