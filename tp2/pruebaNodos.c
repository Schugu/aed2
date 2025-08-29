// Librerias
#include <stdio.h>
#include <stdlib.h>

// Tipos
typedef struct Nodo {
	int anio;
	struct Nodo* siguiente;
} tNodo; 

// Prototipado
tNodo* crearNodo(int, tNodo*); 

// Variables globales
tNodo cabecera;

// Funcion principal 
int main(){
	// Creo el primer nodo
	tNodo* primero = crearNodo(2000, NULL); // Se le pone NULL para inicializar
	cabecera = *primero;

	tNodo* segundo = crearNodo(2002, NULL);

	primero->siguiente = segundo;

	tNodo* tercero = crearNodo(2004, NULL);

	segundo->siguiente = tercero;

	printf("Valor del primero->dato: %d\n", primero->anio);
	printf("Valor del primero->siguiente: %d\n", primero->siguiente);
	printf("Valor del segundo->dato: %d\n", segundo->anio);
	printf("Valor del segundo->siguiente: %d\n", segundo->siguiente);
	printf("Valor del tercero->dato: %d\n", tercero->anio);
	printf("Valor del tercero->siguiente: %d\n", tercero->siguiente);
	return 0;
}

tNodo* crearNodo(int anio, tNodo* enlace){
	// Creo dato tipo apuntador nodo
	tNodo *p;
	
	// Reservo memoria para el nodo
	p = (tNodo*) malloc(sizeof(tNodo));

	if (p == NULL) {
		printf("Error al asignar memoria.");
	}

	// Almaceno el enlace al siguiente nodo
	p->anio = anio;
	p->siguiente = enlace;

	return p;
}













