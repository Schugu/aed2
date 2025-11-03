// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "autos.dat"
#define MAXSTRING 30

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    int codigo;
    tString descripcion;
    int stock;
} tAuto;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unAuto();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirMenorCantidad();

// Variables globales
FILE* autos;

tAuto autom, automAnterior;

tString categorias[4] = {"Sedanes", "SUVs", "Camionetas", "Coupes"};

struct {
    int codigo;
    int stock;
} menorCantidadStock;

int total;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("\t *** INFORME DE STOCK DE VEHICULOS POR CATEGORIA ***\n");
    printf("CATEGORIA DE VEHICULO\t | CANTIDAD DE VEHICULOS CON STOCK\n");
    printf("------------------------------------------------------------------\n");
}

void imprimirLinea() {
    printf("%s\t\t\t | %d vehiculos\n", categorias[autom.codigo - 1], total);
    printf("------------------------------------------------------------------\n");
}

void imprimirMenorCantidad() {
    printf("Categoria con menor cantidad de stock disponible: %s - Hay (%d) vehiculos en stock",
           categorias[menorCantidadStock.codigo - 1], menorCantidadStock.stock);
}

void inicializacion() {
    autos = fopen(ARCHIVO, "rb");
    if (!autos) {
        printf("Error: no se pudo abrir el archivo.");
        exit(EXIT_FAILURE);
    }

    fread(&autom, sizeof(tAuto), 1, autos);

    menorCantidadStock.stock = 0;
    total = 0;

    automAnterior = autom;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(autos)) {
        principioCorte();
        while (!feof(autos) && autom.codigo == automAnterior.codigo) {
            unAuto();
            fread(&autom, sizeof(tAuto), 1, autos);
        }
        finCorte();
    }
}

void principioCorte() {
    total = 0;
}

void unAuto() {
    total++;
}

void finCorte() {
    imprimirLinea();

    if (menorCantidadStock.stock == 0 || menorCantidadStock.stock > total) {
        menorCantidadStock.stock = total;
        menorCantidadStock.codigo = autom.codigo;
    }
    automAnterior = autom;
}

void finalizacion() {
    imprimirMenorCantidad();

    fclose(autos);
}
