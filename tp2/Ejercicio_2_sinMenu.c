/*  a)	Inicializar la lista (establecer puntero en NULL).
	b)	Verificar si una lista está vacía.
	c)	Insertar el primer videojuego (nodo) de la lista.
	d)	Insertar un videojuego al principio de la lista.
	e)	Insertar un videojuego en una posición específica.
	f)	Eliminar el primer videojuego de la lista.*/
	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

typedef char tString50[MAX];

typedef struct {
    int idJuego;
    tString50 titulo;
    int anioLanzamiento;
    float precio;
} tDatosVideojuego;

typedef struct nodo {
    tDatosVideojuego videojuego;
    struct nodo* siguiente;
} tListaVideojuegos;

/* Prototipos */
void inicializarLista(tListaVideojuegos**);
bool listaVacia(tListaVideojuegos*);
void insertarVideojuego(tListaVideojuegos**, tDatosVideojuego);
void insertarPrimerVideojuego(tListaVideojuegos**, tDatosVideojuego);
void insertarVideojuegoAlPrincipio(tListaVideojuegos**, tDatosVideojuego);
void insertarVideojuegoEnPos(tListaVideojuegos**, tDatosVideojuego, int);
void insertarAlFinal(tListaVideojuegos**, tDatosVideojuego);
void eliminarPrimerVideojuego(tListaVideojuegos**);
void eliminarVideojuegoDePos(tListaVideojuegos**, int);
void visualizarVideojuegos(tListaVideojuegos*);
int buscarPorID(tListaVideojuegos*, int);
int totalVideojuegos(tListaVideojuegos*);
void liberarTodaLaMemoria(tListaVideojuegos**);

tDatosVideojuego cargarDatosVideojuego();
void mostrarDatosNodo(tListaVideojuegos*);

int main() {
    tListaVideojuegos* lista;
    int posicion;
    inicializarLista(&lista);

    printf("\n### DEMOSTRACION DE FUNCIONES ###\n");

    /* Insertar primer videojuego*/
    printf("\nCreando el primer videojuego...\n");
    tDatosVideojuego videoJuego = cargarDatosVideojuego();
    insertarVideojuego(&lista, videoJuego);

    /* Insertar otro al principio*/
    printf("\n\nCreando otro videojuego para insertar al principio...\n");
    tDatosVideojuego VideoJuego1 = cargarDatosVideojuego();
    insertarVideojuegoAlPrincipio(&lista, VideoJuego1);

    /* Insertar en posición especifica*/
    printf("\n\nCreando otro videojuego para insertar en posicion especifica...\n");
    printf("Ingrese la posicion en la que se desea insertar el nuevo nodo: ");
    scanf("%d", &posicion);
	tDatosVideojuego VideoJuego2 = cargarDatosVideojuego();
    insertarVideojuegoEnPos(&lista, VideoJuego2, posicion);

    /* Insertar al final*/
    printf("\n\nCreando otro videojuego para insertar al final...\n");
    tDatosVideojuego VideoJuego3 = cargarDatosVideojuego();
    insertarAlFinal(&lista, VideoJuego3);

    /* Visualizar lista completa*/
    printf("\nMostrando videojuegos actuales:\n");
    visualizarVideojuegos(lista);

    /* Buscar por ID*/
    int idBuscado;
    printf("\nIngrese un ID de videojuego para buscar: ");
    scanf("%d", &idBuscado);
    int pos = buscarPorID(lista, idBuscado);
    if (pos != -1) {
        printf("Videojuego con ID %d encontrado en posicion %d.\n", idBuscado, pos);
    } else {
        printf("No se encontro el videojuego con ID %d.\n", idBuscado);
    }

    /* Eliminar el primer videojuego*/
    printf("\nEliminando el primer videojuego...\n");
    eliminarPrimerVideojuego(&lista);

    /* Eliminar videojuego de una posición especifica*/
    printf("\n\nEliminando videojuego de la posicion indicada...\n");
    printf("Ingrese la posicion en la que se desea eliminar el nodo: ");
    scanf("%d", &posicion);
    eliminarVideojuegoDePos(&lista, posicion);

    /* Mostrar lista final*/
    printf("\nLista final de videojuegos:\n");
    visualizarVideojuegos(lista);

    /* Total de videojuegos*/
    printf("\nCantidad total de videojuegos en la lista: %d\n", totalVideojuegos(lista));

    /* Liberar memoria*/
    liberarTodaLaMemoria(&lista);

    return 0;
}

// ---- IMPLEMENTACION DE FUNCIONES ----
void inicializarLista(tListaVideojuegos** listaVideojuegos) {
    *listaVideojuegos = NULL;
    printf("\tLista inicializada!\n");
}

// Funcion para preguntar si la lista esta vacia (devuelve un bool)
bool listaVacia(tListaVideojuegos* listaVideojuegos) {
    return (listaVideojuegos == NULL);
}

void insertarVideojuego(tListaVideojuegos** listaVideojuegos, tDatosVideojuego datosVideojuego) {
    // Se pregunta si la lista esta vacia
    if(listaVacia(*listaVideojuegos)){
        // Si lo esta ingresa desde el primer lugar
        insertarPrimerVideojuego(listaVideojuegos, datosVideojuego);
    } else {
        insertarVideojuegoAlPrincipio(listaVideojuegos, datosVideojuego);
    }
}

void insertarPrimerVideojuego(tListaVideojuegos** listaVideojuegos, tDatosVideojuego datosVideojuego) {
    // Pido memoria con el malloc, casteando la estructura de nodo 
    tListaVideojuegos* nuevoNodo = (tListaVideojuegos*) malloc(sizeof(tListaVideojuegos));
    
    // Asigno la info al nodo
    nuevoNodo->videojuego = datosVideojuego;
    
    // Asigno null al puntero que apunta al siguiente nodo
    // Esto seria como inicializarlo en null (?
    nuevoNodo->siguiente = NULL;

    // Agrego el nodo utilizando la direccion de memoria de la lista de nodos
    // PREGUNTAR A CHATGPT, por que se agrega de esta forma el primer nodo a la lista
    *listaVideojuegos = nuevoNodo;
    printf("\nSe agrego el videojuego: %s!", datosVideojuego.titulo);
}

void insertarVideojuegoAlPrincipio(tListaVideojuegos** listaVideojuegos, tDatosVideojuego datosVideojuego) {
    tListaVideojuegos* nuevoNodo = (tListaVideojuegos*) malloc(sizeof(tListaVideojuegos));
    nuevoNodo->videojuego = datosVideojuego;

    // ??????? no apunta a otro nodo o a null wtf preguntarle a chati
    nuevoNodo->siguiente = *listaVideojuegos;
    *listaVideojuegos = nuevoNodo;
    printf("\nSe agrego el videojuego: %s!", datosVideojuego.titulo);
}

void insertarVideojuegoEnPos(tListaVideojuegos** listaVideojuegos, tDatosVideojuego datosVideojuego, int posicion) {
   
   int i;
	if (posicion < 0) {
        printf("Error: Posición inválida.\n");
        return;
    }
    if (posicion == 0) {
        insertarVideojuegoAlPrincipio(listaVideojuegos, datosVideojuego);
        return;
    }
    tListaVideojuegos* listaAux = *listaVideojuegos;
    for(i = 1; i < posicion-1 && listaAux != NULL; i++) {
        listaAux = listaAux->siguiente;
    }
    if (listaAux == NULL) {
        printf("Error: La posicion es mayor al tamaño de la lista.\n");
        return;
    }
    tListaVideojuegos* nuevoNodo = (tListaVideojuegos*) malloc(sizeof(tListaVideojuegos));
    nuevoNodo->videojuego = datosVideojuego;
    nuevoNodo->siguiente = listaAux->siguiente;
    listaAux->siguiente = nuevoNodo;
    printf("\nVideojuego insertado en la posicion %d: %s", posicion, datosVideojuego.titulo);
}

void insertarAlFinal(tListaVideojuegos** listaVideojuegos, tDatosVideojuego datosVideojuego) {
    tListaVideojuegos* nuevoNodo = (tListaVideojuegos*) malloc(sizeof(tListaVideojuegos));
    nuevoNodo->videojuego = datosVideojuego;
    nuevoNodo->siguiente = NULL;
    if (*listaVideojuegos == NULL) {
        *listaVideojuegos = nuevoNodo;
    } else {
        tListaVideojuegos* listaAux = *listaVideojuegos;
        while (listaAux->siguiente != NULL) {
            listaAux = listaAux->siguiente;
        }
        listaAux->siguiente = nuevoNodo;
    }
    printf("\nVideojuego insertado al final: %s\n", datosVideojuego.titulo);
}

void eliminarPrimerVideojuego(tListaVideojuegos** listaVideojuegos) {
    if(listaVacia(*listaVideojuegos)){
        printf("No hay videojuegos para quitar!\n");
    } else {
        // Preguntar a chati
        tListaVideojuegos* videojuegoSuprimir = *listaVideojuegos;
        *listaVideojuegos = (*listaVideojuegos)->siguiente;
        printf("Videojuego quitado: %s", videojuegoSuprimir->videojuego.titulo);
        free(videojuegoSuprimir);
    }
}

void eliminarVideojuegoDePos(tListaVideojuegos** listaVideojuegos, int posicion) {
    int i;
	if (*listaVideojuegos == NULL) {
        printf("Error: Lista vacía.\n");
        return;
    }
    if (posicion == 0) {
        eliminarPrimerVideojuego(listaVideojuegos);
        return;
    }
    tListaVideojuegos* listaAux = *listaVideojuegos;
    for(i = 1; i < posicion-1 && listaAux != NULL; i++) {
        listaAux = listaAux->siguiente;
    }
    if (listaAux == NULL || listaAux->siguiente == NULL) {
        printf("Error: Posición inválida.\n");
        return;
    }
    tListaVideojuegos* videojuegoSuprimir = listaAux->siguiente;
    listaAux->siguiente = videojuegoSuprimir->siguiente;
    printf("\nVideojuego quitado de la posicion %d: %s", posicion, videojuegoSuprimir->videojuego.titulo);
    free(videojuegoSuprimir);
}

int buscarPorID(tListaVideojuegos* listaVideojuegos, int idJuego) {
    tListaVideojuegos* listaAux = listaVideojuegos;
    int posicion = 0;
    while (listaAux != NULL) {
        posicion++;
        if (listaAux->videojuego.idJuego == idJuego) {
            return posicion;
        }
        listaAux = listaAux->siguiente;
    }
    return -1;
}

void visualizarVideojuegos(tListaVideojuegos* listaVideojuegos) {
    if(listaVacia(listaVideojuegos)){
        printf("No hay videojuegos para mostrar.\n");
        return;
    }
    tListaVideojuegos* listaAux = listaVideojuegos;
    int posicion = 0;
    while(listaAux != NULL){
        posicion++;
        printf("\nPosicion %d:\n", posicion);
        mostrarDatosNodo(listaAux);
        listaAux = listaAux->siguiente;
    }
}

int totalVideojuegos(tListaVideojuegos* listaVideojuegos) {
    int cantidad = 0;
    while(listaVideojuegos != NULL){
        cantidad++;
        listaVideojuegos = listaVideojuegos->siguiente;
    }
    return cantidad;
}

tDatosVideojuego cargarDatosVideojuego() {
    tDatosVideojuego datosVideojuego;
    printf(" ## CREAR VIDEOJUEGO ##\n");
    printf("\tID del juego: ");
    scanf("%d", &datosVideojuego.idJuego);
    printf("\tTitulo: ");
    scanf(" %49[^\n]", datosVideojuego.titulo);
    printf("\tAnio de lanzamiento: ");
    scanf("%d", &datosVideojuego.anioLanzamiento);
    printf("\tPrecio: ");
    scanf("%f", &datosVideojuego.precio);
    return datosVideojuego;
}

void mostrarDatosNodo(tListaVideojuegos* nodo) {
    printf("ID del juego        : %d\n", nodo->videojuego.idJuego);
    printf("Titulo              : %s\n", nodo->videojuego.titulo);
    printf("Anio de lanzamiento : %d\n", nodo->videojuego.anioLanzamiento);
    printf("Precio              : $%.2f\n", nodo->videojuego.precio);
}

void liberarTodaLaMemoria(tListaVideojuegos** listaVideojuegos) {
    tListaVideojuegos* listaAux = *listaVideojuegos;
    while (listaAux != NULL) {
        tListaVideojuegos* siguiente = listaAux->siguiente;
        free(listaAux);
        listaAux = siguiente;
    }
    *listaVideojuegos = NULL;
    printf("\nMemoria liberada correctamente.\n");
}

