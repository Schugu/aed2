// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAXSTRING 50
#define ARCHIVO "archivosImprimir.dat"

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    tString ip;
    tString nombre;
    int tipo;
    int tamanio;
} tArchivo;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unaOperacion();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirSubTotales();
void imprimriTotalesGenerales();

// Variables globales
FILE* archivos;

tString extensiones[5] = {"docx", "pdf", "jpg", "png", "xlsx"};

int totalDocumentos, totalTamanio, subTotalDocumentos, subTotalTamanio, totalDocumentosImagenes;

tArchivo archivo, archivoAnterior;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("\t\t *** Documentos impresos ***\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-10s\n", "IP", "Documento", "Tamanio (bytes)");
    printf("----------------------------------------------------------------------------\n");
}

void imprimirLinea() {
    char nombreCompleto[100];
    sprintf(nombreCompleto, "%s-%s", archivo.nombre, extensiones[archivo.tipo]);
    printf("%-20s | %-30s | %-10d KB\n", archivo.ip, nombreCompleto, archivo.tamanio);
}

void imprimirSubTotales() {
    printf("----------------------------------------------------------------------------\n");
    printf("%-20s | %-30d | %-10d KB\n", "Cant. Documentos:", subTotalDocumentos, subTotalTamanio);
    printf("----------------------------------------------------------------------------\n");
}

void imprimirTotalesGenerales() {
    printf("----------------------------------------------------------------------------\n");
    printf("%-53s | %-10d\n", "Total de archivos de imagenes impresos:", totalDocumentosImagenes);
    printf("%-53s | %-10d\n", "Total de documentos impresos:", totalDocumentos);
    printf("%-53s | %-10d KB\n", "Total de tamanio:", totalTamanio);
    printf("----------------------------------------------------------------------------\n");
}

void inicializacion() {
    archivos = fopen(ARCHIVO, "rb");
    if (!archivos) {
        printf("Error: no se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fread(&archivo, sizeof(tArchivo), 1, archivos);

    archivoAnterior = archivo;

    totalDocumentos = 0;
    totalTamanio = 0;
    totalDocumentosImagenes = 0;

    subTotalDocumentos = 0;
    subTotalTamanio = 0;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(archivos)) {
        principioCorte();
        while (!feof(archivos) && strcmp(archivo.ip, archivoAnterior.ip) == 0) {
            unaOperacion();
            fread(&archivo, sizeof(tArchivo), 1, archivos);
        }
        finCorte();
    }
}

void principioCorte() {
    subTotalDocumentos = 0;
    subTotalTamanio = 0;
}

void unaOperacion() {
    imprimirLinea();
    subTotalDocumentos++;
    subTotalTamanio += archivo.tamanio;

    totalDocumentos++;
    totalTamanio += archivo.tamanio;

    if (archivo.tipo == 2 || archivo.tipo == 3) {
        totalDocumentosImagenes++;
    }
}

void finCorte() {
    imprimirSubTotales();

    archivoAnterior = archivo;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(archivos);
}