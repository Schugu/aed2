/*
    2) (5ptos) Se dispone de un archivo binario llamado Facturacion.dat que contiene los registros
    diarios de facturación de distintos locales comerciales durante un mes. El archivo está ordenado
    por código de local. Cada registro tiene el siguiente formato: Código de local (int) | Día (int)
    | Importe facturado (float). El archivo contiene varios registros por local correspondientes a
    diferentes días. Se solicita aplicar la técnica de corte de control en el archivo dado para generar
    un informe que muestre: Por cada local: total facturado en el mes y promedio diario. Totales
    generales: total general de facturación, cantidad de locales procesados y local con mayor importe
    total.
    Formato de salida esperado:
    *** Informe de facturación por local ***
    Local: 301
    ------------------------------------------------
          Total: $15230.50 | Promedio: $5076.83
    Local: 304
    ------------------------------------------------
          Total: $18400.75 | Promedio: $6133.58

    RESUMEN GENERAL
    ------------------------------------------------
    Total general: $33631.25
    Cantidad de locales: 2
    Local con mayor total: 304 ($18400.75)
*/

// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "facturacion.dat"

// Tipos
typedef struct {
    int codLocal;
    int dia;
    float importe;
} tFactura;

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
FILE* facturas;
tFactura factura, facturaAnterior;

float subTotal, total, promedio;
int cantLocales, subCantFacturas;

struct {
    int codLocal;
    float importe;
} localMayorImporte;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("*** Informe de facturacion por local ***\n");
}

void imprimirSubTotales() {
    printf("Local: %d\n", facturaAnterior.codLocal);
    printf("--------------------------------------\n");
    printf("\tTotal: $%.2f | Promedio: $%.2f\n", subTotal, promedio);
}

void imprimirTotalesGenerales() {
    printf("RESUMEN GENERAL\n");
    printf("---------------------------------------\n");
    printf("Total general: $%.2f\n", total);
    printf("Cantidad de locales: %d\n", cantLocales);
    printf("Local con mayor total: %d ($%.2f)\n",
           localMayorImporte.codLocal, localMayorImporte.importe);
}

void inicializacion() {
    facturas = fopen(ARCHIVO, "rb");
    if (!facturas) {
        printf("Error: no se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }
    fread(&factura, sizeof(tFactura), 1, facturas);
    facturaAnterior = factura;

    subTotal = 0;
    promedio = 0;
    total = 0;
    cantLocales = 0;
    subCantFacturas = 0;
    localMayorImporte.codLocal = -1;
    localMayorImporte.importe = 0;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(facturas)) {
        principioCorte();
        while (!feof(facturas) && factura.codLocal == facturaAnterior.codLocal) {
            unCorte();
            fread(&factura, sizeof(tFactura), 1, facturas);
        }
        finCorte();
    }
}

void principioCorte() {
    cantLocales++;
    subCantFacturas = 0;
    subTotal = 0;
    promedio = 0;
}

void unCorte() {
    subTotal += factura.importe;
    subCantFacturas++;
}

void finCorte() {
    total += subTotal;
    promedio = subTotal / subCantFacturas;

    if (localMayorImporte.importe < subTotal) {
        localMayorImporte.codLocal = facturaAnterior.codLocal;
        localMayorImporte.importe = subTotal;
    }

    imprimirSubTotales();

    facturaAnterior = factura;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(facturas);
}