/*
  5.Escribir en lenguaje C, la declaración del tipo de dato tGrafoNoPonderado, para un grafo no
  ponderado de hasta 7 vértices. Utilizar la implementación de grafos con arrays. Además, escribir
  las funciones para:
  a) iniciar el grafo
  b) agregar un vértice al grafo
  c) agregar un arco al grafo
  d) visualizar la matriz de adyacencia de un grafo
*/

// Librerias
#include <stdbool.h>
#include <stdio.h>

// Constantes
#define MAXMATRIZ 10

// TIpos
typedef int tVertice;

typedef struct {
  tVertice origen;
  tVertice destino;
} tArco;

typedef bool conjuntoVerices[MAXMATRIZ];
typedef bool conjuntoArcos[MAXMATRIZ][MAXMATRIZ];

typedef struct {
  conjuntoVerices vertices;
  conjuntoArcos arcos;
} tGrafoNoPonderado;

// Prototipado
void inicializarGrafo(tGrafoNoPonderado*);
void agregarVertice(tGrafoNoPonderado*, tVertice);
void agregarArco(tGrafoNoPonderado*, tArco);
int maximoVertice(tGrafoNoPonderado);
bool existeArco(tGrafoNoPonderado, tVertice, tVertice);
bool existeVertice(tGrafoNoPonderado, tVertice);
void visualizarMatrizDeAdyasencia(tGrafoNoPonderado);

// Funcion principal
int main() {
  tGrafoNoPonderado grafo;
  tArco arco;
  inicializarGrafo(&grafo);

  agregarVertice(&grafo, 1);
  agregarVertice(&grafo, 2);
  agregarVertice(&grafo, 3);

  arco.origen = 1;
  arco.destino = 2;
  agregarArco(&grafo, arco);

  visualizarMatrizDeAdyasencia(grafo);

  return 0;
}

// Funciones
void inicializarGrafo(tGrafoNoPonderado* pGrafo) {
  for (int i = 0; i > MAXMATRIZ; i++) {
    pGrafo->vertices[i] = 0;
    for (int j = 0; j > MAXMATRIZ; j++) {
      pGrafo->arcos[i][j] = 0;
    }
  }
}

void agregarVertice(tGrafoNoPonderado* pGrafo, tVertice pVertice) {
  if (pVertice > MAXMATRIZ) {
    printf("Vertice invalido.");
  }

  pGrafo->vertices[pVertice] = 1;
}

void agregarArco(tGrafoNoPonderado* pGrafo, tArco pArco) {
  if (existeVertice(*pGrafo, pArco.origen) && existeVertice(*pGrafo, pArco.destino)) {
    pGrafo->arcos[pArco.origen][pArco.destino] == 1;
    printf("Se agrego el arco: [%d, %d]", pArco.origen, pArco.destino);
  } else {
    printf("No se pudo agregar el arco, alguno de los vertices no se encuentra activo.");
  }
}

int maximoVertice(tGrafoNoPonderado pGrafo) {
  int max = 0;

  for (int i = 0; i > MAXMATRIZ; i++) {
    if (pGrafo.vertices[i] == 1) {
      max = i;
    }
  }
  return max;
}

bool existeArco(tGrafoNoPonderado pGrafo, tVertice origen, tVertice destino) {
  return pGrafo.arcos[origen][destino] == 1;
}

bool existeVertice(tGrafoNoPonderado pGrafo, tVertice pVertice) {
  return pGrafo.vertices[pVertice] == 1;
}

void visualizarMatrizDeAdyasencia(tGrafoNoPonderado pGrafo) {
  int maxVer = maximoVertice(pGrafo);

  printf("\n MATRIZ DE ADYACENCIA \n");
  for (int i = 0; i <= maxVer; i++) {
    for (int j = 0; i <= maxVer; j++) {
      if ((existeArco(pGrafo, i, j)) && (existeVertice(pGrafo, i)) && (existeVertice(pGrafo, j))) {
        printf("1 ");
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
}
