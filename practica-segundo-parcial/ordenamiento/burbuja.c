// Librerías
#include <stdio.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorRandom(tVectorInt);
void mostrarDatos(tVectorInt);
void ordenarBurbuja(tVectorInt);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorRandom(vector);

    printf("Antes de ordenar: ");
    mostrarDatos(vector);

    ordenarBurbuja(vector);
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
    Ordenamiento por burbuja:
    Este algoritmo funciona realizando varias pasadas0 por el vector.
    En cada pasada, se comparan elementos consecutivos (j y j+1).
    Si están desordenados (el de la izquierda es mayor que el de la derecha),
    se intercambian. Esto hace que los elementos más grandes vayan
    desplazándose hacia la derecha del vector
*/
void ordenarBurbuja(tVectorInt pVector) {
    int aux; // Auxiliar para guardar valores

    for (int i = 0; i < MAX - 1; i++) { // Pasadas principales (una por cada elemento)
        // En cada pasada completa, al menos un elemento grande termina en su
        // posición correcta en la parte derecha del vector.

        for (int j = 0; j < MAX - 1; j++) { // Comparaciones dentro de cada pasada
            // Acá comparamos el elemento actual (j) con el siguiente (j+1).
            // Si están en orden incorrecto, hacemos un intercambio.

            if (pVector[j] > pVector[j + 1]) {
                // Guardamos el valor del elemento mayor en un auxiliar.
                aux = pVector[j];

                // Pasamos el elemento menor hacia la izquierda.
                pVector[j] = pVector[j + 1];

                // Y el elemento mayor lo pasamos hacia la derecha.
                pVector[j + 1] = aux;
            }
        }
    }
}