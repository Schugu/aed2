// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define ARCHIVO "inventario.dat"
#define MAXSTRING 50

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    tString fecha;
    int entrantes;
    int salientes;
} tInventario;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unInventario();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirTotalesGenerales();

// Variables globales
int totalDias, subTotalEntrantes, subTotalSalidas;

tInventario inventario, inventarioAnterior;

struct {
    tString fecha;
    int cant;
} maxDiasSalientes;

FILE* inventarios;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("\t\t *** Informe de inventario por dia ***\n");
    printf("Fecha\t\t\t | Total de entradas\t | Total de salidas\n");
    printf("-------------------------------------------------------------------\n");
}

void imprimirLinea() {
    printf("%s\t\t | %d\t\t\t | %d\n", inventario.fecha, subTotalEntrantes, subTotalSalidas);
    printf("-------------------------------------------------------------------\n");
}

void imprimirTotalesGenerales() {
    printf("Total de dias registrados en el mes: %d\n", totalDias);
    printf("-------------------------------------------------------------------\n");
    printf("Dia con mas articulos salientes: %s (%d salidas)\n", maxDiasSalientes.fecha, maxDiasSalientes.cant);
    printf("-------------------------------------------------------------------\n");
}

void inicializacion() {
    inventarios = fopen(ARCHIVO, "rb");

    if (!inventarios) {
        printf("Error: no se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }

    fread(&inventario, sizeof(tInventario), 1, inventarios);

    totalDias = 0;
    subTotalEntrantes = 0;
    subTotalSalidas = 0;

    maxDiasSalientes.cant = 0;

    inventarioAnterior = inventario;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(inventarios)) {
        principioCorte();
        while (!feof(inventarios) && strcmp(inventario.fecha, inventarioAnterior.fecha) == 0) {
            unInventario();
            fread(&inventario, sizeof(tInventario), 1, inventarios);
        }
        finCorte();
    }
}

void principioCorte() {
    subTotalEntrantes = 0;
    subTotalSalidas = 0;
}

void unInventario() {
    subTotalEntrantes += inventario.entrantes;
    subTotalSalidas += inventario.salientes;
}

void finCorte() {
    imprimirLinea();
    totalDias++;
    inventarioAnterior = inventario;

    if (maxDiasSalientes.cant < subTotalSalidas) {
        strcpy(maxDiasSalientes.fecha, inventario.fecha);
        maxDiasSalientes.cant = subTotalSalidas;
    }
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(inventarios);
}