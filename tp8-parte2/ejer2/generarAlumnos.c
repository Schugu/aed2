#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50
#define ARCHIVO "alumnos.dat"

typedef char tString[MAXSTRING];

typedef struct {
    int nroLibreta;
    tString nombreApellido;
    int codMateria;
    float nota;
} tAlumno;

void cargarAlumno(FILE* archivo, int libreta, const char* nombre, int materia, float nota) {
    tAlumno alumno;
    alumno.nroLibreta = libreta;
    strcpy(alumno.nombreApellido, nombre);
    alumno.codMateria = materia;
    alumno.nota = nota;
    fwrite(&alumno, sizeof(tAlumno), 1, archivo);
}

int main() {
    FILE* alumnos;

    alumnos = fopen(ARCHIVO, "wb");
    if (!alumnos) {
        printf("Error: no se pudo crear el archivo\n");
        return EXIT_FAILURE;
    }

    // Alumno 1001 - 3 materias
    cargarAlumno(alumnos, 1001, "Garcia Juan", 101, 8.5);
    cargarAlumno(alumnos, 1001, "Garcia Juan", 102, 7.0);
    cargarAlumno(alumnos, 1001, "Garcia Juan", 103, 9.0);

    // Alumno 1002 - 4 materias
    cargarAlumno(alumnos, 1002, "Martinez Ana", 101, 9.5);
    cargarAlumno(alumnos, 1002, "Martinez Ana", 102, 10.0);
    cargarAlumno(alumnos, 1002, "Martinez Ana", 103, 9.0);
    cargarAlumno(alumnos, 1002, "Martinez Ana", 104, 8.5);

    // Alumno 1003 - 2 materias
    cargarAlumno(alumnos, 1003, "Lopez Carlos", 101, 6.0);
    cargarAlumno(alumnos, 1003, "Lopez Carlos", 102, 7.5);

    // Alumno 1004 - 3 materias
    cargarAlumno(alumnos, 1004, "Fernandez Maria", 101, 8.0);
    cargarAlumno(alumnos, 1004, "Fernandez Maria", 103, 8.5);
    cargarAlumno(alumnos, 1004, "Fernandez Maria", 104, 9.0);

    // Alumno 1005 - 2 materias
    cargarAlumno(alumnos, 1005, "Rodriguez Pedro", 102, 7.0);
    cargarAlumno(alumnos, 1005, "Rodriguez Pedro", 104, 6.5);

    fclose(alumnos);

    return 0;
}