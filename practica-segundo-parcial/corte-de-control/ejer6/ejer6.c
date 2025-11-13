/*
    Archivos Binarios: Corte de Control

    2. (5 ptos) Se dispone de un archivo llamado Ventas.dat que contiene las ventas diarias de los vendedores de una empresa durante una semana. El archivo está ordenado por código de vendedor. Cada registro tiene el siguiente formato: Código de Vendedor (int) | Día (int) | Monto de Venta (float).
    El archivo contiene varios registros por vendedor correspondientes a diferentes días.

    Se solicita aplicar la técnica de corte de control en el archivo dado para generar un informe que muestre:
    Por cada vendedor: total de ventas, importe de ventas promedio.
    Totales generales: total general de ventas, cantidad de vendedores, vendedor con mayor importe total.

    Formato de salida esperado:
    *** Informe de Ventas por Vendedor ***

    Vendedor: 101
    Total: $5,600.50 | Promedio: $1,866.83

    Vendedor: 102
    Total: $6,100.75 | Promedio: $3,050.38

    RESUMEN GENERAL
    Total general: $11,701.25
    Cantidad de vendedores: 2
    Vendedor con mayor total: 102 ($6,100.75)

    Nota: En este ejercicio de archivos, no es necesario que se incluyan los prototipos de funciones, tampoco las librerías, de este modo nos ahorramos líneas de código en esta modalidad escrita en papel.
*/

// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "ventas.dat"

// Tipos
typedef struct {
    int codVendedor;
    int dia;
    float monto;
} tVenta;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unCorte();
void finCorte();

void imprimirCabecera();
void imprimirSubTotales();
void imprimirTotalesGenerales();

// Variables globales
FILE* ventas;
tVenta venta, ventaAnterior;

float subTotalVentas, totalVentas, subPromedioVentas;
int cantVendedores, cantVentas;

struct {
    int codVendedor;
    float importeTotal;
} mayorImproteTotal;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("*** Informe de ventas por vendedor.\n");
}

void imprimirSubTotales() {
    printf("Vendedor: %d\n", ventaAnterior.codVendedor);
    printf("----------------------------------\n");
    printf("\tTotal: $%.2f | Promedio: $%.2f\n", subTotalVentas, subPromedioVentas);
}

void imprimirTotalesGenerales() {
    printf("RESUMEN GENERAL\n");
    printf("-----------------------------------\n");
    printf("Total general: $%.2f\n", totalVentas);
    printf("Cantidad de vendedores: %d\n", cantVendedores);
    printf("Vendedor con mayor total: %d (%.2f)\n",
           mayorImproteTotal.codVendedor, mayorImproteTotal.importeTotal);
}

void inicializacion() {
    ventas = fopen(ARCHIVO, "rb");
    if (!ventas) {
        printf("Error: no se pudo abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }
    fread(&venta, sizeof(tVenta), 1, ventas);

    ventaAnterior = venta;

    subTotalVentas = 0;
    totalVentas = 0;
    subPromedioVentas = 0;
    cantVendedores = 0;
    cantVentas = 0;
    mayorImproteTotal.codVendedor = 0;
    mayorImproteTotal.importeTotal = 0;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(ventas)) {
        principioCorte();
        while (!feof(ventas) && venta.codVendedor == ventaAnterior.codVendedor) {
            unCorte();
            fread(&venta, sizeof(tVenta), 1, ventas);
        }
        finCorte();
    }
}

void principioCorte() {
    cantVendedores++;

    subTotalVentas = 0;
    subPromedioVentas = 0;
    cantVentas = 0;
}

void unCorte() {
    subTotalVentas += venta.monto;
    cantVentas++;
}

void finCorte() {
    totalVentas += subTotalVentas;
    subPromedioVentas = subTotalVentas / cantVentas;

    if (subTotalVentas > mayorImproteTotal.importeTotal) {
        mayorImproteTotal.codVendedor = ventaAnterior.codVendedor;
        mayorImproteTotal.importeTotal = subTotalVentas;
    }

    imprimirSubTotales();

    ventaAnterior = venta;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(ventas);
}
