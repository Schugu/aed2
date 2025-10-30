// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAXSTRING 50
#define ARCHIVO "alumnos.dat"

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
    int nroLibreta;
    tString nombreApellido;
    int codMateria;
    float nota;
} tAlumno;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unaOperacion();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirTotales();

// Variables globales
float notaPromedio, acumNotasAlumno;
int totalAlumnos, contNotasAlumno;
struct {
    tString nombreApellido;
    float promedio;
} mejorPromedio;

FILE* alumnos;
tAlumno alumno, alumnoAnterior;

// Función principal
int main() {
    inicializacion();
    procesoCorte();
    finalizacion();

    return 0;
}

// Funciones
void imprimirCabecera() {
    printf("*** Listado de promedios ***\n\n");
    printf("Numero de libreta\t Nota promedio\n");
}

void imprimirLinea() {
    printf("%d\t\t\t %.2f%%\n", alumnoAnterior.nroLibreta, notaPromedio);
}

void imprimirTotales() {
    printf("Total de alumnos: %d\n", totalAlumnos);
    printf("El alumno con mayor promedio es: %s - obtuvo: %.2f%%", mejorPromedio.nombreApellido, mejorPromedio.promedio);
}

void inicializacion() {
    alumnos = fopen(ARCHIVO, "rb");
    if (!alumnos) {
        printf("Error: no se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fread(&alumno, sizeof(tAlumno), 1, alumnos);

    alumnoAnterior = alumno;
    totalAlumnos = 0;
    mejorPromedio.promedio = 0;

    imprimirCabecera();
}

void procesoCorte() {
    while (!feof(alumnos)) {
        principioCorte();
        while (!feof(alumnos) && alumno.nroLibreta == alumnoAnterior.nroLibreta) {
            unaOperacion();
            fread(&alumno, sizeof(tAlumno), 1, alumnos);
        }
        finCorte();
    }
}

void principioCorte() {
    acumNotasAlumno = 0;
    contNotasAlumno = 0;
    notaPromedio = 0;
}

void unaOperacion() {
    acumNotasAlumno += alumno.nota;
    contNotasAlumno++;
}

void finCorte() {
    notaPromedio = acumNotasAlumno / contNotasAlumno;
    imprimirLinea();

    if (notaPromedio > mejorPromedio.promedio) {
        strcpy(mejorPromedio.nombreApellido, alumnoAnterior.nombreApellido);
        mejorPromedio.promedio = notaPromedio;
    }

    totalAlumnos++;
    alumnoAnterior = alumno;
}

void finalizacion() {
    imprimirTotales();
    fclose(alumnos);
}