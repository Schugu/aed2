#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Punto a)
#define MAXSTRING 50

typedef char tString[MAXSTRING];

typedef struct {
  int dni;
  tString nombre;
  tString apellido;
  int edad;
  int tipoAtencion;
} tPaciente;

typedef struct nodo {
  tPaciente datos;
  struct nodo* siguiente;
} tNodo;

typedef struct {
  tNodo* frente;
  tNodo* final;
} tCola;

// Punto b)
void desencolar(tCola* cola) {
  tNodo* aux = cola->frente;

  printf("El paciente con el DNI: %d ya ha sido atendido.", aux->datos.dni);

  cola->frente = aux->siguiente;
  if (!cola->frente) {
    cola->final = NULL;
  }
  free(aux);
}

// Punto c)
void mostrarDatosPorAtencion(tCola* cola, int opcion) {
  tString arr[3] = {"consulta", "reparacion", "extraccion"};

  printf("*** Pacientes en espera para '%s' ***\n", arr[opcion]);
  printf("DNI\t\tNombre\t\tApellido\t\tEdad\t\t");

  tNodo* aux = cola->frente;
  int contador = 0;
  while (aux) {
    printf("%d\t\t%s\t\t%s\t\t%d\n", aux->datos.dni, aux->datos.nombre, aux->datos.apellido, aux->datos.edad);
    aux = aux->siguiente;
    contador++;
  }
  printf("Total de pacientes: %d", contador);
}
