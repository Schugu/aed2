/*
  Escribir una función recursiva que reciba como parametros un arreglo de caracteres, su dimensión
  y un caracter, y retorne la cantidad de caracteres del arreglo que se encuentren almacenados.
*/
#include <stdio.h>

int contarCaracteres(char arr[], int n, char c) {
  if (n == 0) {
    return 0;
  }

  if (arr[n - 1] == c) {
    return 1 + contarCaracteres(arr, n - 1, c);
  } else {
    return contarCaracteres(arr, n - 1, c);
  }
}

int main() {
  char arreglo[] = {'a', 'b', 'c', 'a', 'd', 'a'};
  int dimension = sizeof(arreglo) / sizeof(arreglo[0]);
  char buscado = 'a';

  int cantidad = contarCaracteres(arreglo, dimension, buscado);

  printf("El caracter '%c' aparece %d veces.\n", buscado, cantidad);

  return 0;
}