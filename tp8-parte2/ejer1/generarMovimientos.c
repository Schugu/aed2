#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOMBRE 50

typedef char tString[MAXNOMBRE];

typedef struct {
    int nroCuenta;
    tString nombreCliente;
    int codOperacion; 
    float importe;
} tMovimiento;

int main() {
    FILE *f = fopen("movimientos.dat", "wb");
    if (!f) {
        printf("No se pudo crear el archivo.\n");
        return 1;
    }

    tMovimiento movimientos[] = {
        {1001, "Juan Perez", 1, 1500.50},
        {1001, "Juan Perez", 2, 500.00},
        {1001, "Juan Perez", 1, 200.00},
        {1002, "Maria Lopez", 2, 300.00},
        {1002, "Maria Lopez", 1, 1000.00},
        {1003, "Carlos Diaz", 1, 750.00},
        {1003, "Carlos Diaz", 2, 150.00}
    };

    fwrite(movimientos, sizeof(tMovimiento), sizeof(movimientos)/sizeof(tMovimiento), f);
    fclose(f);

    printf("Archivo 'movimientos.dat' creado correctamente.\n");
    return 0;
}
