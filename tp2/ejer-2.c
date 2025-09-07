/* 
	2. Modificar el ejercicio 1 para implementar todas las operaciones básicas de una lista enlazada: 
	a) Inicializar la lista (establecer puntero en NULL). 
	b) Verificar si una lista está vacía. 
	c) Insertar el primer videojuego (nodo) de la lista. 
	d) Insertar un videojuego al principio de la lista. 
	e) Insertar un videojuego en una posición específica. 
	f) Eliminar el primer videojuego de la lista. 
	g) Eliminar un videojuego de una posición específica. 
	h) Buscar un videojuego por ID y retornar su posición. 
	i) Visualizar todos los videojuegos de la lista. 
	j) Contar la cantidad total de videojuegos.  
	k) Liberar completamente la memoria de la lista. 
	Crear un menú principal que permita probar todas estas funciones. 
	Plus: Insertar un videojuego al final de la lista. 
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSTRING 50

// Tipos 
typedef char tString[MAXSTRING];

typedef struct {
	int id;
	tString titulo;
	int anioLanzamiento;
	float precio;

} tDatosJuego;

typedef struct nodo {
	tDatosJuego datos;
	struct nodo* siguiente;
} tNodo;

// Variables globales
tNodo* cabecera; // Inicializo variable puntero como NULL (no apunta a ningun nodo)

// Prototipado 
void inicializarLista(tNodo**);
void estaLaListaVacia(tNodo**);
void insertarPrimerJuego(tNodo**);
void insertarJuegoAlPrincipio(tNodo**);
void crearMenu(tNodo**);
tDatosJuego ingresarDatos();
tNodo* crearNodo(tDatosJuego, tNodo*);
void mostrarOpcionesMenu();
void mostrarDatos(tDatosJuego);


// Funcion principal 
int main (){
	crearMenu(&cabecera);

// 	// Creo los datos del juego
// 	tDatosJuego juego = ingresarDatos();

// 	// Creo el nodo pasandole los datos y hacia donde apunta
// 	tNodo* nuevoNodo = crearNodo(juego, NULL);

// 	// Ahora el puntero apunta hacia el nuevo nodo
// 	cabecera = nuevoNodo;

// 	// Se crea un nuevo apuntador auxiliar y se le asigna el valor de la cabecera
// 	tNodo* aux = cabecera;
// 	while(aux != NULL){
// 		mostrarDatos(cabecera->datos);

// 		// Se apunta al nodo siguiente al que apunta la cabecera y asi sucesivamente
// 		aux = cabecera->siguiente;
// 	}

// 	return 0;
} 

// Punto a)
void inicializarLista(tNodo** cabecera) {
	*cabecera = NULL;
	printf("Lista inicializada!\n");
}

// Punto b)
void estaLaListaVacia(tNodo** cabecera){
	if(*cabecera == NULL){
		printf("La lista esta vacia\n");
	} else {
		printf("La lista NO esta vacia\n");
	}
}

// Crear Nodo
tNodo* crearNodo(tDatosJuego juego, tNodo* enlace){
	tNodo* nodo;

	nodo = (tNodo*) malloc(sizeof(tNodo));

	if (nodo == NULL) {
		printf("Error al asignar memoria");
	}

	nodo->datos = juego;
	nodo->siguiente = enlace;	

	return nodo;
}

// Punto c)
void insertarPrimerJuego(tNodo** cabecera){
	// Creo los datos del juego
	tDatosJuego juego = ingresarDatos();

	// Creo el nodo pasandole los datos y hacia donde apunta
	tNodo* nuevoNodo = crearNodo(juego, NULL);
	
	// Ahora el puntero apunta hacia el nuevo nodo
	*cabecera = nuevoNodo;
}

// Punto d)
void insertarJuegoAlPrincipio(tNodo** cabecera){
	// Creo los datos del juego
	tDatosJuego juego = ingresarDatos();
	
	// Creo el nodo pasandole los datos y hacia donde apunta
	tNodo* nuevoNodo = crearNodo(juego, *cabecera);
	
	// Ahora el puntero apunta hacia el nuevo nodo
	*cabecera = nuevoNodo;
}

// Menú
void mostrarOpcionesMenu(){
	printf("\n\n===============| Menu |===============\n");
	printf("[a]: Inicializar la lista (establecer puntero en NULL).\n");
	printf("[b]: Verificar si una lista esta vacia.\n");
	printf("[c]: Insertar el primer videojuego (nodo) de la lista.\n");
	printf("[d]: Insertar un videojuego al principio de la lista.\n");
	printf("[e]: Insertar un videojuego en una posicion especifica.\n");
	printf("[f]: Eliminar el primer videojuego de la lista.\n");
	printf("[g]: Eliminar un videojuego de una posicion especifica.\n");
	printf("[h]: Buscar un videojuego por ID y retornar su posicion.\n");
	printf("[i]: Visualizar todos los videojuegos de la lista.\n");
	printf("[j]: Contar la cantidad total de videojuegos.\n");
	printf("[k]: Liberar completamente la memoria de la lista.\n");
}

// Menú
void crearMenu(tNodo** cabecera) {
    char opcion;
    char salir = 'n';

    do {
        mostrarOpcionesMenu();
				fflush(stdin);
				printf("Seleccione una opcion: ");
        scanf(" %c", &opcion); 
				printf("\n\n");

        switch (opcion) {
          case 'a': 
            inicializarLista(cabecera); 
            break;
          case 'b': 
            estaLaListaVacia(cabecera); 
            break;
          case 'c': 
            insertarPrimerJuego(cabecera); 
            break;
          case 'd': 
            insertarJuegoAlPrincipio(cabecera); 
            break;
          case 'x':
            salir = 'y'; 
            break;
          default:
            printf("Opcion invalida.\n");
        }
        
    } while (salir == 'n');
}

tDatosJuego ingresarDatos(){
	tDatosJuego juego;
	printf("Ingrese los datos del juego: \n");
	printf("ID: ");
	scanf("%d", &juego.id);

	printf("Titulo: ");
	scanf(" %49[^\n]", juego.titulo);

	printf("Anio lanzamiento: ");
	scanf("%d", &juego.anioLanzamiento);

	printf("Precio: ");
	scanf("%f", &juego.precio);

	return juego;
}



void mostrarDatos(tDatosJuego juego){
	printf("\n");
	printf("ID: %d\n", juego.id);
	printf("Titulo: %s\n", juego.titulo);
	printf("Anio de lanzamiento: %d\n", juego.anioLanzamiento);
	printf("Precio: %.2f\n", juego.precio);
}