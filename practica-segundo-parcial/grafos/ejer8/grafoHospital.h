/*
    Grafos + TDA
    (5 ptos) Desarrollar un Tipo de Dato Abstracto (TDA) llamado tGrafoHospital para modelar un grafo
    no dirigido y ponderado con capacidad para hasta 120 vértices, representando áreas críticas de un
    hospital (quirófanos, urgencias, laboratorios, habitaciones). Se debe incluir la declaración
    completa de todos los tipos de datos personalizados necesarios para modelar el grafo. Cada arista
    contendrá información sobre la distancia en metros entre áreas y el tiempo promedio de traslado en
    minutos. La implementación del grafo se realizará utilizando arrays. Además, se solicita:
    Codificar una función para agregar un arco en el grafo definido.
    Codificar una función para visualizar la matriz de pesos, donde la información entre dos áreas
    se muestre de la forma (xx,xx mtrs | xx,xx min).
    Crear un programa que haga uso de este TDA, declare una variable grafo del tipo tGrafoHospital y
    utilice las funciones disponibles para gestionar las áreas del hospital y sus conexiones.
    Nota: Tener en cuenta que los nombres de los tipos de datos personalizados tienen que ser acordes
    al problema. Además, en este caso es importante incluir los prototipos de funciones por ser TDA.
*/
#ifndef GRAFOHOSPITAL_H
#define GRAFOHOSPITAL_H

// Librerias
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 120
#define MAXSTRING 30

// Tipos
typedef struct {
    float distanciaMetros;
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
} tGrafoHospital;

// Prototipado
bool existeVertice(tGrafoHospital, tVertice);
bool existeArista(tGrafoHospital, tVertice, tVertice);
void agregarArista(tGrafoHospital*, tArista);
void visualizarMatriz(tGrafoHospital);

// Funciones
bool existeVertice(tGrafoHospital pGrafo, tVertice pVertice) {
    return pVertice >= 0 && pVertice < MAX && pGrafo.vertices[pVertice] == true;
}

bool existeArista(tGrafoHospital pGrafo, tVertice origen, tVertice destino) {
    return existeVertice(pGrafo, origen) && existeVertice(pGrafo, destino) &&
           (pGrafo.aristas[origen][destino].distanciaMetros != 0.0 || pGrafo.aristas[origen][destino].tiempoPromedio != 0.0);
}

void agregarArista(tGrafoHospital* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true && pGrafo->vertices[pArista.destino] == true) {
        pGrafo->aristas[pArista.origen][pArista.destino].distanciaMetros = pArista.peso.distanciaMetros;
        pGrafo->aristas[pArista.origen][pArista.destino].tiempoPromedio = pArista.peso.tiempoPromedio;

        pGrafo->aristas[pArista.destino][pArista.origen].distanciaMetros = pArista.peso.distanciaMetros;
        pGrafo->aristas[pArista.destino][pArista.origen].tiempoPromedio = pArista.peso.tiempoPromedio;

        printf("Arista agregada correctamente.\n");
    } else {
        printf("Error al agregar la arista.\n");
    }
}

void visualizarMatriz(tGrafoHospital pGrafo) {
    if (!pGrafo.cantVertices) {
        printf("Error: no existen vertices.\n");
        return;
    }

    // Imprimir cabecera
    printf("--- Matriz de adyacencia ---\n");
    printf("   ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%3d| ", i);
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
        printf("%3d ", i);
        for (int j = 0; j < pGrafo.cantVertices; j++) {
            if (existeArista(pGrafo, i, j)) {
                printf("(%.2f mtrs | %.2f min)",
                       pGrafo.aristas[i][j].distanciaMetros,
                       pGrafo.aristas[i][j].tiempoPromedio);
            } else {
                pritnf("    ---    ");
            }
        }
        printf(" (%s)\n", pGrafo.etiquetas[i]);
    }
    printf("\n");
}

#endif