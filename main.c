#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de Nodo
typedef struct Nodo {
    int valor;
    struct Nodo* siguiente;
    struct Nodo* anterior;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

// Función para crear un nuevo Nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevoNodo = (Nodo*)calloc(1,sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

// Definición de la estructura de Lista
typedef struct Lista {
    Nodo* actual;
    Nodo* raiz;
    Nodo* final;
    int longitud;
} Lista;

// Función para crear una nueva Lista
struct Lista* crearLista() {
    struct Lista* nuevaLista = (Lista*)calloc(1,sizeof(Lista));
    nuevaLista->actual = NULL;
    nuevaLista->raiz = NULL;
    nuevaLista->final = NULL;
    nuevaLista->longitud = 0;
    return nuevaLista;
}

// Función para agregar un nodo al final de la Lista
void agregarAlFinal(Lista* l, Nodo* n) {
    if (l->final == NULL) {
        l->actual = n;
        l->raiz = n;
        l->final = n;
        l->longitud = 1;
    }
    else {
        l->final->siguiente = n;
        n->anterior = l->final;
        l->final= l->final->siguiente;
        l->actual = l->final;
        l->longitud = l->longitud += 1;
    }
}

// Función para agregar un nodo al inicio de la Lista
void agregarAlInicio(Lista* l, Nodo* n) {
    if (l->raiz == NULL) {
        l->actual = n;
        l->raiz = n;
        l->final = n;
        l->longitud = 1;
    }
    else {
        l->raiz->anterior = n;
        n->siguiente = l->raiz;
        l->raiz= l->raiz->anterior;
        l->actual = l->raiz;
        l->longitud = l->longitud += 1;
    }
}

// Función para obtener la longitud de una Lista
int len(Lista* l) {
    return l->longitud;
}

// Función para recorrer la Lista hacia adelante
void recorrerAdelante(Lista* l) {
    l->actual = l->raiz;
    printf("NULL -> ");
    while (l->actual != NULL) {
        printf("%d -> ", l->actual->valor);
        l->actual = l->actual->siguiente;
    }
    printf("NULL\n");
}

// Función para recorrer la Lista hacia atrás
void recorrerAtras(Lista* l) {
    l->actual = l->final;
    printf("NULL <- ");
    while (l->actual != NULL) {
        printf("%d <- ", l->actual->valor);
        l->actual = l->actual->anterior;
    }
    printf("NULL\n");
}

// Definición de la estructura de Tablero
typedef struct Tablero {
    Nodo* inicio;
    Lista* columna1;
    Lista* columna2;
    Lista* columna3;
    int niveles;
} Tablero;

int main() {
    // Se crea una Lista
    struct Lista* listaEjemplo = crearLista();

    // Se agregan elementos a la Lista
    agregarAlFinal(listaEjemplo, crearNodo(0));
    agregarAlFinal(listaEjemplo, crearNodo(1));
    agregarAlFinal(listaEjemplo, crearNodo(2));
    agregarAlFinal(listaEjemplo, crearNodo(3));
    agregarAlFinal(listaEjemplo, crearNodo(4));
    agregarAlInicio(listaEjemplo, crearNodo(-1));
    agregarAlInicio(listaEjemplo, crearNodo(-2));
    agregarAlInicio(listaEjemplo, crearNodo(-3));
    agregarAlInicio(listaEjemplo, crearNodo(-4));

    // Se revisa el largo de la lista
    printf("La longitud de la lista es de %d elementos. \n", len(listaEjemplo));

    // Se recorre la lista hacia adelante
    printf("Recorriendo la lista hacia adelante:\n");
    recorrerAdelante(listaEjemplo);

    // Se recorre la lista hacia atras
    printf("Recorriendo la lista hacia atras:\n");
    recorrerAtras(listaEjemplo);

    return 0;
}
