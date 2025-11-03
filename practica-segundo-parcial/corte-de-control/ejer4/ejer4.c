// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "productos.dat"
#define MAXSTRING 30

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    int nroTicket;
    int codProducto;
    tString nombre;
    int codCategoria;
    int cant;
    float precioUnit;
} tProducto;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unProducto();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirSubTotal();
void imprimirTotalesGenerales();

// Variables globales
FILE* productos;
tProducto producto, productoAnterior;
float subTotal, montoTotalRecaudado, totalPan, totalLac, totalPer, totalLim;
tString categorias[4] = {"Panaderia", "Lacteos", "Perfumeria", "Limpieza"};

// Funcion Principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("\t *** INFORME DE VENTAS POR DIA ***\n");
    printf("Nro. ticket\t | Cod de producto\t | Nombre\t | Categoria\t | Cantidad\t | Total\n");
    printf("---------------------------------------------------------------------------------------------------\n");
}

void imprimirLinea() {
    printf("%d\t\t | %d\t\t\t | %s\t | %s\t | %d\t\t | %.2f\n",
           producto.nroTicket, producto.codProducto, producto.nombre,
           categorias[producto.codCategoria - 1], producto.cant, producto.precioUnit);
    printf("---------------------------------------------------------------------------------------------------\n");
}

void imprimirSubTotal() {
    printf("Total: %.2f\n", subTotal);
    printf("---------------------------------------------------------------------------------------------------\n");
}

void imprimirTotalesGenerales() {
    printf("%s: %.2f\n", categorias[0], totalPan);
    printf("%s: %.2f\n", categorias[1], totalLac);
    printf("%s: %.2f\n", categorias[2], totalPer);
    printf("%s: %.2f\n", categorias[3], totalLim);
    printf("Monto total recaudado: %.2f\n", montoTotalRecaudado);
}

void inicializacion() {
    productos = fopen(ARCHIVO, "rb");
    if (!productos) {
        printf("Error: no se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }

    fread(&producto, sizeof(tProducto), 1, productos);
    subTotal = 0;
    totalPan = 0;
    totalLac = 0;
    totalPer = 0;
    totalLim = 0;
    montoTotalRecaudado = 0;

    productoAnterior = producto;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(productos)) {
        principioCorte();
        while (!feof(productos) && producto.nroTicket == productoAnterior.nroTicket) {
            unProducto();
            fread(&producto, sizeof(tProducto), 1, productos);
        }
        finCorte();
    }
}

void principioCorte() {
    subTotal = 0;
}

void unProducto() {
    imprimirLinea();
    switch (producto.codCategoria) {
    case 1:
        totalPan += producto.precioUnit;
        break;
    case 2:
        totalLac += producto.precioUnit;
        break;
    case 3:
        totalPer += producto.precioUnit;
        break;
    case 4:
        totalLim += producto.precioUnit;
        break;
    }
    subTotal += producto.precioUnit;
}

void finCorte() {
    imprimirSubTotal();
    productoAnterior = producto;
    montoTotalRecaudado += subTotal;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(productos);
}