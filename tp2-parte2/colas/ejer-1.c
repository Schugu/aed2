/*
  1. Se necesita procesar los datos de los llamados que ingresan al call center de una empresa de
  telecomunicaciones. Para ello se implementa una cola, en donde cada nodo contiene los siguientes
  datos: nombre y apellido, número de teléfono, DNI, código de lugar de procedencia (01-Corrientes
  02-Chaco). Se solicita escribir las funciones para:
  a) Conocer la cantidad de llamadas provenientes de cada lugar de procedencia y la cantidad total
  de llamadas en cola de espera.
  b) Generar un listado que incluya los números telefónicos de las llamadas provenientes de
  Corrientes.
  c) Tener en cuenta que se deben realizar las operaciones básicas necesarias para la manipulación
  de la cola con punteros.
*/
// Librerias
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAXSTRING 50
#define MAXARRAY 3

typedef char tString[MAXSTRING];

typedef struct {
  tString nombreApellido;
  tString numero;
  tString dni;
  tString codigoLugar;
} tLlamada;

typedef struct nodo {
  tLlamada datos;
  struct nodo* siguiente;
} tNodo;

typedef struct {
  tNodo* frente;
  tNodo* final;
} tCola;

// Prototipado
bool colaVacia(tCola);

void elegirCodigoLugar(tString);
tLlamada ingresarDatos();
tNodo* crearNodo(tLlamada, tNodo*);
void insertarNodo(tNodo**, tLlamada);
void push(tNodo**);

// Opcion b)
void mostrarDatos(tLlamada);
void mostrarPila(tNodo**);

// Opcion c)
void mostrarPorCodigo(tNodo**);

// Opcion d)
void eliminarHistorial(tNodo**);

void mostrarOpcionesMenu();
void crearMenu(tNodo**);

// Variables
tString arrayCodigoLugar[MAXARRAY] = {"Corrientes", "Chaco"};

tNodo* tope;

// Función principal
int main() {
  crearMenu(&tope);
  return 0;
}

// Funciones
// Opcion a)
void elegirCodigoLugar(tString codigo) {
  printf("Elija el codigo de lugar de procedencia: \n");
  for (int i = 0; i < MAXARRAY; i++) {
    printf("[%d]: %s\n", i + 1, arrayCodigoLugar[i]);
  }

  int opcion;
  bool valido = false;

  do {
    printf("Ingrese la opcion: ");
    scanf("%d", &opcion);
    printf("\n");
    switch (opcion) {
    case 1:
      strcpy(codigo, arrayCodigoLugar[0]);
      valido = true;
      break;
    case 2:
      strcpy(codigo, arrayCodigoLugar[1]);
      valido = true;
      break;
    default:
      printf("Opcion invalida, por favor ingresela de nuevo.\n");
      break;
    }
  } while (!valido);
}
tLlamada ingresarDatos() {
  tLlamada sitio;

  printf("Nombre y apellido: ");
  scanf(" %49[^\n]", sitio.nombreApellido);

  printf("Numero: ");
  scanf(" %49[^\n]", sitio.numero);

  printf("DNI: ");
  scanf(" %49[^\n]", sitio.dni);

  elegirCodigoLugar(sitio.codigoLugar);

  return sitio;
}
tNodo* crearNodo(tLlamada sitio, tNodo* enlace) {
  tNodo* nodo;
  nodo = (tNodo*)malloc(sizeof(tNodo));

  if (nodo == NULL) {
    printf("Error al asignar memoria.");
  }

  nodo->datos = sitio;
  nodo->siguiente = enlace;

  return nodo;
}
void insertarNodo(tNodo** tope, tLlamada sitio) {
  tNodo* nodo = NULL;
  if (!*tope) {
    nodo = crearNodo(sitio, NULL);
  } else {
    nodo = crearNodo(sitio, *tope);
  }
  *tope = nodo;
}
void push(tNodo** tope) {
  tLlamada sitio = ingresarDatos();
  insertarNodo(tope, sitio);
}

// Opcion b)
void mostrarDatos(tLlamada sitio) {
  printf("Fecha y hora: %s\n", sitio.fechaHora);
  printf("URL del sitio: %s\n", sitio.url);
  printf("Codigo de clasificacion: %s\n", sitio.codigo);
}
void mostrarPila(tNodo** tope) {
  if (!*tope) {
    printf("Lista vacia.");
    return;
  }
  tNodo* aux = *tope;
  int pos = 0;
  printf("\n\n---| Historial |---\n");
  while (aux) {
    printf("\n--- Sitio en posicion: %d ---\n", pos);
    mostrarDatos(aux->datos);
    aux = aux->siguiente;
    pos++;
  }
}

// Punto c)
void mostrarPorCodigo(tNodo** cabecera) {
  tString codigo;
  elegirCodigoLugar(codigo);

  tNodo* aux = *cabecera;
  int pos = 0;
  int cantLlamadas = 0;
  printf("\n\n---| Historial (%s) |---\n", codigo);
  while (aux) {
    if (strcmp(aux->datos.codigo, codigo) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d\n\n", pos);
      cantLlamadas++;
    }
    aux = aux->siguiente;
    pos++;
  }

  if (pos == 0) {
    printf("No hay resultados...");
    return;
  }
  float porcentaje = ((float)cantLlamadas / pos) * 100;
  printf("Porcentaje de visitas a sitios de '%s' respecto del total sitios visitados: %.2f%%", codigo, porcentaje);
}

// Punto d)
void eliminarHistorial(tNodo** tope) {
  tNodo* aux = *tope;

  while (aux) {
    tNodo* siguiente = aux->siguiente;
    free(aux);
    aux = siguiente;
  }
  *tope = NULL;
  printf("Historial eliminado con exito!");
}

// Menú
void mostrarOpcionesMenu() {
  printf("\n\n========================| Menu |========================\n");
  printf("[a]: Agregar sitio.\n");
  printf("[b]: Mostrar historial.\n");
  printf("[c]: Mostrar historial por codigo de clasificacion.\n");
  printf("[d]: Eliminar historial.\n");
  printf("[x]: Salir.\n");
}
void crearMenu(tNodo** tope) {
  char opcion;
  bool salir = false;

  do {
    mostrarOpcionesMenu();
    printf("Seleccione una opcion: ");
    scanf(" %c", &opcion);
    printf("\n\n");

    switch (opcion) {
    case 'a':
      push(tope);
      break;
    case 'b':
      mostrarPila(tope);
      break;
    case 'c':
      mostrarPorCodigo(tope);
      break;
    case 'd':
      eliminarHistorial(tope);
      break;
    case 'x':
      salir = true;
      break;

    default:
      printf("Opcion invalida. \n");
    }
  } while (!salir);
}
