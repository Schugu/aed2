/*
    (2.50 pts) Codificar un tipo de dato tGrafoActividades para modelar un grafo ponderado de hasta 20
    nodos, que representan diferentes actividades recreativas en un parque de diversiones. El peso de
    los arcos es un dato compuesto que representa el tiempo promedio en minutos y el costo en pesos
    argentinos que se requiere para ir de una actividad a otra. Utilizar la implementación de grafos
    con arrays. Además, codificar una función que permita imprimir la matriz de pesos. Los valores de
    los arcos deberán mostrarse como en el siguiente ejemplo: (25 min, $1500.50).
*/
#ifndef GRAFOACTIVIDADES_H
#define GRAFOACTIVIDADES_H

// Librerias
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 20
#define MAXSTRING 30

// Tipos
typedef struct {
    float tiempoPromedioMin;
    float costoPesos;
} tPeso;

typedef int tVertice;

typedef struct {
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArco;

typedef bool conjuntoVertices[MAX];

typedef tPeso conjuntoArcos[MAX][MAX];

typedef char tString[MAX];

typedef struct {
    conjuntoVertices vertices;
    conjuntoArcos arcos;
    int cantVertices;
    tString etiquetas[MAX];
} tGrafoActividades;

// Prototipado
bool existeVertice(tGrafoActividades, tVertice);
bool existeArista(tGrafoActividades, tVertice, tVertice);
void imprimirMatriz(tGrafoActividades);

// Funciones
bool existeVertice(tGrafoActividades pGrafo, tVertice pVertice) {
    return pVertice >= 0 && pVertice < MAX && pGrafo.vertices[pVertice] == true;
}

bool existeArista(tGrafoActividades pGrafo, tVertice origen, tVertice destino) {
    return existeVertice(pGrafo, origen) && existeVertice(pGrafo, destino) &&
           (pGrafo.arcos[origen][destino].costoPesos != 0.0 ||
            pGrafo.arcos[origen][destino].tiempoPromedioMin != 0.0);
}

void imprimirMatriz(tGrafoActividades pGrafo) {
    if (!pGrafo.cantVertices) {
        printf("Error: no existen vertices.\n");
        return;
    }

    // Imprimir cabecera
    printf("--- Matriz de adyacencia ---\n");
    printf("   ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d |", i);
    }
    printf("\n");

    // Imprimir Linea separadora
    printf("  ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("----");
    }
    printf("\n");

    // Imprimir matriz
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        // Imprimir indices
        printf("%3d", i);

        for (int j = 0; j < pGrafo.cantVertices; j++) {
            if (existeArista(pGrafo, i, j)) {
                printf("(%.2fmins, $%.2f)",
                       pGrafo.arcos[i][j].tiempoPromedioMin,
                       pGrafo.arcos[i][j].costoPesos);
            } else {
                printf("    ---    ");
            }
        }
        printf(" (%s)\n", pGrafo.etiquetas[i]);
    }
    printf("\n");
}

#endif