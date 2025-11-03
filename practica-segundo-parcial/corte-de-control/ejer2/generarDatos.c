#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "pedidos.dat"

typedef char tString[30];

typedef struct {
    tString fecha;   // AAAAMMDD
    tString codigo;  // código de cliente
    float importe;   // monto del pedido
} tPedido;

int main() {
    FILE* f = fopen(ARCHIVO, "wb");
    if (!f) {
        printf("Error al crear el archivo %s\n", ARCHIVO);
        return 1;
    }

    tPedido pedidos[] = {
        {"20230101", "Cliente-001", 3500},
        {"20230101", "Cliente-002", 3000},
        {"20230101", "Cliente-003", 2800},

        {"20230102", "Cliente-001", 4000},
        {"20230102", "Cliente-003", 3500},

        {"20230103", "Cliente-002", 5000},
        {"20230103", "Cliente-003", 4500}
    };

    int n = sizeof(pedidos) / sizeof(pedidos[0]);
    for (int i = 0; i < n; i++)
        fwrite(&pedidos[i], sizeof(tPedido), 1, f);

    fclose(f);
    printf("Archivo '%s' generado correctamente con %d registros.\n", ARCHIVO, n);
    return 0;
}
