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
    Lista* nuevaLista = (Lista*)calloc(1,sizeof(Lista));
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
        if (n->siguiente == NULL) {
            l->raiz->anterior = n;
            n->siguiente = l->raiz;
            l->raiz= l->raiz->anterior;
            l->actual = l->raiz;
            l->longitud = l->longitud += 1;
        }
        else if (n->siguiente != NULL && n->izquierda == NULL) {
            l->raiz->anterior = n;
            n->izquierda = l->raiz;
            l->raiz= l->raiz->anterior;
            l->actual = l->raiz;
            l->longitud = l->longitud += 1;
        }
        else if (n->siguiente != NULL && n->izquierda != NULL && n->derecha == NULL) {
            l->raiz->anterior = n;
            n->derecha = l->raiz;
            l->raiz= l->raiz->anterior;
            l->actual = l->raiz;
            l->longitud = l->longitud += 1;
        }

        else {
            printf("Nodo 'n' no cuenta con punteros disponibles para ser enlazado. \n");
        }
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

struct Tablero* crearTablero(int levels) {

    //Creación de una estructura Tablero
    Tablero* nuevoTablero = (Tablero*)calloc(1,sizeof(Tablero));

    //Creación del Nodo inicial
    Nodo* start = crearNodo(0);

    //Creación de las Listas
    Lista* lista1 = crearLista();
    Lista* lista2 = crearLista();
    Lista* lista3 = crearLista();

    //Inicialización de las Listas
    for(int i=0; i<levels; i++){

        Nodo* n1 = crearNodo(0);
        Nodo* n2 = crearNodo(0);
        Nodo* n3 = crearNodo(0);

        n1->derecha = n2;
        n2->izquierda = n1;
        n2->derecha = n3;
        n3->izquierda = n2;

        agregarAlFinal(lista1, n1);
        agregarAlFinal(lista2, n2);
        agregarAlFinal(lista3, n3);
    }

    agregarAlInicio(lista2, start);
    agregarAlInicio(lista1, start);
    agregarAlInicio(lista3, start);

    nuevoTablero->inicio = start;
    nuevoTablero->columna1 = lista1;
    nuevoTablero->columna2 = lista2;
    nuevoTablero->columna3 = lista3;
    nuevoTablero->niveles = levels;
    return nuevoTablero;
}

void imprimirTablero(Tablero* t) {

    if (t->inicio == t->columna1->raiz && t->inicio == t->columna2->raiz && t->inicio == t->columna3->raiz ) {
        printf("--- %d ---\n", t->inicio->valor);

        t->columna1->actual = t->columna1->raiz->izquierda;
        t->columna2->actual = t->columna2->raiz->siguiente;
        t->columna3->actual = t->columna3->raiz->derecha;
    }
    for(int i = 0; i < (t -> niveles) - 1 ; i++){

        t->columna1->actual = t->columna1->actual->siguiente;
        t->columna2->actual = t->columna2->actual->siguiente;
        t->columna3->actual = t->columna3->actual->siguiente;

        printf("|   |   |\n");
        printf("%d - %d - %d\n", t->columna1->actual->valor, t->columna2->actual->valor, t->columna3->actual->valor);
    }
}

int main() {

    Tablero* tablero = crearTablero(5);

    imprimirTablero(tablero);

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
    //printf("La longitud de la lista es de %d elementos. \n", len(listaEjemplo));

    // Se recorre la lista hacia adelante
    //printf("Recorriendo la lista hacia adelante:\n");
    //recorrerAdelante(listaEjemplo);

    // Se recorre la lista hacia atras
    //("Recorriendo la lista hacia atras:\n");
    //recorrerAtras(listaEjemplo);

    return 0;
}
