#include <iostream>
#include <cstring>
#include <malloc.h>
using namespace std;

struct nodo {
    char nombre[50];
    int anoR;
    char genero[30];
    double recaudacion;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *raiz = NULL, *aux, *aux2; 
char nombreBusqueda[50];
char nombreGenero[30];

struct nodo *m1 = NULL, *m2 = NULL , *m3 = NULL;

void posicionarPeli() {
    if(aux->anoR < aux2->anoR) {
        if(aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionarPeli();
        }
        else 
           aux2->izq = aux;
    } 
    else if(aux->anoR > aux2->anoR) {
        if(aux2->der != NULL) {
            aux2 = aux2->der;
            posicionarPeli();
        }
        else 
           aux2->der = aux;
    } else {
        if(aux2->izq == NULL) {
            aux2->izq = aux;
        } else {
            aux2 = aux2->izq;
            posicionarPeli();
        }
    }
}

void añadirPeli() {
    aux = (struct nodo *) malloc(sizeof(struct nodo));
    aux->izq = aux->der = NULL;
    
    cout << "Ingrese el nombre de la Pelicula: ";
    cin.ignore();
    cin.getline(aux->nombre, 50);
    
    cout << "Ingrese el año de realizacion: ";
    cin >> aux->anoR;
    
    cout << "Ingrese el genero: ";
    cin.ignore();
    cin.getline(aux->genero, 30);
    
    cout << "Ingrese la recaudación: ";
    cin >> aux->recaudacion;
    
    if(raiz == NULL) {
        raiz = aux;
        aux = NULL;
    } else {
        aux2 = raiz;
        posicionarPeli();
    }
}

void inorden(struct nodo *recursive) {
    if(recursive != NULL) {
        if(recursive->izq != NULL) {
            inorden(recursive->izq);
        }
            cout << "Nombre: " << recursive->nombre <<   " | Año: "  << recursive->anoR << " | Género: " << recursive->genero
            << " | Recaudación: $" << recursive->recaudacion << "M" << endl;
        if(recursive->der != NULL) {
            inorden(recursive->der);
        }
    }
}

void preorden(struct nodo *recursive) {
    if(recursive != NULL) {
            cout << "Nombre: " << recursive->nombre <<   " | Año: "  << recursive->anoR << " | Género: " << recursive->genero
            << " | Recaudación: $" << recursive->recaudacion << "M" << endl;
        if(recursive->izq != NULL) {
            preorden(recursive->izq);
        }
        if(recursive->der != NULL) {
            preorden(recursive->der);
        }
    }
}

void postorden(struct nodo *recursive) {
    if(recursive != NULL) {
        if(recursive->izq != NULL) {
            postorden(recursive->izq);
        }
        if(recursive->der != NULL) {
            postorden(recursive->der);
        }
            cout << "Nombre: " << recursive->nombre <<   " | Año: "  << recursive->anoR << " | Género: " << recursive->genero
            << " | Recaudación: $" << recursive->recaudacion << "M" << endl;
    }
}

void buscarPN(struct nodo *recursive) {
    if (recursive != NULL) {
        if (strcmp(recursive->nombre, nombreBusqueda) == 0) {
            cout << "Película encontrada:" << endl;
            cout << "Nombre: " << recursive->nombre <<   " | Año: "  << recursive->anoR << " | Género: " << recursive->genero
            << " | Recaudación: $" << recursive->recaudacion << "M" << endl;
        }

        buscarPN(recursive->izq);
        buscarPN(recursive->der);
    }
}

void mostrarPG(struct nodo *recursive) {
    if (recursive != NULL) {
        if (strcmp(recursive->genero, nombreGenero) == 0) {
            cout << "Pelicula: " << recursive->nombre << endl;
        }

        mostrarPG(recursive->izq);
        mostrarPG(recursive->der);
    }
}

void mostrar3Fr(struct nodo *recursive) {
    if (recursive != NULL) {
        mostrar3Fr(recursive->izq);

        if (m1 == NULL || recursive->recaudacion < m1->recaudacion) {
            m3 = m2;
            m2 = m1;
            m1 = recursive;
        } else if (m2 == NULL || recursive->recaudacion < m2->recaudacion) {
            m3 = m2;
            m2 = recursive;
        } else if (m3 == NULL || recursive->recaudacion < m3->recaudacion) {
            m3 = recursive;
        }

        mostrar3Fr(recursive->der);
    }
}

void liberarMemoria(struct nodo *recursive) {
    if(recursive != NULL) {
        liberarMemoria(recursive->izq);
        liberarMemoria(recursive->der);
        free(recursive);
    }
}
int main() {
    int opcion = 0;
    do {
        cout << "1. Agregar Pelicula" << endl;
        cout << "2. Inorden" << endl;
        cout << "3. Preorden" << endl;
        cout << "4. Postorden" << endl;
        cout << "5. Buscar Pelicula por Nombre" << endl;
        cout << "6. Mostrar todas las Pelicula por Genero" << endl;
        cout << "7. Mostrar 3 Fracasos Taquilleros" << endl;
        cout << "8. Salir" << endl;
        cout << "Digite la opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: 
                añadirPeli(); 
                break;
            case 2: 
            if (raiz == NULL) cout << "El arbol esta vacio." << endl;
            else {
                cout << "Recorrido Inorden:" << endl;
                inorden(raiz);
            }
            break;
            case 3: 
            if (raiz == NULL) cout << "El arbol esta vacio." << endl;
            else {
                cout << "Recorrido Preorden:" << endl;
                preorden(raiz); 
            }
                break;
                
            case 4: 
            if (raiz == NULL) cout << "El arbol esta vacio." << endl;
            else {
                cout << "Recorrido Postorden:" << endl;
                postorden(raiz); 
            }
                break;

            case 5:
            if (raiz == NULL) cout << "El arbol esta vacio." << endl;
            else {
                cout << "Ingrese el nombre a buscar: ";
                cin.ignore();
                cin.getline(nombreBusqueda, 50);
                buscarPN(raiz);
            }
                break;

            case 6:
            if (raiz == NULL) cout << "El arbol esta vacio." << endl;
            else {
                cout << "Ingrese el/los género a buscar: ";
                cin.ignore();
                cin.getline(nombreGenero, 50);
                mostrarPG(raiz);
            }
                break;

                case 7:
                if (raiz == NULL) cout << "No hay peliculas registradas." << endl;
                else {
                m1 = m2 = m3 = NULL;
                mostrar3Fr(raiz);
                cout << "3 Fracasos Taquilleros:" << endl;
                if (m1) cout << "1. " << m1->nombre << " - $" << m1->recaudacion << "M" << endl;
                if (m2) cout << "2. " << m2->nombre << " - $" << m2->recaudacion << "M" << endl;
                if (m3) cout << "3. " << m3->nombre << " - $" << m3->recaudacion << "M" << endl;
                }
                break;
            case 8:
                cout << "Saliendo del programa..." << endl;
                liberarMemoria(raiz);
                break;
            default:
                cout << "Opción no válida" << endl;
        }
    } while(opcion != 8);
    
return 0;
}