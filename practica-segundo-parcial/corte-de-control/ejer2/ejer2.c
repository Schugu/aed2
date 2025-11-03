// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define ARCHIVO "pedidos.dat"
#define MAXSTRING 30

// TIPOS
typedef char tString[MAXSTRING];

typedef struct {
    tString fecha;
    tString codigo;
    float importe;
} tPedido;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unPedido();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirMayorPedidoDia();
void imprimirTotalesGenerales();

// Variables
FILE* pedidos;

tPedido pedido, pedidoAnterior;

struct {
    tString codigo;
    float importe;
} mayorPedidoDia;

int totalDias;
float importeTotalGeneral;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funcioones
void imprimirCabecera() {
    printf("\t *** Informe de pedidos por dia *** \n");
    printf("Fecha\t | Cliente\t | Importe pedido \n");
    printf("-----------------------------------------------\n");
}

void imprimirLinea() {
    printf("%s\t | %s\t | %.2f\n", pedido.fecha, pedido.codigo, pedido.importe);
}

void imprimirMayorPedidoDia() {
    printf("* Cliente con mayor pedido del dia: %s (importe: %.2f)\n", mayorPedidoDia.codigo, mayorPedidoDia.importe);
    printf("-----------------------------------------------\n");
}

void imprimirTotalesGenerales() {
    printf("Total de dias registrados: %d\n", totalDias);
    printf("Total general de pedidos: $%.2f\n", importeTotalGeneral);
}

void inicializacion() {
    pedidos = fopen(ARCHIVO, "rb");
    if (!pedidos) {
        printf("Error: no se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }

    fread(&pedido, sizeof(tPedido), 1, pedidos);

    totalDias = 0;
    importeTotalGeneral = 0;
    mayorPedidoDia.importe = 0;

    pedidoAnterior = pedido;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(pedidos)) {
        principioCorte();
        while (!feof(pedidos) && strcmp(pedido.fecha, pedidoAnterior.fecha) == 0) {
            unPedido();
            fread(&pedido, sizeof(tPedido), 1, pedidos);
        }
        finCorte();
    }
}

void principioCorte() {
    mayorPedidoDia.importe = 0;
}

void unPedido() {
    imprimirLinea();
    if (mayorPedidoDia.importe < pedido.importe) {
        mayorPedidoDia.importe = pedido.importe;
        strcpy(mayorPedidoDia.codigo, pedido.codigo);
    }
    importeTotalGeneral += pedido.importe;
}

void finCorte() {
    imprimirMayorPedidoDia();
    totalDias++;

    pedidoAnterior = pedido;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(pedidos);
}