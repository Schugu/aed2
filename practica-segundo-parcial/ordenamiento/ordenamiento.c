// Librerías
#include <stdio.h>
#include <stdlib.h>

#define MAX 8

// Tipos
typedef int tVectorInt[MAX];

/* Prototipos */
void cargarVector(tVectorInt); 
void mostrarElementos(tVectorInt);
void burbujaTraza(tVectorInt); // Traza de trazado
void seleccionDirectaTraza(tVectorInt);
void insercionDirectaTraza(tVectorInt);

// Variable global
tVectorInt v;

// Función principal
int main() {
    printf("-----------------------------------------\n");
    printf("   Burbuja, Seleccion e Insercion \n");
    printf("------------------------------------------\n\n");

    /* MÉTODO BURBUJA */
    cargarVector(v);
    printf("METODO BURBUJA (antes de ordenar):");
    mostrarElementos(v);
    burbujaTraza(v);
    printf("\nMETODO BURBUJA (despues de ordenar):");
    mostrarElementos(v);
    printf("\n---------------------------------------------\n");

    /* MÉTODO SELECCIÓN DIRECTA */
    cargarVector(v);
    printf("METODO SELECCION DIRECTA (antes de ordenar):");
    mostrarElementos(v);
    seleccionDirectaTraza(v);
    printf("\nMETODO SELECCION DIRECTA (despues de ordenar):");
    mostrarElementos(v);
    printf("\n----------------------------------------------\n");

    /* MÉTODO INSERCIÓN DIRECTA */
    cargarVector(v);
    printf("METODO INSERCION DIRECTA (antes de ordenar):");
    mostrarElementos(v);
    insercionDirectaTraza(v);
    printf("\nMETODO INSERCION DIRECTA (despues de ordenar):");
    mostrarElementos(v);
    printf("\n-----------------------------------------------\n");

    return 0;
}

// Funciones
void cargarVector(tVectorInt pVector) {
    int valores[MAX] = {64, 34, 25, 12, 22, 11, 90, 88};
    for (int i = 0; i < MAX; i++) {
        pVector[i] = valores[i];
    }
}

void mostrarElementos(tVectorInt pVector) {
    printf("\nElementos: \n | ");
    for (int i = 0; i < MAX; i++) {
        printf("%d | ", pVector[i]);
    }
    printf("\n");
}

/* MÉTODO BURBUJA
   Recorre el vector repetidamente comparando elementos adyacentes.
   Si dos elementos están desordenados, los intercambia.
   En cada pasada, el elemento más grande de la parte desordenada se desplaza hacia el final del vector.
   En cada iteración la cantidad de comparaciones disminuye porque
   los últimos elementos ya van quedando ordenados.
*/
void burbujaTraza(tVectorInt pVector) {
    int i, j, aux;
    for (i = 0; i < MAX - 1; i++) {            // Pasadas
        for (j = 0; j < MAX - 1 - i; j++) {    // Comparaciones en cada pasada
            if (pVector[j] > pVector[j + 1]) { // Intercambio si están desordenados
                aux = pVector[j];
                pVector[j] = pVector[j + 1];
                pVector[j + 1] = aux;
            }
        }
        printf("\nDespues de la pasada %d:", i + 1);
        mostrarElementos(pVector);
    }
}

/* MÉTODO SELECCIÓN DIRECTA
   En cada pasada se busca el menor elemento de la parte desordenada
   y se lo coloca en su posición correcta (al principio de esa zona).
   En la primera pasada queda el menor en la posición 0,
   en la segunda pasada queda el segundo menor en la posición 1,
   y así sucesivamente.
   Se imprime la traza mostrando el vector después de cada pasada.
*/
void seleccionDirectaTraza(tVectorInt pVector) {
    int i, j, posMenor, aux;
    for (i = 0; i < MAX - 1; i++) {
        posMenor = i;
        for (j = i + 1; j < MAX; j++) {
            if (pVector[j] < pVector[posMenor]) {
                posMenor = j;
            }
        }
        if (posMenor != i) {
            aux = pVector[i];
            pVector[i] = pVector[posMenor];
            pVector[posMenor] = aux;
        }
        printf("\nDespues de la pasada %d:", i + 1);
        mostrarElementos(pVector);
    }
}

/* MÉTODO INSERCIÓN DIRECTA (tipo "baraja")
   Simula la forma en que ordenamos cartas en la mano.
   Toma cada elemento del vector y lo inserta en la posición correcta
   dentro de los elementos ya ordenados a su izquierda.
   La traza muestra el estado del vector después de insertar cada elemento.
*/
void insercionDirectaTraza(tVectorInt pVector) {
    int i, j, aux;
    for (i = 1; i < MAX; i++) {
        aux = pVector[i];
        j = i - 1;

        while ((j >= 0) && (pVector[j] > aux)) {
            pVector[j + 1] = pVector[j];
            j--;
        }

        pVector[j + 1] = aux;

        printf("\nDespues de la pasada %d:", i);
        mostrarElementos(pVector);
    }
}
