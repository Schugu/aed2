#ifndef GRAFOREDSOCIAL_h
#define GRAFOREDSOCIAL_H

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constantes
#define MAX 50
#define MAXSTRING 30

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    int intensidad;
    tString fechaPrimeraInteraccion;
} tPeso;

typedef int tVertice;

typedef struct {
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArco;

typedef bool conjuntoVertices[MAX];

typedef tPeso conjuntoArcos[MAX][MAX];

typedef struct {
    conjuntoVertices vertices;
    conjuntoArcos arcos;
    int cantVertices;
} tGrafoRedSocial;

// Prototipado
void inicializarGrafo(tGrafoRedSocial*);
void agregarVertice(tGrafoRedSocial*, tVertice);
void agregarArco(tGrafoRedSocial*, tArco);

// Funcioens
void inicializarGrafo(tGrafoRedSocial* pGrafo) {
    pGrafo->cantVertices = 0;
    for (int i = 0; i < MAX; i++) {
        pGrafo->vertices[i] = false;
        for (int j = 0; j < MAX; j++) {
            pGrafo->arcos[i][j].intensidad = 0;
            strcpy(pGrafo->arcos[i][j].fechaPrimeraInteraccion, " ");
        }
    }
}

void agregarVertice(tGrafoRedSocial* pGrafo, tVertice pVertice) {
    if (!pGrafo->vertices[pVertice]) {
        pGrafo->vertices[pVertice] = true;
        pGrafo->cantVertices++;
        printf("Vertice agregado con exito.\n");
    } else {
        printf("El vertice ya existe.\n");
    }
}

void agregarArco(tGrafoRedSocial* pGrafo, tArco pArco) {
    if (pGrafo->vertices[pArco.origen] == true &&
        pGrafo->vertices[pArco.destino] == true) {

        pGrafo->arcos[pArco.origen][pArco.destino].intensidad = pArco.peso.intensidad;
        strcpy(pGrafo->arcos[pArco.origen][pArco.destino].fechaPrimeraInteraccion, pArco.peso.fechaPrimeraInteraccion);

        pGrafo->arcos[pArco.destino][pArco.origen].intensidad = pArco.peso.intensidad;
        strcpy(pGrafo->arcos[pArco.destino][pArco.origen].fechaPrimeraInteraccion, pArco.peso.fechaPrimeraInteraccion);
    
        printf("Arco agregado exitosamente.\n");
    } else {
        printf("Error: vertices invalidos.\n");
    }
}

#endif