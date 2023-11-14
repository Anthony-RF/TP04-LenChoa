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
    Nodo* actual;
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
    nuevoTablero->actual = start;
    nuevoTablero->columna1 = lista1;
    nuevoTablero->columna2 = lista2;
    nuevoTablero->columna3 = lista3;
    nuevoTablero->niveles = levels;
    return nuevoTablero;
}

void imprimirTablero(Tablero* t) {

    int niveles = t->niveles;
    int margen = (niveles/2) * niveles;

    t->columna1->actual = t->columna1->raiz->izquierda;
    t->columna2->actual = t->columna2->raiz->siguiente;
    t->columna3->actual = t->columna3->raiz->derecha;

    for(int i = t->niveles; i > 0; i--) {

        if(i == niveles){

            // Imprime el valor de la cuspide del tablero

            for (int j = 0; j < margen + i; j++) {
                printf(" ");
            }
            printf("%d\n", t->inicio->valor);

        }

        else{

            // Imprime los simbolos

            for (int j = 0; j < (margen + i - (2 * (niveles - i))); j++) {
                printf(" ");
            }
            printf("/");

            for (int j = 0; j < (3 * (niveles - i) - 1); j++) {
                printf(" ");
            }
            printf("|");

            for (int j = 0; j < (3 * (niveles - i) - 1); j++) {
                printf(" ");
            }
            printf("%c", '\\');

            printf("\n");

            // Imprime los valores

            for (int j = 0; j < (margen + i - (2 * (niveles - i)) - 1); j++) {
                printf(" ");
            }
            printf("%d", t->columna1->actual->valor);

            for (int j = 0; j < (3 * (niveles - i)); j++) {
                printf("-");
            }
            printf("%d", t->columna2->actual->valor);

            for (int j = 0; j < (3 * (niveles - i)); j++) {
                printf("-");
            }
            printf("%d", t->columna3->actual->valor);

            printf("\n");

            }

        // Se mueve al siguiente valor en las 3 listas

        t->columna1->actual = t->columna1->actual->siguiente;
        t->columna2->actual = t->columna2->actual->siguiente;
        t->columna3->actual = t->columna3->actual->siguiente;
    }
}

void iniciarJuego(Tablero* t){

    printf("Instrucciones:\n");
    printf("Para mover tu pieza, ingrese la cordenada donde esta su pieza y la direccion a la que deseas mover.\n\n\n");

    printf("El tigre se ha colocado en la cuspide del tablero.\n");
    printf("Los leopardos han tomado su posicion, empieza el juego!\n\n\n");

    t->inicio->valor = 1;

    t->columna1->final->valor = 2;
    t->columna2->final->valor = 2;
    t->columna3->final->valor = 2;
    t->columna1->final->anterior->valor = 2;
    t->columna2->final->anterior->valor = 2;
    t->columna3->final->anterior->valor = 2;

    char* jugador = "T";

    int columna;
    int fila;
    int ficha;
    int movimiento;

    int leopardos = 6;
    int tigreflag = 0;

    while(leopardos > 3 && tigreflag == 0){

        imprimirTablero(t);
        printf("\n\n", jugador);

        printf("Turno del jugador: %s\n\n", jugador);

        printf("Por favor, ingrese la columna de su ficha: ");
        scanf("%d", &columna);

        printf("Por favor, ingrese la fila de su ficha: ");
        scanf("%d", &fila);

        if(columna == 1){
            t->columna1->actual = t->columna1->raiz;
            for(int i=0; i < fila; i++)
            {
                t->columna1->actual = t->columna1->actual->siguiente;
            }
            t->actual = t->columna1->actual;
        }

        if(columna == 2){
            t->columna2->actual = t->columna2->raiz;
            for(int i=0; i < fila; i++)
            {
                t->columna2->actual = t->columna2->actual->siguiente;
            }
            t->actual = t->columna2->actual;
        }

        if(columna == 3){
            t->columna3->actual = t->columna3->raiz;
            for(int i=0; i < fila; i++)
            {
                t->columna3->actual = t->columna3->actual->siguiente;
            }
            t->actual = t->columna3->actual;
        }

        ficha = t->actual->valor;

        printf("Por favor, ingrese la direccion de su movimiento: ");
        scanf("%d", &movimiento);

        if(jugador == "T" && ficha == 1){

            if(movimiento == 1){
                    t->actual->siguiente->valor = 1;
                    t->actual->valor = 0;
            }

            else if(movimiento == 2){
                    t->actual->anterior->valor = ficha;
                    t->actual->valor = 0;
            }

            else if(movimiento == 3) {
                    t->actual->derecha->valor = ficha;
                    t->actual->valor = 0;
            }
            else if(movimiento == 4){
                    t->actual->izquierda->valor = ficha;
                    t->actual->valor = 0;
            }

            jugador = "L";

        }
        if(jugador == "L" && ficha == 2){

            if(movimiento == 1){
                t->actual->siguiente->valor = ficha;
                t->actual->valor = 0;
            }

            if(movimiento == 2){
                t->actual->siguiente->valor = ficha;
                t->actual->valor = 0;
            }

            if(movimiento == 3){
                t->actual->siguiente->valor = ficha;
                t->actual->valor = 0;
            }

            if(movimiento == 4){
                t->actual->siguiente->valor = ficha;
                t->actual->valor = 0;
            }

            jugador = "T";
        }

    }
}

int main() {

    Tablero* tablero = crearTablero(7);

    imprimirTablero(tablero);

    iniciarJuego(tablero);

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
