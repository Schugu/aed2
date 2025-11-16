// Librerías
#include <stdio.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorRandom(tVectorInt);
void mostrarDatos(tVectorInt);
void ordenarSeleccionDirecta(tVectorInt);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorRandom(vector);

    printf("Antes de ordenar: ");
    mostrarDatos(vector);

    ordenarSeleccionDirecta(vector);
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
    Ordenamiento por Selección Directa:
    Este algoritmo usa los índices para ordenar de menor a mayor. En cada pasada se supone
    que el índice i contiene el elemento menor. Luego se recorren los elementos restantes
    con un for j, desde la posición i + 1 hasta el final del vector. Si se encuentra un
    elemento más chico, se actualiza la variable posMenor; si no, se deja como está.

    Cuando se termina la comparación, si posMenor es distinto de i, se realiza el intercambio:
    el elemento menor pasa a la posición i, y el elemento que estaba en i pasa a la posición
    donde se encontró el menor.
*/
void ordenarSeleccionDirecta(tVectorInt pVector) {
    int posMenor; // Guarda la posición del menor encontrado
    int aux;      // Auxiliar para los intercambios

    for (int i = 0; i < MAX - 1; i++) {
        // Suponemos que el menor está en la posición actual (i)
        posMenor = i;

        // Buscamos un elemento más chico en el resto del vector
        for (int j = i + 1; j < MAX; j++) {
            // Si encontramos un elemento más chico, actualizamos la posición del menor
            if (pVector[j] < pVector[posMenor]) {
                posMenor = j;
            }
        }

        // Intercambiamos el menor encontrado con el elemento ubicado en la posición i
        if (posMenor != i) {
            aux = pVector[i];
            pVector[i] = pVector[posMenor];
            pVector[posMenor] = aux;
        }
    }
}