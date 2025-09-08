/*
  3.Una plataforma de streaming de música necesita gestionar las canciones de
  sus playlists mediante una lista enlazada. Cada nodo debe contener: idCancion
  (entero), titulo (cadena), artista (cadena), duracionSegundos (entero), genero
  (cadena). Implementar las siguientes funcionalidades:
  a) Inicializar la playlist.
  b) Agregar una canción a la playlist (contemplar todos los casos posibles)
  c) Eliminar una canción por posición.
  d) Mostrar todas las canciones de la playlist.
  e) Buscar canción por título (mostrar todos los datos si se encuentra).
  f) Calcular duración total de la playlist (en formato mm:ss).
  g) Mostrar la canción más larga y la más corta.
  h) Listar canciones de un artista específico.
  i) Liberar memoria de toda la playlist.
  Crear un menú completo que incluya todas las opciones.
  *Plus:
    - Agregar canción al final de la playlist.
    - Eliminar canción por ID.
    - Contar canciones por género.
*/

// Librerias
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constante
#define MAXSTRING 50

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
  int id;
  tString titulo;
  tString artista;
  int duracionSegundos;
  tString genero;
} tDatosCancion;

typedef struct nodo {
  tDatosCancion datos;
  struct nodo* siguiente;
} tNodo;

// Prototipado
void inicializarLista(tNodo**);

// Punto b
void insertarPrimero(tNodo**);
void push(tNodo**);
void insertarEnPos(tNodo**);
void insertarAlFinal(tNodo**);

bool estaLaListaVacia(tNodo**);
void mostrarLista(tNodo**);

void mostrarOpcionesMenu();
void mostrarOpcionesMenuAgregar();
void mostrarOpcionesMenuEliminar();
void crearMenuAgregar(tNodo**);
void crearMenuEliminar(tNodo**);
void crearMenu(tNodo**);

// Variables globales
tNodo* cabecera;

// Funcion principal
int main() {
  crearMenu(&cabecera);

  return 0;
}

// Funciones
// Punta a)
void inicializarLista(tNodo** cabecera) {
  *cabecera = NULL;
  printf("Lista inicializada!\n");
}

bool estaLaListaVacia(tNodo** cabecera) {
  return (*cabecera == NULL) ? true : false;
}

// Punto b)
tDatosCancion ingresarDatos() {
  tDatosCancion cancion;

  printf("Ingrese los datos de la cancion: \n");
  printf("ID: ");
  scanf("%d", &cancion.id);

  printf("Titulo: ");
  scanf(" %49[^\n]", cancion.titulo);

  printf("Artista: ");
  scanf(" %49[^\n]", cancion.artista);

  printf("Duracion en segundo: ");
  scanf("%d", &cancion.duracionSegundos);

  printf("Genero: ");
  scanf(" %49[^\n]", cancion.genero);

  return cancion;
}

tNodo* crearNodo(tDatosCancion elemento, tNodo* enlace) {
  tNodo* nodo;

  nodo = (tNodo*)malloc(sizeof(tNodo));

  if (nodo == NULL) {
    printf("Error al asignar memoria");
  }

  nodo->datos = elemento;
  nodo->siguiente = enlace;

  return nodo;
}

// Punto b.1)
void insertarPrimero(tNodo** cabecera) {
  tDatosCancion elemento = ingresarDatos();

  tNodo* nuevoNodo = crearNodo(elemento, NULL);

  *cabecera = nuevoNodo;
}

// Punto b.2)
void push(tNodo** cabecera) {
  tDatosCancion elemento = ingresarDatos();

  tNodo* nuevoNodo = crearNodo(elemento, *cabecera);

  *cabecera = nuevoNodo;
}

// Punto b.3)
void insertarEnPos(tNodo** cabecera) {
  int posicion = 0;
  printf("Ingrese la posicion de ingreso: ");
  scanf("%d", &posicion);

  if (posicion < 0) {
    printf("\nPosicion invalida\n");
    return;
  }

  if (posicion == 0) {
    tDatosCancion elemento = ingresarDatos();

    tNodo* nuevoNodo = crearNodo(elemento, *cabecera);

    *cabecera = nuevoNodo;
    return;
  }

  tNodo* listaAux = *cabecera;
  for (int i = 1; i < posicion - 1 && listaAux != NULL; i++) {
    listaAux = listaAux->siguiente;
  }
  if (listaAux == NULL) {
    printf("Error: La posicion es mayor al tamanio de la lista.\n");
    return;
  }
  tDatosCancion elemento = ingresarDatos();
  tNodo* nuevoNodo = crearNodo(elemento, listaAux->siguiente);
  listaAux->siguiente = nuevoNodo;
  printf("\nElemento insertado en la posicion %d: %s", posicion, elemento.titulo);
}

// Punto b.4)
void insertarAlFinal(tNodo** cabecera){
	tDatosCancion elemento = ingresarDatos();
	tNodo* nuevoNodo = crearNodo(elemento, NULL);

	if (!*cabecera){
		*cabecera = nuevoNodo;
	} else {
    tNodo* aux = *cabecera;
    while (aux->siguiente) {
			aux = aux->siguiente;
    }

    aux->siguiente = nuevoNodo;
	}
  printf("\nElemento insertado al final de la lista con exito!\n");
}

// Punto d)
void mostrarDatos(tDatosCancion cancion) {
  printf("ID: %d\n", cancion.id);
  printf("Titulo: %s\n", cancion.titulo);
  printf("Artista: %s\n", cancion.artista);
  printf("Anio de lanzamiento: %d\n", cancion.duracionSegundos);
  printf("Genero: %s", cancion.genero);
}

void mostrarLista(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede mostrar la lista por que esta vacia.");
    return;
  }

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux != NULL) {
    printf("\n\n--- Cancion en posicion %d ---\n", pos);
    mostrarDatos(aux->datos);
    aux = aux->siguiente;
    pos++;
  }
}

void mostrarOpcionesMenu() {
  printf("\n\n========================| Menu |========================\n");
  printf("[a]: Inicializar la playlist.\n");
  printf("[b]: Agregar una canción a la playlist.\n");    // Submenu
  printf("[c]: Eliminar una canción de la playlist.\n");  // Submenu
  printf("[d]: Mostrar todas las canciones de la playlist.\n");
  printf("[e]: Buscar canción por título.\n");
  printf("[f]: Calcular duración total de la playlist.\n");
  printf("[g]: Mostrar la canción más larga y la más corta.\n");
  printf("[h]: Listar canciones de un artista específico.\n");
  printf("[i]: Liberar memoria de toda la playlist.\n");
  printf("[j]: Contar canciones por género.\n");
  printf("[x]: Salir.\n");
}

void mostrarOpcionesMenuAgregar() {
  printf("\n\n========================| Agregar |========================\n");
  printf("[1]: La primera cancion de la playlist.\n");
  printf("[2]: Cancion al principio de la playlist (push).\n");
  printf("[3]: Agregar cancion en una posicion especifica de la playlist.\n");
  printf("[4]: Cancion al final de la playlist.\n");
  printf("[5]: Volver.\n");
}

void mostrarOpcionesMenuEliminar() {
  printf("\n\n========================| Eliminar |========================\n");
  printf("[1]: Cancion al principio de la playlist (pop).\n");
  printf("[2]: Cancion de una posicion especifica de la playlist.\n");
  printf("[3]: Cancion al final de la playlist.\n");
  printf("[4]: Volver.\n");
}

void crearMenuAgregar(tNodo** cabecera) {
  int opcion;
  int salir = false;

  do {
    mostrarOpcionesMenuAgregar();
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    printf("\n\n");

    switch (opcion) {
      case 1:
        insertarPrimero(cabecera);
        break;
      case 2:
        push(cabecera);
        break;
      case 3:
        insertarEnPos(cabecera);
        break;
      case 4:
        insertarAlFinal(cabecera);
        break;
      case 5:
        salir = true;
        break;
      default:
        printf("Opcion invalida.\n");
    }
  } while (!salir);
}

void crearMenuEliminar(tNodo** cabecera) {
  int opcion;
  int salir = false;

  do {
    mostrarOpcionesMenuEliminar();
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    printf("\n\n");

    switch (opcion) {
      // case 1: inicializarLista(cabecera); break;
      // case 2: preguntarSiLaListaEstaVacia(cabecera); break;
      // case 3: insertarPrimerJuego(cabecera); break;
      case 4:
        salir = true;
        break;
      default:
        printf("Opcion invalida.\n");
    }
  } while (!salir);
}

void crearMenu(tNodo** cabecera) {
  char opcion;
  char salir = false;

  do {
    mostrarOpcionesMenu();
    fflush(stdin);
    printf("Seleccione una opcion: ");
    scanf(" %c", (&opcion));
    opcion = tolower(opcion);
    printf("\n\n");

    switch (opcion) {
      case 'a':
        inicializarLista(cabecera);
        break;
      case 'b':
        crearMenuAgregar(cabecera);
        break;
      case 'c':
        crearMenuEliminar(cabecera);
        break;
      case 'd':
        mostrarLista(cabecera);
        break;
      case 'x':
        salir = true;
        break;
      default:
        printf("Opcion invalida.\n");
    }
  } while (!salir);
}