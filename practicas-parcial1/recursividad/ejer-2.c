/*
  Escribir una función recursiva que reciba como parametros un arreglo de caracteres, su dimensión
  y un caracter, y retorne la cantidad de vocales del arreglo que se encuentren almacenados.
*/
#include <stdbool.h>
#include <stdio.h>

bool esVocal(char c) {
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int contarVocales(char arr[], int n) {
  char vocales[5] = {'a', 'e', 'i', 'o', 'u'};
  if (n == 0) {
    return 0;
  }

  if (esVocal(arr[n - 1])) {
    return 1 + contarVocales(arr, n - 1);
  } else {
    return contarVocales(arr, n - 1);
  }
}

int main() {
  char arreglo[] = {'a', 'b', 'c', 'a', 'd', 'a'};
  int dimension = sizeof(arreglo) / sizeof(arreglo[0]);

  int cantidad = contarVocales(arreglo, dimension);

  printf("Aparecen %d vocales en el arreglo.\n", cantidad);

  return 0;
}