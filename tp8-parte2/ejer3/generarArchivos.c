#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50
#define ARCHIVO "archivosImprimir.dat"

typedef char tString[MAXSTRING];

typedef struct {
    tString ip;
    tString nombre;
    int tipo;
    int tamano;
} tArchivo;

int main() {
    FILE* archivo;
    tArchivo doc;
    
    archivo = fopen(ARCHIVO, "wb");
    if (!archivo) {
        printf("Error: no se pudo crear el archivo\n");
        return EXIT_FAILURE;
    }
    
    // Datos para IP: 192.168.2.1
    strcpy(doc.ip, "192.168.2.1");
    strcpy(doc.nombre, "lista");
    doc.tipo = 0; // docx
    doc.tamano = 30720; // 30 KB
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.1");
    strcpy(doc.nombre, "foto1");
    doc.tipo = 2; // jpg
    doc.tamano = 10240; // 10 KB
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.1");
    strcpy(doc.nombre, "Libro");
    doc.tipo = 1; // pdf
    doc.tamano = 5120; // 5 KB
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    // Datos para IP: 192.168.2.2
    strcpy(doc.ip, "192.168.2.2");
    strcpy(doc.nombre, "informe");
    doc.tipo = 0; // docx
    doc.tamano = 45000;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.2");
    strcpy(doc.nombre, "presentacion");
    doc.tipo = 4; // xlsx
    doc.tamano = 82000;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.2");
    strcpy(doc.nombre, "imagen_fondo");
    doc.tipo = 3; // png
    doc.tamano = 15360;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    // Datos para IP: 192.168.2.3
    strcpy(doc.ip, "192.168.2.3");
    strcpy(doc.nombre, "carta");
    doc.tipo = 1; // pdf
    doc.tamano = 8192;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.3");
    strcpy(doc.nombre, "foto_perfil");
    doc.tipo = 2; // jpg
    doc.tamano = 25600;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.3");
    strcpy(doc.nombre, "screenshot");
    doc.tipo = 3; // png
    doc.tamano = 102400;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.3");
    strcpy(doc.nombre, "planilla");
    doc.tipo = 4; // xlsx
    doc.tamano = 51200;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    // Datos para IP: 192.168.2.5
    strcpy(doc.ip, "192.168.2.5");
    strcpy(doc.nombre, "manual");
    doc.tipo = 1; // pdf
    doc.tamano = 204800;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    strcpy(doc.ip, "192.168.2.5");
    strcpy(doc.nombre, "grafico");
    doc.tipo = 3; // png
    doc.tamano = 76800;
    fwrite(&doc, sizeof(tArchivo), 1, archivo);
    
    fclose(archivo);

    return 0;
}