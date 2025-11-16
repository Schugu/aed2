// Librerías
#include <stdio.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorOrdenado(tVectorInt);
void mostrarDatos(tVectorInt);
int busquedaSecuencialOrdenada(tVectorInt, int);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorOrdenado(vector);
    mostrarDatos(vector);

    int buscar = 5;
    printf("Buscamos el %d: ", buscar);
    int busqueda = busquedaSecuencialOrdenada(vector, buscar); // Le paso el vector donde buscar y el elemento por argumento
    if (busqueda == -1) {
        printf("No se encontro.\n");
    } else {
        printf("Se encontro en la posicion: %d.\n", busqueda);
    }
}

// Funciones
void crearVectorOrdenado(tVectorInt pVector) {
    tVectorInt v = {1, 2, 3, 4, 5};

    for (int i = 0; i < MAX; i++) {
        pVector[i] = v[i];
    }
}

void mostrarDatos(tVectorInt pVector) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d] ", pVector[i]);
    }
    printf("\n");
}

// Para esta busqueda se necesita un vector previamente ordenado de menor a mayor
int busquedaSecuencialOrdenada(tVectorInt pVector, int pElem) { // Le paso por parámetros el vector donde buscar y el elemento
    // Inicializo i, que es el índice
    int i = 0;

    // Seguir buscando mientras no se llegue al final del vector y el elemento del vector no sea mayor que el elemento a buscar
    while (i < MAX && pVector[i] < pElem) {
        i++;
    }
    // Se sale del while por 2 razones:
    // 1. Se termino el vector
    // 2. Se encontró un elemento mayor al buscado, entonces no hace falta seguir buscando, no se va a encontrar el elemento

    // Entonces, si el vector no se termina y el elemento del vector es igual al buscado
    if (i < MAX && pVector[i] == pElem) {
        return i; // Se encontró (devolvemos la posición del elemento en el vector)
    } else {
        return -1; // No se encontró (devolvemos una posición inválida del vector)
    }
}
