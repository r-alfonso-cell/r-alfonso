//Julian Andres Lizalda Aristizabal y Pool Alexander Delgado Palacios
#include <iostream>
#include <cstdlib> // Esto es para malloc y free
using namespace std;


// Estructura del nodo que representa a un producto
struct nodo {
    int id;         // ID del producto
    char nombre[30];   // Nombre del producto (hasta 30 caracteres)
    nodo *sig;         // Puntero al siguiente nodo en la lista
};


// Punteros globales para manipular la lista
nodo *cab = NULL, *aux = NULL, *aux2 = NULL;
int contadorID = 1;


// Función para agregar un nuevo producto al final de la lista
void agregarProducto() {
    // Asignación dinámica de memoria para el nuevo nodo
    aux = (nodo *) malloc(sizeof(nodo));
    if (aux == NULL) {  // Verifica si la asignación de memoria fue exitosa
        cout << "Error: no se pudo asignar memoria." << endl;
        return;
    }

    cout << "Ingrese el nombre del producto: ";
    cin >> aux->nombre;

    aux->id = contadorID++;

    aux->sig = NULL;  // El nuevo nodo no tiene siguiente (es el último)

    // Si la lista está vacía, el nuevo nodo será el primer nodo (cabeza de la lista)
    if (cab == NULL) {
        cab = aux;
    } else {
        // Si la lista no está vacía, recorre la lista hasta el final
        aux2 = cab;
        while (aux2->sig != NULL) {
            aux2 = aux2->sig;
        }
        aux2->sig = aux;  // Añade el nuevo nodo al final
    }
}


// Función para mostrar todos los productos registrados en la lista
void mostrarProducto() {
    
    if (cab == NULL) {
        cout << "La lista está vacía." << endl;
        return;
    }
    // Si la lista no está vacía, recorre y muestra todos los productos
    for (aux = cab; aux != NULL; aux = aux->sig) {
        cout << "ID: " << aux->id << " | Nombre: " << aux->nombre << endl;
    }
}


// Función para buscar un producto en la lista por su ID
int buscarProducto() {
    int seed;
    cout << "Digite el ID del producto a buscar: ";
    cin >> seed;

    // Recorre la lista buscando un nodo con el mismo ID
    for (aux = cab; aux != NULL; aux = aux->sig) {
        if (aux->id == seed) {
            
            cout << "Producto encontrado: " << aux->nombre << endl;
            return 1;  // Producto encontrado
        }
    }
    cout << "Producto no encontrado." << endl;
    return 0;  
}


// Función para eliminar un producto de la lista por su ID
void eliminarProducto() {
    int id;
    cout << "Digite el ID del producto a eliminar: ";
    cin >> id;

    if (cab == NULL) {
        cout << "La lista está vacía, no se puede eliminar." << endl;
        return;
    }

    // Si el primer nodo es el que se desea eliminar
    if (cab->id == id) {
        aux = cab;  // Almacena el nodo a eliminar
        cab = cab->sig;  // Actualiza la cabeza de la lista al siguiente nodo
        free(aux);  // Libera la memoria del nodo eliminado
        cout << "Producto eliminado correctamente." << endl;
        return;
    }

    // Si el nodo a eliminar no es el primero, recorre la lista buscando el nodo a eliminar
    aux = cab;
    while (aux->sig != NULL && aux->sig->id != id) {
        aux = aux->sig;
    }

    // Si no se encuentra el producto
    if (aux->sig == NULL) {
        cout << "Producto no encontrado." << endl;
    } else {
        // Si se encuentra el producto, ajusta el puntero para eliminarlo
        aux2 = aux->sig;
        aux->sig = aux->sig->sig;  // Desenlaza el nodo de la lista
        free(aux2);  // Libera la memoria del nodo eliminado
        cout << "Producto eliminado correctamente." << endl;
    }
}


// Función para contar la cantidad de productos en la lista
int contarProductos() {
    int contador = 0;
    // Recorre la lista y cuenta los nodos
    for (aux = cab; aux != NULL; aux = aux->sig) {
        contador++;  // Incrementa el contador por cada nodo
    }
    return contador;  
}


// Función para modificar el nombre de un producto por su ID
void modificarNombreProducto() {
    int id;
    cout << "Digite el ID del producto cuyo nombre desea modificar: ";
    cin >> id;

    for (aux = cab; aux != NULL; aux = aux->sig) {
        if (aux->id == id) {
            
            cout << "Producto encontrado: " << aux->nombre << endl;
            cout << "Ingrese el nuevo nombre para el producto: ";
            cin >> aux->nombre;  // Solicita el nuevo nombre y lo actualiza
            cout << "Nombre del producto modificado correctamente." << endl;
            return;
        }
    }

    
    cout << "Producto no encontrado." << endl;
}


// Función para liberar la memoria ocupada por la lista
void liberarMemoria() {
    aux = cab;
    // Recorre la lista liberando la memoria de cada nodo
    while (aux != NULL) {
        aux2 = aux->sig;  // Almacena el siguiente nodo
        free(aux);  // Libera la memoria del nodo actual
        aux = aux2;  // Avanza al siguiente nodo
    }
    cab = NULL;  // Pone la cabeza de la lista en NULL
    cout << "Memoria liberada correctamente." << endl;
}


int main() {
    int opc;
    do {
        cout << "\n==== MENÚ ====\n";
        cout << "1. Añadir producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto\n";
        cout << "4. Eliminar producto\n";
        cout << "5. Contar productos registrados\n";
        cout << "6. Modificar nombre del producto\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opc;
        
        switch(opc) {
            case 1:
                agregarProducto();  
                break;
            case 2:
                mostrarProducto();  
                break;
            case 3:
                buscarProducto();  
                break;
            case 4:
                eliminarProducto();  
                break;
            case 5:
                cout << "Cantidad de productos registrados: " << contarProductos() << endl; 
                break;
            case 6:
                modificarNombreProducto();  
                break;
            case 7:
                cout << "Saliendo del programa..." << endl;  
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;  
                break;
        }
    } while(opc != 7);  
    
    liberarMemoria();  
    return 0;
}