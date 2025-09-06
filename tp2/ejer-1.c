/* 
	1.Crear un tipo de dato tListaVideojuegos para un nodo que permita almacenar los siguientes datos de un
	videojuego: idJuego (entero), titulo (cadena de 50 caracteres), anioLanzamiento (entero), precio
	(flotante).
	Luego, declarar un puntero a una variable de ese tipo, crear el primer nodo de la lista a partir del ingreso
	de datos por teclado, y mostrar todos los datos del nodo almacenado.
	Importante: Implementar también la liberación correcta de la memoria asignada.
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSTRING 50

// Tipos 
typedef char tString[MAXSTRING];

typedef struct {
	int id;
	tString titulo;
	int anioLanzamiento;
	float precio;

} tDatosJuego;

typedef struct nodo {
	tDatosJuego datos;
	struct nodo* siguiente;
} tNodo;

// Variables globales
tNodo cabecera;

// Prototipado 
tDatosJuego ingresarDatos();
tNodo* crearNodo(tDatosJuego, tNodo*);
void mostrarDatos(tDatosJuego);


// Funcion principal 
int main (){
	tDatosJuego juego = ingresarDatos();

	tNodo* nuevoNodo = crearNodo(juego, NULL);

	cabecera = *nuevoNodo;

	tNodo* aux;
	while(aux != NULL){
		mostrarDatos(cabecera->datos);
		aux = cabecera->siguiente;
	}

	return 0;
} 

tDatosJuego ingresarDatos(){
	tDatosJuego juego;
	printf("Ingrese los datos del juego: \n");
	printf("ID: ");
	scanf("%d", &juego.id);

	printf("Titulo: ");
	scanf(" %49[^\n]", juego.titulo);

	printf("Anio lanzamiento: ");
	scanf("%d", &juego.anioLanzamiento);

	printf("Precio: ");
	scanf("%f", &juego.precio);

	return juego;
}

tNodo* crearNodo(tDatosJuego juego, tNodo* enlace){
	tNodo* nodo;

	nodo = (tNodo*) malloc(sizeof(tNodo));

	if (nodo == NULL) {
		printf("Error al asignar memoria");
	}

	nodo->datos = juego;
	nodo->siguiente = enlace;	

	return nodo;
}

void mostrarDatos(tDatosJuego juego){
	printf("ID: %d", juego.id);
	printf("Titulo: %s", juego.titulo);
	printf("Anio de lanzamiento: %d", juego.anioLanzamiento);
	printf("Precio: %.2f", juego.precio);
}