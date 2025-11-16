// Librerías
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipado
void crearVectorOrdenado(tVectorInt);
void mostrarDatos(tVectorInt);
int busquedaBinaria(tVectorInt, int);

// Función principal
int main() {
    tVectorInt vector;

    crearVectorOrdenado(vector);
    mostrarDatos(vector);

    int buscar = 5;
    printf("Buscamos el %d: ", buscar);
    int busqueda = busquedaBinaria(vector, buscar); // Le paso el vector donde buscar y el elemento por argumento
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

// Para esta búsqueda se debe tener un vector previamente ordenado de menor a mayor.
// Esta búsqueda consiste en ir generando y descartando rangos donde el elemento no puede estar,
// hasta achicar el rango tanto que se encuentre o se termine la búsqueda.
int busquedaBinaria(tVectorInt pVector, int pElem) {
    int extInf = 0;       // Extremo inferior, lo más bajo posible (posición 0)
    int extSup = MAX - 1; // Extremo superior, lo más alto posible (última posición)
    int posMed;
    bool encontrado = false;

    // Buscar hasta que se encuentre el elemento o mientras haya un rango válido en donde buscar
    while (!encontrado && extSup >= extInf) {
        posMed = (extInf + extSup) / 2; // Buscar la posición del medio

        // Si el elemento del vector en la posición central es igual al elemento buscado, marcarlo como encontrado
        // Punto importante: el algoritmo va achicando rangos hasta que la posición del medio coincide con el elemento buscado.
        // Si no lo encuentra, ya no entraría en el while porque el rango de búsqueda dejaría de ser válido.
        if (pVector[posMed] == pElem) {
            encontrado = true;
        } else if (pElem > pVector[posMed]) {
            // Si el elemento buscado es mayor, descartar TODO el rango izquierdo de búsqueda
            extInf = posMed + 1;
        } else { // pElem < pVector[posMed]
            // Si el elemento buscado es menor, descartar TODO el rango derecho de búsqueda
            extSup = posMed - 1;
        }
    }

    // Si se encuentra el elemento, devolver su posición; si no, devolver una posición inválida
    return encontrado ? posMed : -1;
}

/*
    Existe una versión booleana de este algoritmo de búsqueda.
    Solo se debe cambiar la definición de la función a:
        bool busquedaBinaria(tVectorInt pVector, int pElem);

    Y el return debe quedar como:
        return encontrado;
*/