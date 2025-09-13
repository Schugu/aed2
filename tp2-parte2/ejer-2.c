/*
  2. Un sistema operativo para teléfonos móviles requiere que se agregue un módulo para guardar el
  historial de las llamadas de los usuarios. Para ello se almacena en una pila la siguiente información
  de las llamadas: fecha y hora(string), número de teléfono, y código de tipo de llamada (1-Entrante
  2-Saliente). Las llamadas se insertan en la pila, según el orden en el cual fueron realizadas.
  Se requiere:
  a) Codificar en lenguaje C, las estructuras de datos necesarias para la declaración del tipo
  tPilaLlamadas adecuado.
  b) Una función que permita visualizar el detalle de llamadas según el código de tipo de llamada
  que se recibe como parámetro. Además, se pide calcular el porcentaje de llamadas que
  coincidan con ese tipo de llamada respecto del total de llamadas. Un ejemplo del formato de
  impresión solicitado es el siguiente:
  *** Llamadas “Entrantes” ***
  Fecha y hora Número de teléfono
  19.45 hs 3794 12324
  18.30 hs 3794 34587
  Porcentaje de llamadas “entrantes” respecto del de llamadas: 37.75%
  c) Escribir una función que permita borrar todo el historial de llamadas.
*/
// Librerias
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAXSTRING 50
#define MAXARRAY 2

typedef char tString[MAXSTRING];

typedef struct {
  tString fechaHora;
  tString numero;
  tString codigo;
} tLlamada;

typedef struct nodo {
  tLlamada datos;
  struct nodo* siguiente;
} tNodo;

// Prototipado
// Opcion a)
void elegirCodigoClasif(tString);
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
tString arrayCodigoLlamada[MAXARRAY] = {"Entrante", "Saliente"};

tNodo* tope;

// Función principal
int main() {
  crearMenu(&tope);
  return 0;
}

// Funciones
// Opcion a)
void elegirCodigoClasif(tString codigo) {
  printf("Elija el codigo de tipo de llamada: \n");
  for (int i = 0; i < MAXARRAY; i++) {
    printf("[%d]: %s\n", i + 1, arrayCodigoLlamada[i]);
  }

  int opcion;
  bool valido = false;

  do {
    printf("Ingrese la opcion: ");
    scanf("%d", &opcion);
    printf("\n");
    switch (opcion) {
    case 1:
      strcpy(codigo, arrayCodigoLlamada[0]);
      valido = true;
      break;
    case 2:
      strcpy(codigo, arrayCodigoLlamada[1]);
      valido = true;
      break;
    default:
      printf("Opcion invalida, por favor ingresela de nuevo.\n");
      break;
    }
  } while (!valido);
}
tLlamada ingresarDatos() {
  tLlamada llamada;

  printf("Fecha y hora: ");
  scanf(" %49[^\n]", llamada.fechaHora);

  printf("Numero de telefono: ");
  scanf(" %49[^\n]", llamada.numero);

  elegirCodigoClasif(llamada.codigo);

  return llamada;
}
tNodo* crearNodo(tLlamada llamada, tNodo* enlace) {
  tNodo* nodo;
  nodo = (tNodo*)malloc(sizeof(tNodo));

  if (nodo == NULL) {
    printf("Error al asignar memoria.");
  }

  nodo->datos = llamada;
  nodo->siguiente = enlace;

  return nodo;
}
void insertarNodo(tNodo** tope, tLlamada llamada) {
  tNodo* nodo = NULL;
  if (!*tope) {
    nodo = crearNodo(llamada, NULL);
  } else {
    nodo = crearNodo(llamada, *tope);
  }
  *tope = nodo;
}
void push(tNodo** tope) {
  tLlamada llamada = ingresarDatos();
  insertarNodo(tope, llamada);
}

// Opcion b)
void mostrarDatos(tLlamada llamada) {
  printf("Fecha y hora: %s\n", llamada.fechaHora);
  printf("Numero de telefono: %s\n", llamada.numero);
  printf("Codigo de clasificacion: %s\n", llamada.codigo);
}
void mostrarPila(tNodo** tope) {
  if (!*tope) {
    printf("Lista vacia.");
    return;
  }
  tNodo* aux = *tope;
  int pos = 0;
  printf("\n\n---| Llamadas |---\n");
  while (aux) {
    printf("\n--- llamada en posicion: %d ---\n", pos);
    mostrarDatos(aux->datos);
    aux = aux->siguiente;
    pos++;
  }
}

// Punto c)
void mostrarPorCodigo(tNodo** cabecera) {
  tString codigo;
  elegirCodigoClasif(codigo);

  tNodo* aux = *cabecera;
  int pos = 0;
  int cantLlamadas = 0;
  printf("\n\n---| Llamadas (%ss) |---\n", codigo);
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
  printf("Porcentaje de llamadas '%s' respecto del total de llamadas: %.2f%%", codigo, porcentaje);
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
  printf("Historial de llamadas eliminado con exito!");
}

// Menú
void mostrarOpcionesMenu() {
  printf("\n\n========================| Menu |========================\n");
  printf("[a]: Agregar llamada.\n");
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
