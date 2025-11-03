#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "productos.dat"
#define MAXSTRING 30

typedef char tString[MAXSTRING];

typedef struct {
    int nroTicket;
    int codProducto;
    tString nombre;
    int codCategoria;
    int cant;
    float precioUnit;
} tProducto;

int main() {
    FILE* archivo;
    tProducto prod;
    
    archivo = fopen(ARCHIVO, "wb");
    if (!archivo) {
        printf("Error: no se pudo crear el archivo.\n");
        return 1;
    }
    
    // ========== TICKET 0001 ==========
    // Producto 1: Leche (Lácteos)
    prod.nroTicket = 1;
    prod.codProducto = 112;
    strcpy(prod.nombre, "Leche");
    prod.codCategoria = 2; // Lácteos
    prod.cant = 2;
    prod.precioUnit = 250.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 2: Pan (Panadería)
    prod.nroTicket = 1;
    prod.codProducto = 212;
    strcpy(prod.nombre, "Pan");
    prod.codCategoria = 1; // Panadería
    prod.cant = 1;
    prod.precioUnit = 800.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    // Total ticket 0001: 500.00 + 800.00 = 1300.00
    
    // ========== TICKET 0002 ==========
    // Producto 1: Leche (Lácteos)
    prod.nroTicket = 2;
    prod.codProducto = 112;
    strcpy(prod.nombre, "Leche");
    prod.codCategoria = 2; // Lácteos
    prod.cant = 1;
    prod.precioUnit = 250.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 2: Pan (Panadería)
    prod.nroTicket = 2;
    prod.codProducto = 212;
    strcpy(prod.nombre, "Pan");
    prod.codCategoria = 1; // Panadería
    prod.cant = 2;
    prod.precioUnit = 800.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    // Total ticket 0002: 250.00 + 1600.00 = 1850.00
    
    // ========== TICKET 0003 ==========
    // Producto 1: Yogurt (Lácteos)
    prod.nroTicket = 3;
    prod.codProducto = 113;
    strcpy(prod.nombre, "Yogurt");
    prod.codCategoria = 2; // Lácteos
    prod.cant = 3;
    prod.precioUnit = 150.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 2: Facturas (Panadería)
    prod.nroTicket = 3;
    prod.codProducto = 213;
    strcpy(prod.nombre, "Facturas");
    prod.codCategoria = 1; // Panadería
    prod.cant = 6;
    prod.precioUnit = 100.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 3: Shampoo (Perfumería)
    prod.nroTicket = 3;
    prod.codProducto = 314;
    strcpy(prod.nombre, "Shampoo");
    prod.codCategoria = 3; // Perfumería
    prod.cant = 1;
    prod.precioUnit = 850.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    // Total ticket 0003: 450.00 + 600.00 + 850.00 = 1900.00
    
    // ========== TICKET 0004 ==========
    // Producto 1: Detergente (Limpieza)
    prod.nroTicket = 4;
    prod.codProducto = 415;
    strcpy(prod.nombre, "Detergente");
    prod.codCategoria = 4; // Limpieza
    prod.cant = 2;
    prod.precioUnit = 650.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 2: Lavandina (Limpieza)
    prod.nroTicket = 4;
    prod.codProducto = 416;
    strcpy(prod.nombre, "Lavandina");
    prod.codCategoria = 4; // Limpieza
    prod.cant = 1;
    prod.precioUnit = 380.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    // Total ticket 0004: 1300.00 + 380.00 = 1680.00
    
    // ========== TICKET 0005 ==========
    // Producto 1: Crema (Lácteos)
    prod.nroTicket = 5;
    prod.codProducto = 114;
    strcpy(prod.nombre, "Crema");
    prod.codCategoria = 2; // Lácteos
    prod.cant = 1;
    prod.precioUnit = 420.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 2: Perfume (Perfumería)
    prod.nroTicket = 5;
    prod.codProducto = 315;
    strcpy(prod.nombre, "Perfume");
    prod.codCategoria = 3; // Perfumería
    prod.cant = 1;
    prod.precioUnit = 1500.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    
    // Producto 3: Medialunas (Panadería)
    prod.nroTicket = 5;
    prod.codProducto = 214;
    strcpy(prod.nombre, "Medialunas");
    prod.codCategoria = 1; // Panadería
    prod.cant = 12;
    prod.precioUnit = 80.00;
    fwrite(&prod, sizeof(tProducto), 1, archivo);
    // Total ticket 0005: 420.00 + 1500.00 + 960.00 = 2880.00
    
    fclose(archivo);
    
    printf("Archivo 'productos.dat' creado exitosamente!\n\n");
    printf("=== RESUMEN DE DATOS GENERADOS ===\n\n");
    printf("TICKET 0001:\n");
    printf("  - 2 Leche (Lacteos) @ 250.00 = 500.00\n");
    printf("  - 1 Pan (Panaderia) @ 800.00 = 800.00\n");
    printf("  Total: 1300.00\n\n");
    
    printf("TICKET 0002:\n");
    printf("  - 1 Leche (Lacteos) @ 250.00 = 250.00\n");
    printf("  - 2 Pan (Panaderia) @ 800.00 = 1600.00\n");
    printf("  Total: 1850.00\n\n");
    
    printf("TICKET 0003:\n");
    printf("  - 3 Yogurt (Lacteos) @ 150.00 = 450.00\n");
    printf("  - 6 Facturas (Panaderia) @ 100.00 = 600.00\n");
    printf("  - 1 Shampoo (Perfumeria) @ 850.00 = 850.00\n");
    printf("  Total: 1900.00\n\n");
    
    printf("TICKET 0004:\n");
    printf("  - 2 Detergente (Limpieza) @ 650.00 = 1300.00\n");
    printf("  - 1 Lavandina (Limpieza) @ 380.00 = 380.00\n");
    printf("  Total: 1680.00\n\n");
    
    printf("TICKET 0005:\n");
    printf("  - 1 Crema (Lacteos) @ 420.00 = 420.00\n");
    printf("  - 1 Perfume (Perfumeria) @ 1500.00 = 1500.00\n");
    printf("  - 12 Medialunas (Panaderia) @ 80.00 = 960.00\n");
    printf("  Total: 2880.00\n\n");
    
    printf("=== TOTALES POR CATEGORIA ===\n");
    printf("Panaderia: 3360.00\n");
    printf("Lacteos: 1620.00\n");
    printf("Perfumeria: 2350.00\n");
    printf("Limpieza: 1680.00\n");
    printf("\nMonto total Recaudado: 9010.00\n");
    
    return 0;
}