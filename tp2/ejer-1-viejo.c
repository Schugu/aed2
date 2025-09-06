// Librerias 
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define maxLength 50

// Tipos
typedef char tString[maxLength];

// Creo el tipo de datos del juego
typedef struct {
  int id;
  tString titulo;
  int anioLanzamiento;
  float precio;
} tDatosVideojuego;

// Creo el tipo de dato nodo 
typedef struct nodo {
  tDatosVideojuego juego; // Información del juego
  struct nodo* siguiente; // Puntero al siguiente nodo de la lista
} tListaVideojuegos;

// Prototipado
tListaVideojuegos* crearNodo(); // Función para crear un nuevo nodo
void ingresarDatos(tDatosVideojuego*); // Paso por referencia (dirección de memoria)
void mostrarDatos(tDatosVideojuego*); // Paso por referencia (dirección de memoria)
void liberarMemoria(tListaVideojuegos**); // Paso por referencia (doble puntero => puntero del puntero)

// Función principal
int main(){
  // Creo el nodo
  // Creo un puntero a nodo usando la función crearNodo()
  tListaVideojuegos* primerNodo = crearNodo();

  /*
    Función de mostrar el dato, la forma de acceder a la info del nodo es utilizando la dirección
    de memoria con la flechita que seria como el punto de un struct hacia la propiedad donde esta la info 
  */
  mostrarDatos(&primerNodo->juego);

  // libero la memoria mandandole la dirección de memoria del nodo creado
  liberarMemoria(&primerNodo);
  return 0;
}

tListaVideojuegos* crearNodo(){
  tListaVideojuegos* nodo = NULL;

  // Segun chat no hace falta castear acá
  // nodo = (tListaVideojuegos*) malloc(sizeof(tListaVideojuegos));
  // Forma sin casteo: 
  // Pido memoria con malloc para un nodo
  nodo = malloc(sizeof(tListaVideojuegos));

  // Si no se asigna memoria tirar error y retornar null sino el programa sigue
  if (nodo == NULL){
    printf("Error al asignar memoria. \n");
    return NULL;
  }

  // Función de ingresar datos pasandole la dirección de memoria del nodo accediendo a la info del mismo
  ingresarDatos(&nodo->juego);

  // Asignar null a la referencia del sigueinte nodo de la lista por que no hay info que ingresar 
  // (lo dejamos para el futuro)
  nodo->siguiente = NULL;

  // Retornamos el nodo creado
  return nodo;
}

// Función de ingresar datos, le paso el objeto con la info del nodo
void ingresarDatos(tDatosVideojuego* juego){ 
  printf("Ingrese los datos del juego: \n");
  printf("ID:");
  scanf("%d", &juego->id);

  // Segun chat, no se pone el & acá por que los strings en este caso 'titulo' ya es una dirección de memoria
  // por lo tanto el scanf ya recibe la dirección de memoria donde escribir el string
  printf("Titulo: ");
  scanf(" %49[^\n]", juego->titulo);

  printf("Anio de lanzamiento: ");
  scanf("%d", &juego->anioLanzamiento);

  printf("Precio: ");
  scanf("%f", &juego->precio);
}

// Función para mostrar los datos, le paso el objeto con la info del nodo
void mostrarDatos(tDatosVideojuego* juego){
  printf("\n\n==============| Datos del juego: |==============\n");
  printf("ID: %d \n", juego->id);
  printf("Titulo: %s \n", juego->titulo);
  printf("Anio de lanzamiento: %d \n", juego->anioLanzamiento);
  printf("Precio: $%.2f \n", juego->precio);
  printf("================================================\n\n");
}

// Función para liberar memoria, le paso el nodo
void liberarMemoria(tListaVideojuegos** nodo){
  free(*nodo); // Libero la memoria del nodo
  *nodo = NULL; // Pongo el puntero en null
  printf("Memoria liberada exitosamente! \n");
}