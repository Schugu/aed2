#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "inventario.dat"

typedef char tString[50];

typedef struct {
    tString fecha;      // AAAAMMDD
    int entrantes;
    int salientes;
} tInventario;

int main() {
    FILE* f = fopen(ARCHIVO, "wb");
    if (!f) {
        printf("Error al crear el archivo %s\n", ARCHIVO);
        return 1;
    }

    // Creamos un arreglo de estructuras vacío
    tInventario datos[9];

    // Cargamos los registros manualmente
    strcpy(datos[0].fecha, "20230101"); datos[0].entrantes = 30; datos[0].salientes = 10;
    strcpy(datos[1].fecha, "20230101"); datos[1].entrantes = 70; datos[1].salientes = 40;
    strcpy(datos[2].fecha, "20230102"); datos[2].entrantes = 10; datos[2].salientes = 15;
    strcpy(datos[3].fecha, "20230102"); datos[3].entrantes = 10; datos[3].salientes = 15;
    strcpy(datos[4].fecha, "20230103"); datos[4].entrantes = 100; datos[4].salientes = 50;
    strcpy(datos[5].fecha, "20230103"); datos[5].entrantes = 100; datos[5].salientes = 100;
    strcpy(datos[6].fecha, "20230104"); datos[6].entrantes = 25; datos[6].salientes = 10;
    strcpy(datos[7].fecha, "20230104"); datos[7].entrantes = 10; datos[7].salientes = 5;
    strcpy(datos[8].fecha, "20230105"); datos[8].entrantes = 40; datos[8].salientes = 60;

    int n = 9;
    for (int i = 0; i < n; i++) {
        fwrite(&datos[i], sizeof(tInventario), 1, f);
    }

    fclose(f);
    printf("Archivo '%s' generado correctamente con %d registros.\n", ARCHIVO, n);
    return 0;
}
