// Librerias
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define ARCHIVO "productos.dat"
#define MAXSTRING 30

// Tipos
typedef char tString[MAXSTRING];

typedef struct {
  int nroticket;
  int codProducto;
  tString nombre;
  int codCategoria;
  int cantVendida;
  float precioUnit;
} tProducto;

// Prototipado
void inicializacion();
void procesoCorte();
void finalizacion();

void principioCorte();
void unProducto();
void finCorte();

void imprimirCabecera();
void imprimirLinea();
void imprimirSubTotales();
void imprimirTotalesGenerales();

// Variables globales
FILE* productos;
tProducto producto, productoAnterior;
float totalPan, totalLac, totalPer, totalLim, totalRecaudado;
int cantTIckets;
tString categorias[4] = {"Panaderia", "Lacteos", "Perfumeria", "Limpieza"};

// Funcion Principal
int main() {
  inicializacion();
  procesoCorte();
  finalizacion();

  return 0;
}

// Funciones
void imprimirCabecera() {
  printf("\t *** INFORME DE VENTA POR DIA ***\n");
  printf("Nro.Ticket\t | Cod. de Producto\t | Nombre\t | Categoria\t | Cantidad\t | Total |\n");
  printf("-----------------------------------------------------------------------------------\n");
}

void imprimirLinea() {
  printf("%d\t | %d\t | %s\t | %s\t | %d\t | %.2f\n",
         producto.nroticket, producto.codProducto, producto.nombre,
         categorias[producto.codCategoria - 1], producto.cantVendida, producto.precioUnit);
}

void imprimirSubTotales() {
  printf("%s: %.2f\n", categorias[0], totalPan);
  printf("%s: %.2f\n", categorias[1], totalLac);
  printf("%s: %.2f\n", categorias[2], totalPer);
  printf("%s: %.2f\n", categorias[3], totalLim);
}

void imprimirTotalesGenerales() {
  printf("Monto total recaudado: %.2f\n", totalRecaudado);
  printf("Cantidad de tickets: %d\n", cantTIckets);
}

void inicializacion() {
  productos = fopen(ARCHIVO, "rb");
  if (!productos) {
    printf("Error: no se pudo abrir el archivo.");
    exit(EXIT_FAILURE);
  }

  fread(&producto, sizeof(tProducto), 1, productos);

  productoAnterior = producto;

  totalPan = 0;
  totalLac = 0;
  totalPer = 0;
  totalLim = 0;
  totalRecaudado = 0;
  cantTIckets = 0;

  imprimirCabecera();
}

void procesoCorte() {
  while (!feof(productos)) {
    principioCorte();
    while (!feof(productos) && producto.nroticket == productoAnterior.nroticket) {
      unProducto();
      fread(&producto, sizeof(tProducto), 1, productos);
    }
    finCorte();
  }
}

void principioCorte() {
  totalPan = 0;
  totalLac = 0;
  totalPer = 0;
  totalLim = 0;
}

void unPorducto() {
  imprimirLinea();

  switch (producto.codCategoria) {
  case 1:
    totalPan += producto.precioUnit;
  case 2:
    totalLac += producto.precioUnit;
  case 3:
    totalPer += producto.precioUnit;
  case 4:
    totalLim += producto.precioUnit;
  }

  totalRecaudado += producto.precioUnit;
}

void finCorte() {
  imprimirSubTotales();
  cantTIckets++;

  productoAnterior = producto;
}

void finalizacion() {
  imprimirTotalesGenerales();
  fclose(productos);
}