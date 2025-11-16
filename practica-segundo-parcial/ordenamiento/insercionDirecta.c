// Librerías
#include <stdio.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorRandom(tVectorInt);
void mostrarDatos(tVectorInt);
void ordenarInsercionDirecta(tVectorInt);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorRandom(vector);

    printf("Antes de ordenar: ");
    mostrarDatos(vector);

    ordenarInsercionDirecta(vector);
    printf("Despues de ordenar: ");
    mostrarDatos(vector);

    return 0;
}

// Funciones
void crearVectorRandom(tVectorInt pVector) {
    tVectorInt v = {22, 74, 16, 28, 1};

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

/*
    Ordenamiento por Inserción Directa (baraja):
    Este algoritmo funciona como cuando ordenamos cartas en la mano. Se asume que la parte
    izquierda del vector está ordenada, y se van tomando elementos de la parte desordenada
    para insertarlos en el lugar correcto dentro de esa zona ordenada.

    En cada pasada se toma el elemento ubicado en la posición i y se lo guarda en 'aux'.
    Luego se compara hacia atrás con los elementos ya ordenados (posiciones 0 hasta i-1).
    Mientras exista un elemento mayor que 'aux', ese elemento se mueve una posición hacia
    la derecha para hacer espacio.

    Cuando ya no quedan elementos mayores a la izquierda, 'aux' se inserta en la posición
    donde corresponde (j+1). De esta manera, la parte izquierda del vector crece ordenada
    pasada tras pasada.
*/
void ordenarInsercionDirecta(tVectorInt pVector) {
    int aux; // Auxiliar para guardar el elemento que vamos a insertar
    int j;

    // Arrancamos desde la posición 1 porque el elemento en la posición 0 ya está "ordenado"
    for (int i = 1; i < MAX; i++) {
        aux = pVector[i];      // Tomamos el elemento desordenado actual
        j = i - 1;             // j apunta al último elemento de la parte ordenada

        // Comparamos hacia atrás mientras haya elementos mayores que 'aux'
        while (j >= 0 && pVector[j] > aux) {
            // Movemos el elemento mayor una posición hacia la derecha
            pVector[j + 1] = pVector[j];
            j--;  // Retrocedemos para seguir comparando
        }
        
        // Insertamos 'aux' en el hueco que quedó libre
        pVector[j + 1] = aux;
    }
}