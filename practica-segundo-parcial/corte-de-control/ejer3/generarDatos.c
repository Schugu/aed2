// Programa para generar el archivo autos.dat con datos de prueba
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "autos.dat"
#define MAXSTRING 30

typedef char tString[MAXSTRING];

typedef struct {
    int codigo;
    tString descripcion;
    int stock;
} tAuto;

int main() {
    FILE* archivo;
    tAuto auto_temp;
    
    archivo = fopen(ARCHIVO, "wb");
    if (!archivo) {
        printf("Error: no se pudo crear el archivo.\n");
        return 1;
    }
    
    // Categoría 1: Sedanes (5 vehículos)
    auto_temp.codigo = 1;
    strcpy(auto_temp.descripcion, "Toyota Corolla");
    auto_temp.stock = 5;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 1;
    strcpy(auto_temp.descripcion, "Honda Civic");
    auto_temp.stock = 3;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 1;
    strcpy(auto_temp.descripcion, "Ford Fusion");
    auto_temp.stock = 8;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 1;
    strcpy(auto_temp.descripcion, "Mazda 3");
    auto_temp.stock = 4;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 1;
    strcpy(auto_temp.descripcion, "Nissan Sentra");
    auto_temp.stock = 6;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    // Categoría 2: SUVs (3 vehículos) - MENOR CANTIDAD
    auto_temp.codigo = 2;
    strcpy(auto_temp.descripcion, "Jeep Cherokee");
    auto_temp.stock = 2;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 2;
    strcpy(auto_temp.descripcion, "Toyota RAV4");
    auto_temp.stock = 7;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 2;
    strcpy(auto_temp.descripcion, "Honda CR-V");
    auto_temp.stock = 5;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    // Categoría 3: Camionetas (6 vehículos)
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "Ford F-150");
    auto_temp.stock = 4;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "Chevrolet Silverado");
    auto_temp.stock = 3;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "RAM 1500");
    auto_temp.stock = 6;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "Toyota Hilux");
    auto_temp.stock = 8;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "Nissan Frontier");
    auto_temp.stock = 2;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 3;
    strcpy(auto_temp.descripcion, "Ford Ranger");
    auto_temp.stock = 5;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    // Categoría 4: Coupés (4 vehículos)
    auto_temp.codigo = 4;
    strcpy(auto_temp.descripcion, "BMW Serie 3 Coupe");
    auto_temp.stock = 7;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 4;
    strcpy(auto_temp.descripcion, "Audi A5");
    auto_temp.stock = 9;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 4;
    strcpy(auto_temp.descripcion, "Mercedes C-Class Coupe");
    auto_temp.stock = 3;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    auto_temp.codigo = 4;
    strcpy(auto_temp.descripcion, "Ford Mustang");
    auto_temp.stock = 6;
    fwrite(&auto_temp, sizeof(tAuto), 1, archivo);
    
    fclose(archivo);
    
    printf("Archivo 'autos.dat' creado exitosamente!\n\n");
    printf("Datos generados:\n");
    printf("- Sedanes: 5 vehiculos\n");
    printf("- SUVs: 3 vehiculos (MENOR CANTIDAD)\n");
    printf("- Camionetas: 6 vehiculos\n");
    printf("- Coupes: 4 vehiculos\n");
    
    return 0;
}