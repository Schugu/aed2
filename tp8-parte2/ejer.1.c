// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define TITULO "\n*** INFORME DE MOVIMIENTOS ***\n"
#define MAXNOMBRE 50
#define ARCHIVO "movimientos.dat"

// Tipos
typedef char tString[MAXNOMBRE];

typedef struct {
    int nroCuenta;
    tString nombreCliente;
    int codOperacion;
    float importe;
} tMovimiento;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unaOperacion();
void finCorte();

// Variables globales
FILE* movimientos;
tMovimiento movimiento, movimientoAnterior;

int cantDep, cantExt;
float totalDep, totalExt;
float totalDepGral = 0, totalExtGral = 0;

// Función principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();
}

// Funciones
void imprimirCabecera() {
    printf("%s\n", TITULO);
    printf("Nro. Cuenta\t\t | Deposito\t\t | Extraccion\n");
    printf("---------------------------------------------------------\n");
}

void imprimirLinea() {
    printf("%d\t\t\t | ", movimiento.nroCuenta);
    if (movimiento.codOperacion == 1) {
        printf("$%.2f\t\t | $0.0\n", movimiento.importe);
    } else {
        printf("$0.0\t\t\t | $%.2f\n", movimiento.importe);
    }
}

void imprimirTotalesCuenta() {
    printf("---------------------------------------------------------\n");
    printf("Total\t\t\t | $%.2f\t\t | $%.2f\n", totalDep, totalExt);
    printf("Cantidad de mov.\t | %d\t\t\t | %d\n", cantDep, cantExt);
    printf("---------------------------------------------------------\n\n");
}

void inicializacion() {
    movimientos = fopen(ARCHIVO, "rb");
    if (!movimientos) {
        printf("No se encontro el archivo \n");
        exit(EXIT_FAILURE);
    }

    fread(&movimiento, sizeof(tMovimiento), 1, movimientos);
    movimientoAnterior = movimiento;
    cantDep = 0;
    cantExt = 0;
    totalDep = 0;
    totalExt = 0;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(movimientos)) {
        principioCorte();
        while (!feof(movimientos) && movimiento.nroCuenta == movimientoAnterior.nroCuenta) {
            unaOperacion();
            fread(&movimiento, sizeof(tMovimiento), 1, movimientos);
        }
        finCorte();
    }
}

void principioCorte() {
    cantDep = 0;
    cantExt = 0;
    totalDep = 0;
    totalExt = 0;
}

void unaOperacion() {
    imprimirLinea();

    if (movimiento.codOperacion == 1) {
        totalDep += movimiento.importe;
        cantDep++;
    } else {
        totalExt += movimiento.importe;
        cantExt++;
    }
}

void finCorte() {
    imprimirTotalesCuenta();

    totalDepGral += totalDep;
    totalExtGral += totalExt;

    movimientoAnterior = movimiento;
}

void finalizacion() {
    printf("Total depositos: $%.2f\tTotal extracciones: $%.2f\n",
           totalDepGral, totalExtGral);
    fclose(movimientos);
}