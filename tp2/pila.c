// Librerias
#include <stdio.h>
#include <stdlib.h>

// Tipos
// tipo de estructura nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Apilar (push)
void push(Nodo** tope, int valor) {
    // Crear nodo
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    // Verificar si se reservó memoria
    if (!nuevoNodo) {
        printf("Error al reservar memoria\n");
        return;
    }

    // Configuro el nodo
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = *tope; // el nuevo nodo apunta al anterior tope
    *tope = nuevoNodo;            // el nuevo nodo se convierte en el tope
}

// Desapilar (pop)
int pop(Nodo** tope) {
    // Preguntarse si la lista esta vacia
    if (*tope == NULL) {
        printf("La pila está vacía\n");
        return -1; // valor de error
    }
    // Aux temp  para almacenar el elemento antiguo
    Nodo* temp = *tope;
    int valor = temp->dato;

    // Asignar el tope al siguiente nodo del eliminado
    *tope = temp->siguiente; // mover tope al siguiente nodo
    free(temp);              // liberar memoria

    // Retornar el valor eliminado
    return valor;
}

// Mostrar pila
void mostrar(Nodo* tope) {
    // Recorro la pila
    while (tope) { // No hace falta poner el == NULL
        printf("%d -> ", tope->dato);
        // Hacer que la copia tope se mueva al siguiente nodo
        tope = tope->siguiente;
    }
    printf("NULL\n");
}

// Función principal
int main() {
    // Creo la pila y la inicializo en NULL
    Nodo* pila = NULL;

    // Creo nodos e inserto datos
    push(&pila, 10);
    push(&pila, 20);
    push(&pila, 30);

    // Muestro la pila completa
    mostrar(pila); 

    // Muestro el elemento eliminado
    printf("Elemento desapilado: %d\n", pop(&pila));
    mostrar(pila); 

    return 0;
}
