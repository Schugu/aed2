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

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
bool estaLaListaVacia(tNodo**);
void insertarPrimerJuego(tNodo**);
void push(tNodo**);
void insertarJuegoEnPos(tNodo**);
void pop(tNodo**);
void eliminarJuegoEnPos(tNodo**);
void mostrarLista(tNodo**);
void crearMenu(tNodo**);
tDatosJuego ingresarDatos();
tNodo* crearNodo(tDatosJuego, tNodo*);
void mostrarOpcionesMenu();
void mostrarDatos(tDatosJuego);

// Funcion principal 
int main (){
	crearMenu(&cabecera);

	return 0;
} 

// Funciones
// Punto a)
void inicializarLista(tNodo** cabecera) {
	*cabecera = NULL;
	printf("Lista inicializada!\n");
}

bool estaLaListaVacia(tNodo** cabecera){
	return (*cabecera == NULL) ? true : false;
}

// Punto b)
void preguntarSiLaListaEstaVacia(tNodo** cabecera){
	estaLaListaVacia(cabecera) ? printf("La lista esta vacia\n") : printf("La lista NO esta vacia\n"); 
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
void push(tNodo** cabecera){
	// Creo los datos del juego
	tDatosJuego juego = ingresarDatos();
	
	// Creo el nodo pasandole los datos y hacia donde apunta
	tNodo* nuevoNodo = crearNodo(juego, *cabecera);
	
	// Ahora el puntero apunta hacia el nuevo nodo
	*cabecera = nuevoNodo;
}

// Punto e)
void insertarJuegoEnPos(tNodo** cabecera){
	int posicion = 0;
	printf("Ingrese la posicion de ingreso: ");
	scanf("%d", &posicion);

	// Validar posicion
	if (posicion < 0) {
		printf("\nPosicion invalida\n");
		return;
	}

	// Ingresar al principio
	if (posicion == 0){
		tDatosJuego juego = ingresarDatos();

		// Creo el nodo pasandole los datos y hacia donde apunta
		tNodo* nuevoNodo = crearNodo(juego, *cabecera);
	
		// Ahora el puntero apunta hacia el nuevo nodo
		*cabecera = nuevoNodo;
		return; 
	}

	tNodo* listaAux = *cabecera;
	for(int i = 1; i < posicion-1 && listaAux != NULL; i++) {
    listaAux = listaAux->siguiente;
  }
  if (listaAux == NULL) {
    printf("Error: La posicion es mayor al tamanio de la lista.\n");
    return;
  }
	tDatosJuego juego = ingresarDatos();
	tNodo* nuevoNodo = crearNodo(juego, listaAux->siguiente);
	listaAux->siguiente = nuevoNodo;
  printf("\nVideojuego insertado en la posicion %d: %s", posicion, juego.titulo);
}

void mostrarDatos(tDatosJuego juego){
	printf("ID: %d\n", juego.id);
	printf("Titulo: %s\n", juego.titulo);
	printf("Anio de lanzamiento: %d\n", juego.anioLanzamiento);
	printf("Precio: $%.2f\n", juego.precio);
}

// Punto f)
void pop(tNodo** cabecera){
	if (estaLaListaVacia(cabecera)) {
		printf("Error: No se puede eliminar por que la lista esta vacia.");
    return;
  }

	// Asigno el nodo que quiero eliminar a aux
	tNodo* aux = *cabecera;
	
	// remplazo el tope con el siguiente del nodo a eliminar
	*cabecera = aux->siguiente;

	// Libero la memoria del nodo
	free(aux);

	printf("Primer juego eliminado.\n");
}

// Punto g)
void eliminarJuegoEnPos(tNodo** cabecera){
	int posicion = 0;
	printf("Ingrese la posicion de ingreso: ");
	scanf("%d", &posicion);

	// Validar posicion
	if (posicion < 0) {
		printf("\nPosicion invalida\n");
		return;
	}

	// Eliminar primer posicion (pop)
	if (posicion == 0){
		pop(cabecera);
		printf("Juego eliminado exitosamente de la posicion: %d", posicion); 
		return;
	}

	// Buscar el nodo anterior al que quiero eliminar
	tNodo* listaAux = *cabecera;
	for(int i = 1; i < posicion-1 && listaAux != NULL; i++) {
    listaAux = listaAux->siguiente;
  }

	if (!listaAux || !listaAux->siguiente) {
    printf("Error: La posicion es mayor al tamanio de la lista.\n");
    return;
  }

	// Puntero al nodo a eliminar
	tNodo* juegoSuprimir = listaAux->siguiente;

	// Enlazar nodo anterior con el nodo siguiente del nodo a eliminar
	listaAux->siguiente = juegoSuprimir->siguiente;

 	printf("\nJuego eliminado de la posicion %d: %s",posicion, juegoSuprimir->datos.titulo);

	free(juegoSuprimir);
}

// Punto i)
void mostrarLista(tNodo** cabecera){
	if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede mostrar la lista por que esta vacia.");
		return;
  }

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux != NULL){
    printf("\n--- Juego en posicion %d ---\n", pos);
    mostrarDatos(aux->datos);
    aux = aux->siguiente;
    pos++;
  }
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
            preguntarSiLaListaEstaVacia(cabecera); 
            break;
          case 'c': 
            insertarPrimerJuego(cabecera); 
            break;
          case 'd': 
            push(cabecera); 
            break;
					case 'e': 
            insertarJuegoEnPos(cabecera); 
            break;
					case 'f': 
            pop(cabecera); 
            break;
					case 'g': 
            eliminarJuegoEnPos(cabecera); 
            break;
					case 'i': 
            mostrarLista(cabecera); 
            break;
          case 'x':
            salir = 'y'; 
            break;
          default:
            printf("Opcion invalida.\n");
        }
        
    } while (salir == 'n');
}