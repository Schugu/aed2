/*
    Archivos Binarios: Corte de Control
    (5 pts) Se dispone de un archivo llamado Pedidos.dat que contiene los pedidos realizados a diferentes proveedores durante un trimestre. El archivo está ordenado por código de proveedor. Cada registro tiene el siguiente formato:
    Código de Proveedor (int) | Número de Pedido (int) | Monto (float).
    El archivo contiene varios registros por proveedor correspondientes a diferentes pedidos realizados.

    Se solicita aplicar la técnica de corte de control en el archivo dado para generar un informe que muestre:
    Por cada proveedor: monto total de pedidos, cantidad de pedidos realizados.
    Totales generales: monto total general, cantidad de proveedores, proveedor con menor importe total.

    Formato de salida esperado:
    *** Informe de Pedidos por Proveedor ***
    Proveedor: 301
    Total: $25,000.00 | Cantidad de pedidos: 5
    Proveedor: 302
    Total: $38,000.00 | Cantidad de pedidos: 6
    Proveedor: 303
    Total: $32,000.00 | Cantidad de pedidos: 3

    RESUMEN GENERAL
    Monto total: $95,000.00
    Cantidad de proveedores: 3
    Proveedor con menor importe total: 303 ($12,000.00)

    Nota: En este ejercicio de archivos, no es necesario que se incluyan los prototipos de funciones, tampoco las librerías, de este modo nos ahorramos líneas de código en esta modalidad escrita en papel.
*/

// Librerias
#include <stdio.h>
#include <stdlib.h>

// Contantes
#define ARCHIVO "pedidos.dat"

// Tipos
typedef struct {
    int codProveedor;
    int numPedido;
    float monto;
} tPedido;

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
FILE* pedidos;
tPedido pedido, pedidoAnterior;

float subTotalMonto, montoTotal;
int subCantPedidos, cantProveedores;

struct {
    int codProveedor;
    float importe;
} menorImporteTotal;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("*** Informe de pedidos por proveedor ***\n");
}

void imprimirSubTotales() {
    printf("Proveedor: %d\n", pedidoAnterior.codProveedor);
    printf("---------------------------------------------\n");
    printf("\t Total: $%.2f | Cantidad de pedidos: %d\n", subTotalMonto, subCantPedidos);
}

void imprimirTotalesGenerales() {
    printf("RESUMEN GENERAL\n");
    printf("-----------------------------------------------\n");
    printf("Monto total: $%.2f\n", montoTotal);
    printf("Cantidad de proveedores: %d\n", cantProveedores);
    printf("Proveedor con menor importe: %d ($%.2f)\n",
           menorImporteTotal.codProveedor, menorImporteTotal.importe);
}

void inicializacion() {
    pedidos = fopen(ARCHIVO, "rb");
    if (!pedidos) {
        printf("Error: no se pudo abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }
    fread(&pedido, sizeof(tPedido), 1, pedidos);
    pedidoAnterior = pedido;

    subTotalMonto = 0;
    subCantPedidos = 0;
    montoTotal = 0;
    cantProveedores = 0;

    menorImporteTotal.codProveedor = -1;
    menorImporteTotal.importe = 999999999;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(pedidos)) {
        principioCorte();
        while (!feof(pedidos) && pedido.codProveedor == pedidoAnterior.codProveedor) {
            unCorte();
            fread(&pedido, sizeof(tPedido), 1, pedidos);
        }
        finCorte();
    }
}

void principioCorte() {
    subTotalMonto = 0;
    subCantPedidos = 0;
    cantProveedores++;
}

void unCorte(){
    subTotalMonto += pedido.monto;
    subCantPedidos ++;
}

void finCorte(){
    montoTotal += subTotalMonto;

    if (menorImporteTotal.importe > subTotalMonto){
        menorImporteTotal.codProveedor = pedidoAnterior.codProveedor;
        menorImporteTotal.importe = subTotalMonto;
    }

    imprimirSubTotales();

    pedidoAnterior = pedido;
}

void finalizacion(){
    imprimirTotalesGenerales();
    fclose(pedidos);
}