/*
    1) (5ptos) Grafos + TDA Desarrollar un Tipo de Dato Abstracto (TDA) llamado tGrafoRedComputadoras para modelar una red local de computadoras en una empresa. El grafo será no dirigido y ponderado, con capacidad para hasta 100 equipos. Cada arista representará una conexión de red entre dos computadoras y contendrá información sobre la velocidad del enlace (Mbps) y el nivel de latencia (ms). La implementación del grafo se realizará utilizando arrays. Se solicita:
    Incluir la declaración completa de todos los tipos de datos personalizados necesarios para modelar el grafo.
    Codificar una función para agregar una conexión entre dos equipos activos.
    Codificar una función para eliminar una conexión existente.
    Codificar una función para visualizar la matriz de conexiones, mostrando los valores con el formato: (xxx Mbps | xx ms)
    Crear un programa que haga uso del TDA, declare una variable del tipo tGrafoRedComputadoras, y utilice las funciones para gestionar los equipos y las conexiones entre ellos. Nota: Tener en cuenta que los nombres de los tipos de datos personalizados deben ser acordes al problema. Además, incluir los prototipos de funciones por tratarse de un TDA.
*/

#ifndef GRAFICOREDCOMPUTADORAS.H
#define GRAFICOREDCOMPUTADORAS_H

// Librerias
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 100
#define MAXSTRING 30

// Tipos
typedef struct {
    float velocidadEnlace;
    float nivelDeLatencia;
} tPeso;

typedef int tVertice;

typedef struct {
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArista;

typedef bool conjuntoVertices[MAX];

typedef tPeso conjuntoAristas[MAX][MAX];

typedef char tString[MAXSTRING];

typedef struct {
    conjuntoVertices vertices;
    conjuntoAristas aristas;
    int cantVertices;
    tString etiquetas[MAX];
} tGrafoRedComputadoras;

// Prototipado
void agregarArista(tGrafoRedComputadoras*, tArista);
void eliminarArista(tGrafoRedComputadoras*, tArista);
bool existeVertice(tGrafoRedComputadoras, tVertice);
bool existeArista(tGrafoRedComputadoras, tVertice, tVertice);
void visualizarMatriz(tGrafoRedComputadoras);

// Funciones
void agregarArista(tGrafoRedComputadoras* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true && pGrafo->vertices[pArista.destino] == true) {
        pGrafo->aristas[pArista.origen][pArista.destino].velocidadEnlace = pArista.peso.velocidadEnlace;
        pGrafo->aristas[pArista.origen][pArista.destino].nivelDeLatencia = pArista.peso.nivelDeLatencia;

        pGrafo->aristas[pArista.destino][pArista.origen].velocidadEnlace = pArista.peso.velocidadEnlace;
        pGrafo->aristas[pArista.destino][pArista.origen].nivelDeLatencia = pArista.peso.nivelDeLatencia;

        printf("Arista agregada correctamente.\n");
    } else {
        printf("Error al agregar la arista.\n");
    }
}

void eliminarArista(tGrafoRedComputadoras* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true && pGrafo->vertices[pArista.destino] == true) {
        pGrafo->aristas[pArista.origen][pArista.destino].velocidadEnlace = 0.0;
        pGrafo->aristas[pArista.origen][pArista.destino].nivelDeLatencia = 0.0;
        ;

        pGrafo->aristas[pArista.destino][pArista.origen].velocidadEnlace = 0.0;
        ;
        pGrafo->aristas[pArista.destino][pArista.origen].nivelDeLatencia = 0.0;
        ;

        printf("Arista eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la arista.\n");
    }
}

bool existeVertice(tGrafoRedComputadoras pGrafo, tVertice pVertice) {
    return (pVertice >= 0 && pVertice < MAX && pGrafo.vertices[pVertice] == true);
}

bool existeArista(tGrafoRedComputadoras pGrafo, tVertice origen, tVertice destino) {
    return (existeVertice(pGrafo, origen) && existeVertice(pGrafo, destino) &&
            (pGrafo.aristas[origen][destino].nivelDeLatencia != 0.0 ||
             pGrafo.aristas[origen][destino].velocidadEnlace != 0.0));
}

void visualizarMatriz(tGrafoRedComputadoras pGrafo) {
    if (!pGrafo.cantVertices) {
        printf("Error: no existen vertices.\n");
        return;
    }

    // Imprimir cabecera
    printf("--- Matriz adyacencia ---\n");
    printf("     ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d |", i);
    }
    printf("\n");

    // Imprimir linea separadora
    printf("     ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("----");
    }
    printf("\n");

    // Imprimir matriz
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d |", i);
        for (int j = 0; j < pGrafo.cantVertices; j++) {
            if (existeArista(pGrafo, i, j)) {
                printf("(%.2fmbps | %.2fms)",
                       pGrafo.aristas[i][j].velocidadEnlace,
                       pGrafo.aristas[i][j].nivelDeLatencia);
            } else {
                printf("    ---    ");
            }
        }
        printf(" (%s)", pGrafo.etiquetas[i]);
    }
    printf("\n");
}

#endif