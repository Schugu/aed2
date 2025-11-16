// Librerías
#include <stdio.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorRandom(tVectorInt);
void mostrarDatos(tVectorInt);
int busquedaSecuencial(tVectorInt, int);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorRandom(vector);
    mostrarDatos(vector);

    int buscar = 52;
    printf("Buscamos el %d: ", buscar);
    int busqueda = busquedaSecuencial(vector, buscar); // Le paso el vector donde buscar y el elemento por argumento
    if (busqueda == -1) {
        printf("No se encontró.\n");
    } else {
        printf("Se encontró en la posición: %d.\n", busqueda);
    }
}

// Funciones
void crearVectorRandom(tVectorInt pVector) {
    tVectorInt v = {12, 24, 36, 48, 52};

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

int busquedaSecuencial(tVectorInt pVector, int pElem) { // Le paso por parámetros el vector donde buscar y el elemento
    // Inicializo i, que es el índice
    int i = 0;

    // Seguir buscando mientras no se llegue al final del vector y no se encuentre el elemento
    while (i < MAX && pVector[i] != pElem) {
        i++;
    }
    // Se sale del while por encontrar el elemento o por llegar al final del vector

    // Entonces, si el índice no es el final del vector, se encontró un elemento en dicho índice
    if (i < MAX) {
        return i; // Se encontró (devolvemos la posición del elemento en el vector)
    } else {
        return -1; // No se encontró (devolvemos una posición inválida del vector)
    } 
}
