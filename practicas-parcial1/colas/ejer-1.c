#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50

typedef char tString[MAXSTRING];

typedef struct {
  int codigo;
  tString destinatario;
  tString direccion;
  int cp;
  bool esFragil;
} tPaquete;

typedef struct nodo {
  tPaquete datos;
  struct nodo* siguiente;
} tNodo;

typedef struct {
  tNodo* frente;
  tNodo* final;
} tCola;

// Prototipado
void inicializarCola(tCola*);
bool colaVacia(tCola*);
void encolar(tCola*, tPaquete);
void desencolar(tCola*);
void mostrarPorFragilidad(tCola*, bool);

// Variable

int main() {
  tCola cola;
  inicializarCola(&cola);

  tPaquete p1 = {1452, "Juan Martinez", "Av. Cordoba 123 (Bs. As.)", 1234, 1};
  tPaquete p2 = {1456, "Maria Almada", "Irigoyen 435 (Entre Rios)", 2345, 1};
  tPaquete p3 = {1457, "Carlos Perez", "San Martin 500 (Mendoza)", 4567, 0};

  // Encolamos
  encolar(&cola, p1);
  encolar(&cola, p2);
  encolar(&cola, p3);

  desencolar(&cola);

  // Mostrar solo los frágiles
  mostrarPorFragilidad(&cola, true);

  // Mostrar los NO frágiles
  mostrarPorFragilidad(&cola, false);
  return 0;
}

void inicializarCola(tCola* c) {
  c->frente = NULL;
  c->final = NULL;
}

bool colaVacia(tCola* c) {
  return ((c->frente == NULL) && (c->final == NULL));
}

void encolar(tCola* c, tPaquete p) {
  tNodo* nuevoNodo = (tNodo*)malloc(sizeof(tNodo));
  if (nuevoNodo == NULL) {
    printf("Error al asignar memoria.");
    return;
  }

  nuevoNodo->datos = p;
  nuevoNodo->siguiente = NULL;

  if (colaVacia(c)) {
    c->frente = nuevoNodo;
  } else {
    c->final->siguiente = nuevoNodo;
  }
  c->final = nuevoNodo;
}

void desencolar(tCola* c) {
  if (colaVacia(c)) {
    printf("Error: no se puede desencolar por que esta vacia la cola.\n");
    return;
  }
  tNodo* aux = c->frente;

  printf("EL paquete %d, se insertara en el camion.\n", aux->datos.codigo);

  c->frente = aux->siguiente;
  if (!c->frente) {
    c->final = NULL;
  }
  tPaquete p = aux->datos;
  free(aux);
}

void mostrarPorFragilidad(tCola* c, bool fragil) {
  tNodo* aux = c->frente;
  int contador = 0;

  printf("*** Paquetes marcados como '%s' ***\n\n", fragil ? "Fragil" : "No fragiles");
  printf("Cod. unico - Destinatario - Direccion - CP\n");

  while (aux) {
    if (aux->datos.esFragil == fragil) {
      printf("%d\t\t%s\t\t%s\t\t%d\n",
             aux->datos.codigo,
             aux->datos.destinatario,
             aux->datos.direccion,
             aux->datos.cp);
      contador++;
    }
    aux = aux->siguiente;
  }

  printf("\nTotal de paquetes marcados como %s: %d\n",
         fragil ? "fragiles" : "no fragiles", contador);
}