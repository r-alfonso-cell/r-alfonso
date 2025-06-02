#include <iostream>
#include <cstring>
#include <cstdlib>  // para malloc y free
using namespace std;

struct pelicula {
    char nombre[50];
    char genero[30];
    float dinero;
    int fecha;
    struct pelicula *izq;
    struct pelicula *der;
};

struct peli {
    char nombre[50];
    char genero[30];
    float dinero;
    int fecha;
    struct peli *sig;
};

pelicula* f1 = NULL;
pelicula* f2 = NULL;
pelicula* f3 = NULL;

char pelib[50];
char gen[30];

struct pelicula *raiz = NULL, *aux, *aux2;
struct peli *cab = NULL;

void posicionarpelicula() {
    if (aux->fecha <= aux2->fecha) {
        if (aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionarpelicula();
        } else {
            aux2->izq = aux;
        }
    } else {
        if (aux2->der != NULL) {
            aux2 = aux2->der;
            posicionarpelicula();
        } else {
            aux2->der = aux;
        }
    }
}

void adicionarpelicula() {
    aux = (struct pelicula*) malloc(sizeof(struct pelicula));
    aux->izq = aux->der = NULL;
    cout << "Ingrese el nombre de la pelicula: ";
    cin.ignore();
    cin.getline(aux->nombre, 50);
    cout << "Ingrese el genero de la pelicula: ";
    cin.getline(aux->genero, 30);
    cout << "Ingrese el año en el que salio la pelicula: ";
    cin >> aux->fecha;
    cout << "Ingrese el valor de recaudo de la pelicula en millones de dolares: ";
    cin >> aux->dinero;

    if (raiz == NULL) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionarpelicula();
    }
}

int preorden(struct pelicula* nuevaRaiz) {
    if (nuevaRaiz == NULL) return 0;

    cout << "Nombre: " << nuevaRaiz->nombre << endl;
    cout << "Género: " << nuevaRaiz->genero << endl;
    cout << "Año: " << nuevaRaiz->fecha << endl;
    cout << "Recaudación: " << nuevaRaiz->dinero << " millones\n\n";

    preorden(nuevaRaiz->izq);
    preorden(nuevaRaiz->der);
    return 0;
}

int inorden(struct pelicula* nuevaRaiz) {
    if (nuevaRaiz == NULL) return 0;

    inorden(nuevaRaiz->izq);
    cout << "Nombre: " << nuevaRaiz->nombre << endl;
    cout << "Género: " << nuevaRaiz->genero << endl;
    cout << "Año: " << nuevaRaiz->fecha << endl;
    cout << "Recaudación: " << nuevaRaiz->dinero << " millones\n\n";
    inorden(nuevaRaiz->der);
    return 0;
}

int balanceo(struct pelicula* nuevaRaiz) {
    if (nuevaRaiz == NULL) return 0;

    balanceo(nuevaRaiz->izq);

    struct peli* nuevo = (struct peli*) malloc(sizeof(struct peli));
    strcpy(nuevo->nombre, nuevaRaiz->nombre);
    strcpy(nuevo->genero, nuevaRaiz->genero);
    nuevo->dinero = nuevaRaiz->dinero;
    nuevo->fecha = nuevaRaiz->fecha;
    nuevo->sig = NULL;

    if (cab == NULL) {
        cab = nuevo;
    } else {
        struct peli* cursor = cab;
        while (cursor->sig != NULL) {
            cursor = cursor->sig;
        }
        cursor->sig = nuevo;
    }

    balanceo(nuevaRaiz->der);
    return 0;
}

void reconstruirArbolBalanceado() {
    // Paso 1: Contar elementos
    int total = 0;
    peli* tmp = cab;
    while (tmp != NULL) {
        total++;
        tmp = tmp->sig;
    }

    // Paso 2: Obtener nodo central
    int mitad = total / 2;
    peli* actual = cab;
    int i = 0;
    while (i < mitad && actual != NULL) {
        actual = actual->sig;
        i++;
    }

    if (actual == NULL) return;

    // Paso 3: Crear nueva raíz
    raiz = (struct pelicula*) malloc(sizeof(struct pelicula));
    strcpy(raiz->nombre, actual->nombre);
    strcpy(raiz->genero, actual->genero);
    raiz->dinero = actual->dinero;
    raiz->fecha = actual->fecha;
    raiz->izq = raiz->der = NULL;

    // Paso 4: Insertar el resto
    peli* cursor = cab;
    i = 0;
    while (cursor != NULL) {
        if (cursor != actual) {
            aux = (struct pelicula*) malloc(sizeof(struct pelicula));
            strcpy(aux->nombre, cursor->nombre);
            strcpy(aux->genero, cursor->genero);
            aux->dinero = cursor->dinero;
            aux->fecha = cursor->fecha;
            aux->izq = aux->der = NULL;

            aux2 = raiz;
            posicionarpelicula();
        }
        cursor = cursor->sig;
        i++;
    }
}

int postorden(struct pelicula* nuevaRaiz) {
    if (nuevaRaiz == NULL) return 0;

    postorden(nuevaRaiz->izq);
    postorden(nuevaRaiz->der);
    cout << "Nombre: " << nuevaRaiz->nombre << endl;
    cout << "Género: " << nuevaRaiz->genero << endl;
    cout << "Año: " << nuevaRaiz->fecha << endl;
    cout << "Recaudación: " << nuevaRaiz->dinero << " millones\n\n";
    return 0;
}

void buscarpornombre(pelicula* ayd) {
    if (ayd == NULL) return;

    if (strcmp(pelib, ayd->nombre) == 0) {
        cout << "Nombre: " << ayd->nombre << endl;
        cout << "Género: " << ayd->genero << endl;
        cout << "Año: " << ayd->fecha << endl;
        cout << "Recaudación: " << ayd->dinero << endl;
    }

    buscarpornombre(ayd->izq);
    buscarpornombre(ayd->der);
}

void procesogenero(pelicula* ayd) {
    if (ayd == NULL) return;

    if (strcmp(gen, ayd->genero) == 0) {
        cout << "Nombre: " << ayd->nombre << endl;
        cout << "Año: " << ayd->fecha << endl;
        cout << "Recaudación: " << ayd->dinero << endl;
    }

    procesogenero(ayd->izq);
    procesogenero(ayd->der);
}

void buscarporgenero(pelicula* raiz) {
    cout << "Ingrese el genero de película que desea buscar: ";
    cin.ignore();
    cin.getline(gen, 50);
    procesogenero(raiz);
}

void encontrarTresfracs(pelicula* raiz) {
    if (raiz == NULL) return;

    if (f1 == NULL || raiz->dinero < f1->dinero) {
        f3 = f2;
        f2 = f1;
        f1 = raiz;
    } else if (f2 == NULL || raiz->dinero < f2->dinero) {
        f3 = f2;
        f2 = raiz;
    } else if (f3 == NULL || raiz->dinero < f3->dinero) {
        f3 = raiz;
    }

    encontrarTresfracs(raiz->izq);
    encontrarTresfracs(raiz->der);
}

void buscarMayorIzquierdo(pelicula* nodo, pelicula** padreMayor, pelicula** mayor) {
    *padreMayor = nodo;
    *mayor = nodo->izq;
    while ((*mayor)->der != NULL) {
        *padreMayor = *mayor;
        *mayor = (*mayor)->der;
    }
}

pelicula* buscarConPadrePorNombre(pelicula* actual, char nombre[50], pelicula** padre) {
    if (actual == NULL) return NULL;

    if (strcmp(actual->nombre, nombre) == 0) {
        return actual;
    }

    *padre = actual;
    pelicula* encontrado = buscarConPadrePorNombre(actual->izq, nombre, padre);
    if (encontrado != NULL) return encontrado;

    *padre = actual;
    return buscarConPadrePorNombre(actual->der, nombre, padre);
}

void eliminarNodo() {
    if (raiz == NULL) {
        cout << "El árbol está vacío.\n";
        return;
    }

    char nombreEliminar[50];
    cout << "Ingrese el nombre de la película que desea eliminar: ";
    cin.ignore();
    cin.getline(nombreEliminar, 50);

    pelicula* padre = NULL;
    aux = buscarConPadrePorNombre(raiz, nombreEliminar, &padre);
    if (aux == NULL) {
        cout << "Película no encontrada.\n";
        return;
    }

    bool esHijoIzq = (padre != NULL && padre->izq == aux);

    if (aux->izq == NULL && aux->der == NULL) {
        if (padre == NULL) {
            raiz = NULL;
        } else if (esHijoIzq) {
            padre->izq = NULL;
        } else {
            padre->der = NULL;
        }
        free(aux);
    }
    else if (aux->izq == NULL || aux->der == NULL) {
        pelicula* hijo = (aux->izq != NULL) ? aux->izq : aux->der;
        if (padre == NULL) {
            raiz = hijo;
        } else if (esHijoIzq) {
            padre->izq = hijo;
        } else {
            padre->der = hijo;
        }
        free(aux);
    }
    else {
        pelicula* padreMayor = NULL;
        pelicula* mayor = NULL;
        buscarMayorIzquierdo(aux, &padreMayor, &mayor);

        strcpy(aux->nombre, mayor->nombre);
        strcpy(aux->genero, mayor->genero);
        aux->fecha = mayor->fecha;
        aux->dinero = mayor->dinero;

        if (padreMayor == aux) {
            aux->izq = mayor->izq;
        } else if (padreMayor->izq == mayor) {
            padreMayor->izq = mayor->izq;
        } else {
            padreMayor->der = mayor->izq;
        }

        free(mayor);
    }

    aux = NULL;
    cout << "Película eliminada correctamente.\n";
}

int main() {
    int opcion = 0;
    do {
        cout << "1. Registrar\n";
        cout << "2. Preorden\n";
        cout << "3. Inorden\n";
        cout << "4. Postorden\n";
        cout << "5. Buscar por nombre\n";
        cout << "6. Buscar por género\n";
        cout << "7. Mostrar 3 películas con menor recaudación\n";
        cout << "8. Eliminar película\n";
        cout << "9. Rebalancear árbol\n";
        cout << "10. Salir\n";
        cout << "Digite la opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: adicionarpelicula(); break;
            case 2: preorden(raiz); break;
            case 3: inorden(raiz); break;
            case 4: postorden(raiz); break;
            case 5:
                cout << "Ingrese el nombre de la película que desea buscar: ";
                cin.ignore();
                cin.getline(pelib, 50);
                buscarpornombre(raiz);
                break;
            case 6: buscarporgenero(raiz); break;
            case 7:
                f1 = f2 = f3 = NULL;
                encontrarTresfracs(raiz);
                if (f1) cout << "\n1. " << f1->nombre << " $" << f1->dinero << endl;
                if (f2) cout << "2. " << f2->nombre << " $" << f2->dinero << endl;
                if (f3) cout << "3. " << f3->nombre << " $" << f3->dinero << endl;
                break;
            case 8:
                eliminarNodo();
                break;
            case 9:
                cab = NULL;
                balanceo(raiz);
                reconstruirArbolBalanceado();
                cout << "Árbol reestructurado (balanceado).\n";
                break;
            case 10:
                cout << "Programa cerrado con éxito.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 10);

    return 0;
}
