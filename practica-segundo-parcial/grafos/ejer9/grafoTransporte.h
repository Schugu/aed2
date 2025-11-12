/*
    1) (5ptos) Grafos + TDA Desarrollar un Tipo de Dato Abstracto (TDA) llamado tGrafoTransporte para modelar un grafo no dirigido y ponderado con capacidad para hasta 80 vértices, representando las estaciones y conexiones de una red de transporte metropolitano (por ejemplo, trenes o subte). Cada arista contendrá información sobre la distancia en kilómetros entre estaciones y el tiempo promedio de viaje en minutos.
    La implementación del grafo se realizará utilizando arrays. Se solicita:
    Incluir la declaración completa de todos los tipos de datos personalizados necesarios para modelar el grafo.
    Codificar una función para agregar una conexión (arco) entre dos estaciones activas.
    Codificar una función para eliminar una conexión existente entre dos estaciones.
    Codificar una función para mostrar la matriz de conexiones, donde cada celda muestre los datos en el formato: (xx,xx km | xx,xx min)
    Crear un programa que haga uso del TDA, declare una variable del tipo tGrafoTransporte, y utilice las funciones disponibles para gestionar las estaciones y sus conexiones. Nota: Tener en cuenta que los nombres de los tipos de datos personalizados deben ser acordes al problema. Además, es importante incluir los prototipos de funciones por tratarse de un TDA.
*/

#ifndef GRAFICOTRANSPORTE_H
#define GRAFICOTRANSPORTE_H

// Librerias
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 80
#define MAXSTRING 30

// Tipos
typedef struct {
    float distanciaKilom;
    float tiempoPromedio;
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
} tGrafoTransporte;

// Prototipado
void agregarArista(tGrafoTransporte*, tArista);
void eliminarArista(tGrafoTransporte*, tArista);
bool existeVertice(tGrafoTransporte, tVertice);
bool existeArista(tGrafoTransporte, tVertice, tVertice);
void visualizarMatriz(tGrafoTransporte);

// Funciones
void agregarArista(tGrafoTransporte* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true && pGrafo->vertices[pArista.destino] == true) {

        pGrafo->aristas[pArista.origen][pArista.destino].distanciaKilom = pArista.peso.distanciaKilom;
        pGrafo->aristas[pArista.origen][pArista.destino].tiempoPromedio = pArista.peso.tiempoPromedio;

        pGrafo->aristas[pArista.destino][pArista.origen].distanciaKilom = pArista.peso.distanciaKilom;
        pGrafo->aristas[pArista.destino][pArista.origen].tiempoPromedio = pArista.peso.tiempoPromedio;

        printf("Arista agregada exitosamente.\n");
    } else {
        printf("Error al agregar la arista.\n");
    }
}

void eliminarArista(tGrafoTransporte* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true && pGrafo->vertices[pArista.destino] == true) {
        pGrafo->aristas[pArista.origen][pArista.destino].distanciaKilom = 0.0;
        pGrafo->aristas[pArista.origen][pArista.destino].tiempoPromedio = 0.0;

        pGrafo->aristas[pArista.destino][pArista.origen].distanciaKilom = 0.0;
        pGrafo->aristas[pArista.destino][pArista.origen].tiempoPromedio = 0.0;

        printf("Arista eliminada exitosamente.\n");
    } else {
        printf("Error al elimianr la arista.\n");
    }
}

bool existeVertice(tGrafoTransporte pGrafo, tVertice pVertice) {
    return (pVertice >= 0 && pVertice < MAX && pGrafo.vertices[pVertice] == true);
}

bool existeArista(tGrafoTransporte pGrafo, tVertice origen, tVertice destino) {
    return (existeVertice(pGrafo, origen) && existeVertice(pGrafo, destino) &&
                pGrafo.aristas[origen][destino].distanciaKilom != 0.0 ||
            pGrafo.aristas[origen][destino].tiempoPromedio != 0.0);
}

void visualizarMatriz(tGrafoTransporte pGrafo) {
    if (!pGrafo.cantVertices) {
        printf("Error: no existen vertices.\n");
        return;
    }

    // Imprimir cabecera
    printf("--- Matriz de adyacencia ---\n");
    printf("    ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d |", i);
    }
    printf("\n");

    // Imprimir linea separadora
    printf("   ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("----");
    }
    printf("\n");

    // Imprimir matriz
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d |", i);
        for (int j = 0; j < pGrafo.cantVertices; j++) {
            if (existeArista(pGrafo, i, j)) {
                printf("(%.2fkm | %.2fmin)",
                       pGrafo.aristas[i][j].distanciaKilom,
                       pGrafo.aristas[i][j].tiempoPromedio);
            } else {
                printf("    ---    ");
            }
        }
        printf(" (%s)", pGrafo.etiquetas[i]);
    }
    printf("\n");
}
#endif