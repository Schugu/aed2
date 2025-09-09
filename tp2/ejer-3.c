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
#include <string.h>

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

typedef struct {
  int pos;
  int duracion;
} tMinMaxCancion;

// Prototipado
// Punto a)
void inicializarLista(tNodo**);

// Punto b)
bool estaLaListaVacia(tNodo**);
void insertarPrimero(tNodo**);
void push(tNodo**);
void insertarEnPos(tNodo**);
void insertarAlFinal(tNodo**);

// Punto c)
void pop(tNodo**);
void eliminarEnPos(tNodo**);
void eliminarAlFinal(tNodo**);
void eliminarPorId(tNodo**);

// Punto d)
void mostrarDatos(tDatosCancion);
void mostrarLista(tNodo**);

// Punto e)
void convertirMinuscula(tString);
void buscarPorTitulo(tNodo**);

// Punto f)
void mostrarNodoPorPos(tNodo**, int);
void calcularDuracionTotal(tNodo**);

// Punto g)
void calcularMaxYMin(tNodo**);

// Punto h)
void buscarCancionesPorArtista(tNodo**);

// Punto i)
void liberarMemoriaTotal(tNodo**);

// Punto j)
void contarCancionesPorGenero(tNodo**);

// Mneú
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
  printf("\nElemento insertado en la posicion %d: %s", posicion,
         elemento.titulo);
}

// Punto b.4)
void insertarAlFinal(tNodo** cabecera) {
  tDatosCancion elemento = ingresarDatos();
  tNodo* nuevoNodo = crearNodo(elemento, NULL);

  if (!*cabecera) {
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

// Punto c.1)
void pop(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: No se puede eliminar por que la lista esta vacia.");
    return;
  }

  tNodo* aux = *cabecera;

  *cabecera = aux->siguiente;

  free(aux);

  printf("Primer elemento eliminado.\n");
}

// Punto c.2)
void eliminarEnPos(tNodo** cabecera) {
  int posicion = 0;
  printf("Ingrese la posicion de egreso: ");
  scanf("%d", &posicion);

  if (posicion < 0) {
    printf("\nPosicion invalida\n");
    return;
  }

  if (posicion == 0) {
    pop(cabecera);
    printf("Elemento eliminado exitosamente de la posicion: %d", posicion);
    return;
  }

  tNodo* listaAux = *cabecera;
  for (int i = 1; i < posicion - 1 && listaAux != NULL; i++) {
    listaAux = listaAux->siguiente;
  }

  if (!listaAux || !listaAux->siguiente) {
    printf("Error: La posicion es mayor al tamanio de la lista.\n");
    return;
  }

  tNodo* elementoSuprimir = listaAux->siguiente;

  listaAux->siguiente = elementoSuprimir->siguiente;

  printf("\nElemento eliminado de la posicion %d: %s", posicion,
         elementoSuprimir->datos.titulo);

  free(elementoSuprimir);
}

// Punto c.3)
void eliminarAlFinal(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: No se puede eliminar porque la lista está vacía.\n");
    return;
  }

  tNodo* aux = *cabecera;
  tNodo* auxAnterior = NULL;

  // Caso especial: solo hay un nodo
  if (aux->siguiente == NULL) {
    free(aux);
    *cabecera = NULL;  // la lista queda vacía
    printf("\nElemento eliminado del final de la lista con éxito!\n");
    return;
  }

  while (aux->siguiente != NULL) {
    auxAnterior = aux;
    aux = aux->siguiente;
  }

  auxAnterior->siguiente = NULL;
  printf("\nElemento eliminado del final de la lista con éxito!\n");
}

// Punto c.4)
void eliminarPorId(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede eliminar por ID porque la lista está vacía.\n");
    return;
  }

  int busqueda;
  printf("Ingrese un ID: ");
  scanf("%d", &busqueda);

  if (busqueda < 0) {
    printf("\nID inválido\n");
    return;
  }

  tNodo* aux = *cabecera;
  tNodo* auxAnterior = NULL;
  int pos = 0;

  while (aux != NULL) {
    if (aux->datos.id == busqueda) {
      mostrarDatos(aux->datos);

      if (auxAnterior == NULL) {
        *cabecera = aux->siguiente;
      } else {
        auxAnterior->siguiente = aux->siguiente;
      }

      free(aux);
      printf("\nElemento con ID %d eliminado en posición %d\n", busqueda, pos);
      return;
    }

    auxAnterior = aux;
    aux = aux->siguiente;
    pos++;
  }

  printf("No se encontraron resultados para ID %d...\n", busqueda);
}

// Punto d)
void mostrarDatos(tDatosCancion cancion) {
  printf("ID: %d\n", cancion.id);
  printf("Titulo: %s\n", cancion.titulo);
  printf("Artista: %s\n", cancion.artista);
  printf("Duracion en segundos: %d\n", cancion.duracionSegundos);
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

// Punto e)
void convertirMinuscula(tString string) {
  for (int i = 0; string[i] != '\0'; i++) {
    string[i] = tolower(string[i]);
  }
}

void buscarPorTitulo(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf(
        "Error: no se puede buscar por titulo, la lista por que esta vacia.");
    return;
  }

  tString busqueda;
  printf("Ingrese un titulo: ");
  scanf(" %49[^\n]", busqueda);
  convertirMinuscula(busqueda);

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux) {
    tString auxTitulo;
    strcpy(auxTitulo, aux->datos.titulo);
    convertirMinuscula(auxTitulo);
    if (strcmp(auxTitulo, busqueda) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d", pos);
      return;
    }
    aux = aux->siguiente;
    pos++;
  }
  printf("No se encontraron resultaodos...");
  return;
}

// Punto f)
void calcularDuracionTotal(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf(
        "Error: no se puede calcular duracion total, la lista por que esta "
        "vacia.");
    return;
  }

  tNodo* aux = *cabecera;
  int acumulador = 0;

  while (aux) {
    acumulador += aux->datos.duracionSegundos;
    aux = aux->siguiente;
  }

  printf("Duracion total de la playlist en segundos: %d", acumulador);
}

void mostrarNodoPorPos(tNodo** cabecera, int pos) {
  tNodo* aux = *cabecera;

  for (int i = 0; i < pos; i++) {
    aux = aux->siguiente;
  }
  mostrarDatos(aux->datos);
}

// Punto g
void calcularMaxYMin(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede calcular por que la lista esta vacia.");
    return;
  };

  tMinMaxCancion minimo;
  tMinMaxCancion maximo;

  tNodo* aux = *cabecera;
  int pos = 0;
  minimo.duracion = aux->datos.duracionSegundos;
  minimo.pos = 0;
  maximo.duracion = aux->datos.duracionSegundos;
  maximo.pos = 0;

  while (aux) {
    if (aux->datos.duracionSegundos > maximo.duracion) {
      maximo.duracion = aux->datos.duracionSegundos;
      maximo.pos = pos;
    } else if (aux->datos.duracionSegundos < minimo.duracion) {
      minimo.duracion = aux->datos.duracionSegundos;
      minimo.pos = pos;
    }
    aux = aux->siguiente;
    pos++;
  }

  printf("La cancion mas corta de la playlist es: \n");
  mostrarNodoPorPos(cabecera, minimo.pos);

  printf("\nLa cancion mas larga de la playlist es: \n");
  mostrarNodoPorPos(cabecera, maximo.pos);
}

void buscarCancionesPorArtista(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf(
        "Error: no se pueden listar las canciones por artista por que la lista "
        "esta vacia.");
    return;
  }

  tString busqueda;
  printf("Ingrese el artista: ", busqueda);
  scanf(" %49[^\n]", busqueda);
  convertirMinuscula(busqueda);

  tNodo* aux = *cabecera;
  tNodo* cancionesArtista = NULL;
  while (aux) {
    tString auxArtista;
    strcpy(auxArtista, aux->datos.artista);
    convertirMinuscula(busqueda);

    if (strcmp(auxArtista, busqueda) == 0) {
      if (cancionesArtista == NULL) {
        tNodo* nuevoNodo = crearNodo(aux->datos, NULL);

        cancionesArtista = nuevoNodo;
      } else {
        tNodo* nuevoNodo = crearNodo(aux->datos, cancionesArtista);

        cancionesArtista = nuevoNodo;
      }
    }
    aux = aux->siguiente;
  }

  if (cancionesArtista == NULL) {
    printf("No se encontraron resultados...");
  } else {
    printf("Canciones encontradas del artista: %s", busqueda);
    mostrarLista(&cancionesArtista);
  }
}

// Punto i)
void liberarMemoriaTotal(tNodo** cabecera) {
  tNodo* aux = *cabecera;
  while (aux) {
    // tNodo* siguiente = aux->siguiente;
    free(aux);
    aux = aux->siguiente;
  }
  *cabecera = NULL;
  printf("\nMemoria liberada exitosamente!\n");
}

// Punto j)
void contarCancionesPorGenero(tNodo** cabecera) {
  tString busqueda;
  printf("Ingrese el genero: ", busqueda);
  scanf(" %49[^\n]", busqueda);
  convertirMinuscula(busqueda);

  tNodo* aux = *cabecera;
  int contador = 0;

  while (aux) {
    tString auxGenero;
    strcpy(auxGenero, aux->datos.genero);
    convertirMinuscula(auxGenero);

    if (strcmp(auxGenero, busqueda) == 0) {
      contador++;
    }

    aux = aux->siguiente;
  }

  printf("Total de canciones para el genero %s: %d", busqueda, contador);
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
  printf("[4]: Cancion por ID de la playlist.\n");
  printf("[5]: Volver.\n");
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
      case 1:
        pop(cabecera);
        break;
      case 2:
        eliminarEnPos(cabecera);
        break;
      case 3:
        eliminarAlFinal(cabecera);
        break;
      case 4:
        eliminarPorId(cabecera);
        break;
      case 5:
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
      case 'e':
        buscarPorTitulo(cabecera);
        break;
      case 'f':
        calcularDuracionTotal(cabecera);
        break;
      case 'g':
        calcularMaxYMin(cabecera);
        break;
      case 'h':
        buscarCancionesPorArtista(cabecera);
        break;
      case 'i':
        liberarMemoriaTotal(cabecera);
        break;
      case 'j':
        contarCancionesPorGenero(cabecera);
        break;
      case 'x':
        salir = true;
        break;
      default:
        printf("Opcion invalida.\n");
    }
  } while (!salir);
}