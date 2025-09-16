#include <stdio.h>

#define MAXSTRING 50

typedef char tString[MAXSTRING];

typedef struct {
  tString fechaHora;
  int numero;
  int codTipo;
} tLlamada;

typedef struct nodo {
  tLlamada datos;
  struct nodo* siguiente;
} tNodo;

void mostrarLlamadasPorTipo(tNodo** cabecera, int codTipoLLamada) {
  tString tipoLlamada[2] = {"Entrantes", "Salientes"};

  tNodo* aux = *cabecera;
  int totalLlamadas = 0;
  int totalLLamadasDeTipo = 0;

  printf("*** Llamadas '%s' ***\n", tipoLlamada[codTipoLLamada]);
  printf("Fecha y hora\t\tNumero de telefono\n");

  while (aux) {
    if (aux->datos.codTipo == codTipoLLamada) {
      printf("%s hs\t\t%d\n");
      totalLLamadasDeTipo++;
    }

    aux = aux->siguiente;
    totalLlamadas++;
  }

  float porcentaje = (float)codTipoLLamada / totalLlamadas;

  printf("Porcentaje de llamadas '%s' respecto del de llamadas: %.2f", tipoLlamada[codTipoLLamada], porcentaje);
}

void borrarHistorial(tNodo** cabecera) {
  tNodo* aux = *cabecera;

  while (aux) {
    tNodo* siguiente = aux->siguiente;
    free(aux);
    aux = siguiente;
  }
  *cabecera = NULL;
  printf("Historial borrado con exito!");
}