/* Ejercicio de clase
   Búsquedas en vectores: secuencial, secuencial sobre vector ordenado,
   binaria (con retorno de posición y con bool), búsqueda de mayor y menor.
*/

// Librerias
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Constantes
#define MAX 5

// Tipos
typedef int tVectorInt[MAX];

// Prototipos
int busquedaSecuencial(tVectorInt, int);
int busquedaSecuencialOrdenada(tVectorInt, int);
int busquedaBinaria(tVectorInt, int);
bool busquedaBinariaBool(tVectorInt, int);
int buscarMayor(tVectorInt);
int buscarMenor(tVectorInt);
void cargarVectorOrdenado();
void cargarVectorDesordenado();
void mostrarElementos();

// Variables globales
tVectorInt v;

// Funcion principal
int main() {
    // VECTOR DESORDENADO + BÚSQUEDA SECUENCIAL
    cargarVectorDesordenado();
    mostrarElementos();
    printf("Buscamos al 50 → busquedaSecuencial: %d\n\n",
           busquedaSecuencial(v, 50));

    // VECTOR ORDENADO
    cargarVectorOrdenado();
    mostrarElementos();

    printf("Buscamos al 40 → busquedaSecuencialOrdenada: %d\n",
           busquedaSecuencialOrdenada(v, 40));

    printf("Buscamos al 30 → busquedaBinaria: %d\n\n",
           busquedaBinaria(v, 30));

    if (busquedaBinariaBool(v, 50)) {
        printf("Elemento encontrado\n\n");
    } else {
        printf("Elemento no encontrado\n\n");
    }

    // MAYOR Y MENOR
    cargarVectorDesordenado();
    mostrarElementos();
    printf("Posición del mayor: %d\n", buscarMayor(v));
    printf("Posición del menor: %d\n\n", buscarMenor(v));

    return 0;
}

// Funciones
// Carga un vector ordenado crecientemente
void cargarVectorOrdenado() {
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;
    v[3] = 40;
    v[4] = 50;
}

// Carga un vector con números aleatorios entre 1 y 7 /
void cargarVectorDesordenado() {
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        v[i] = 1 + rand() % 7;
    }
}

// Muestra los elementos del vector /
void mostrarElementos() {
    for (int i = 0; i < MAX; i++) {
        printf("%d\t", v[i]);
    }
    printf("\n");
}

/* BÚSQUEDA SECUENCIAL
   Recorre el vector desde el principio al final hasta encontrar elem.
   Devuelve la posición o -1 si no está.
*/
int busquedaSecuencial(tVectorInt pVector, int elem) {
    int i = 0;

    while (i < MAX && pVector[i] != elem) {
        i++;
    }

    if (i < MAX) {
        return i; // Encontrado
    } else {
        return -1; // No encontrado
    }
}

/* BÚSQUEDA SECUENCIAL SOBRE VECTOR ORDENADO
   Se detiene cuando el elemento del vector supera al buscado.
   Devuelve la posición o -1.
   Pre-condición: el vector está ordenado crecientemente.
*/
int busquedaSecuencialOrdenada(tVectorInt pVector, int elem) {
    int i = 0;

    while (i < MAX && pVector[i] < elem) {
        i++;
    }

    if (i < MAX && pVector[i] == elem) {
        return i;
    } else {
        return -1;
    }
}

/* BÚSQUEDA BINARIA
   Divide el intervalo en dos y descarta la mitad en cada paso.
   Devuelve la posición o -1.
*/
int busquedaBinaria(tVectorInt pVector, int elem) {
    int extInf = 0;
    int extSup = MAX - 1;
    int posMed;
    bool encontrado = false;

    while (!encontrado && extSup >= extInf) {
        posMed = (extInf + extSup) / 2;

        if (pVector[posMed] == elem) {
            encontrado = true;
        } else if (elem > pVector[posMed]) {
            extInf = posMed + 1;
        } else {
            extSup = posMed - 1;
        }
    }

    return encontrado ? posMed : -1;
}

/* BÚSQUEDA BINARIA (versión booleana)
   Devuelve true si encontró el elemento, false si no.
*/
bool busquedaBinariaBool(tVectorInt pVector, int elem) {
    int extInf = 0;
    int extSup = MAX - 1;
    int posMed;
    bool encontrado = false;

    while (!encontrado && extSup >= extInf) {
        posMed = (extInf + extSup) / 2;

        if (pVector[posMed] == elem) {
            encontrado = true;
        } else if (elem > pVector[posMed]) {
            extInf = posMed + 1;
        } else {
            extSup = posMed - 1;
        }
    }

    return encontrado;
}

/* BUSCAR MAYOR
   Devuelve la posición del mayor valor del vector.
*/
int buscarMayor(tVectorInt pVector) {
    int posMayor = 0;

    for (int i = 1; i < MAX; i++) {
        if (pVector[i] > pVector[posMayor]) {
            posMayor = i;
        }
    }
    return posMayor;
}

/* BUSCAR MENOR
   Devuelve la posición del menor valor del vector.
*/
int buscarMenor(tVectorInt pVector) {
    int posMenor = 0;

    for (int i = 1; i < MAX; i++) {
        if (pVector[i] < pVector[posMenor]) {
            posMenor = i;
        }
    }
    return posMenor;
}
