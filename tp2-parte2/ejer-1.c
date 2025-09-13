/*
  1. Un nuevo navegador de internet requiere que se agregue un módulo para guardar el historial de
  sitios web visitados por el usuario. Para ello se almacena en una pila la siguiente información de los
  sitios web: fecha y hora(string), url del sitio, y código de tipo de clasificación del sitio
  (1-Empresariales 2-Gubernamentales 3-Redes Sociales). Los sitios se insertan en la pila, según el orden
  en el cual fueron visitados.
  Se requiere:
    a) Codificar en lenguaje C, las estructuras de datos necesarias para la declaración del tipo
      tPilaSitiosWeb adecuado.
    b) Una función que permita visualizar el detalle de sitios web que fueron visitados según el tipo de
      clasificación que se recibe como parámetro. Además, se pide calcular el porcentaje de visitas
      a sitios web que coincidan con ese tipo de clasificación respecto del total sitios visitados.
      Un ejemplo del formato de impresión solicitado es el siguiente:
        *** Sitios web del tipo “Redes Sociales” ***
          Fecha y hora        url
          14.45 hs            www.facebook.com
          16.30 hs            www.instagram.com
      Porcentaje de visitas a sitios de “Redes Sociales” respecto del total sitios visitados: 25%
    c) Escribir una función que permita borrar todo el historial del navegador.
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
  tString fechaHora;
  tString url;
  tString codigo;
} tSitio;

typedef struct nodo {
  tSitio datos;
  struct nodo* siguiente;
} tNodo;

// Prototipado
// Opcion a)
void elegirCodigoClasif(tString);
tSitio ingresarDatos();
tNodo* crearNodo(tSitio, tNodo*);
void insertarNodo(tNodo**, tSitio);
void push(tNodo**);

// Opcion b)
void mostrarDatos(tSitio);
void mostrarPila(tNodo**);

// Opcion c)
void mostrarPorCodigo(tNodo**);

// Opcion d)
void eliminarHistorial(tNodo**);

void mostrarOpcionesMenu();
void crearMenu(tNodo**);

// Variables
tString arrayCodigoClasificacion[MAXARRAY] = {"Empresariales", "Gubernamentales", "Redes Sociales"};

tNodo* tope;

// Función principal
int main() {
  crearMenu(&tope);
  return 0;
}

// Funciones
// Opcion a)
void elegirCodigoClasif(tString codigo) {
  printf("Elija el codigo de claisifacion: \n");
  for (int i = 0; i < MAXARRAY; i++) {
    printf("[%d]: %s\n", i + 1, arrayCodigoClasificacion[i]);
  }

  int opcion;
  bool valido = false;

  do {
    printf("Ingrese la opcion: ");
    scanf("%d", &opcion);
    printf("\n");
    switch (opcion) {
    case 1:
      strcpy(codigo, "Empresariales");
      valido = true;
      break;
    case 2:
      strcpy(codigo, "Gubernamentales");
      valido = true;
      break;
    case 3:
      strcpy(codigo, "Redes Sociales");
      valido = true;
      break;
    default:
      printf("Opcion invalida, por favor ingresela de nuevo.\n");
      break;
    }
  } while (!valido);
}
tSitio ingresarDatos() {
  tSitio sitio;

  printf("Fecha y hora (formato: hh:ss): ");
  scanf(" %49[^\n]", sitio.fechaHora);

  printf("URL del sitio: ");
  scanf(" %49[^\n]", sitio.url);

  elegirCodigoClasif(sitio.codigo);

  return sitio;
}
tNodo* crearNodo(tSitio sitio, tNodo* enlace) {
  tNodo* nodo;
  nodo = (tNodo*)malloc(sizeof(tNodo));

  if (nodo == NULL) {
    printf("Error al asignar memoria.");
  }

  nodo->datos = sitio;
  nodo->siguiente = enlace;

  return nodo;
}
void insertarNodo(tNodo** tope, tSitio sitio) {
  tNodo* nodo = NULL;
  if (!*tope) {
    nodo = crearNodo(sitio, NULL);
  } else {
    nodo = crearNodo(sitio, *tope);
  }
  *tope = nodo;
}
void push(tNodo** tope) {
  tSitio sitio = ingresarDatos();
  insertarNodo(tope, sitio);
}

// Opcion b)
void mostrarDatos(tSitio sitio) {
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
  elegirCodigoClasif(codigo);

  tNodo* aux = *cabecera;
  int pos = 0;
  int cantSitios = 0;
  printf("\n\n---| Historial (%s) |---\n", codigo);
  while (aux) {
    if (strcmp(aux->datos.codigo, codigo) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d\n\n", pos);
      cantSitios++;
    }
    aux = aux->siguiente;
    pos++;
  }

  if (pos == 0) {
    printf("No hay resultados...");
    return;
  }
  float porcentaje = ((float)cantSitios / pos) * 100;
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
