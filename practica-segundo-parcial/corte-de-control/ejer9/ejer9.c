/*
    2) (5ptos) Se dispone de un archivo binario llamado InscripcionesCursos.dat que contiene los
    registros de inscripciones a cursos de capacitación de empleados de una empresa durante un semestre.
    El archivo está ordenado por código de curso. Cada registro tiene el siguiente formato: Código de
    curso (int) | Mes (int) | Cantidad de inscriptos (int). El archivo contiene varios registros por
    curso correspondientes a diferentes meses. Se solicita aplicar la técnica de corte de control sobre
    el archivo dado para generar un informe que muestre: Por cada curso: total de inscriptos en el
    semestre y promedio mensual. Totales generales: total general de inscriptos, cantidad de cursos
    procesados y el curso con mayor cantidad total de inscriptos.
    Formato de salida esperado:
            *** Informe de inscripciones por curso ***
    Curso: 301
    ------------------------------------------------
          Total: 145 inscriptos | Promedio: 24.2 inscriptos
    Curso: 305
    ------------------------------------------------
          Total: 180 inscriptos | Promedio: 30.0 inscriptos

    RESUMEN GENERAL
    ------------------------------------------------
    Total general de inscriptos: 325
    Cantidad de cursos: 2
    Curso con mayor total: 305 (180 inscriptos)
*/

// librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "inscripcionesCursos.dat"

// Tipoes
typedef struct {
    int curso;
    int mes;
    int cant;
} tInscripcion;

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
FILE* inscripciones;
tInscripcion inscripcion, inscripcionAnterior;

int subTotal, total, cantCursos, subCantInscripciones;
float subPromedio;

struct {
    int curso;
    int cant;
} mayorTotalCurso;

// Funcion principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("*** Informe de inscripciones por curso ***\n");
}

void imprimirSubTotales() {
    printf("Curso: %d\n", inscripcionAnterior.curso);
    printf("----------------------------------------\n");
    printf("\tTotal: %d inscriptos | Promedio: %.2f\n", subTotal, subPromedio);
}

void imprimirTotalesGenerales() {
    printf("RESUMEN GENERAL\n");
    printf("-----------------------------------------\n");
    printf("Total general de inscriptos: %d\n", total);
    printf("Cantidad de cursos: %d\n", cantCursos);
    printf("Curso con mayor total: %d (%d inscriptos)\n",
           mayorTotalCurso.curso, mayorTotalCurso.cant);
}

void inicializacion() {
    inscripciones = fopen(ARCHIVO, "rb");
    if (!inscripciones) {
        printf("Error: no se pudo abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }
    fread(&inscripcion, sizeof(tInscripcion), 1, inscripciones);
    inscripcionAnterior = inscripcion;

    subTotal = 0;
    total = 0;
    cantCursos = 0;
    subPromedio = 0;
    subCantInscripciones = 0;
    mayorTotalCurso.cant = 0;
    mayorTotalCurso.curso = -1;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(inscripciones)) {
        principioCorte();
        while (!feof(inscripciones) && inscripcion.curso == inscripcionAnterior.curso) {
            unCorte();
            fread(&inscripcion, sizeof(tInscripcion), 1, inscripciones);
        }
        finCorte();
    }
}

void principioCorte() {
    cantCursos++;
    subTotal = 0;
    subPromedio = 0;
    subCantInscripciones = 0;
}

void unCorte() {
    subTotal += inscripcion.cant;
    subCantInscripciones++;
}

void finCorte() {
    total += subTotal;
    subPromedio = subTotal / subCantInscripciones;

    if (mayorTotalCurso.cant < subTotal) {
        mayorTotalCurso.cant = subTotal;
        mayorTotalCurso.curso = inscripcionAnterior.curso;
    }

    imprimirSubTotales();

    inscripcionAnterior = inscripcion;
}

void finalizacion() {
    imprimirTotalesGenerales();
    fclose(inscripciones);
}