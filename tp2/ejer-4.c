/*
  Una empresa de delivery de comida necesita un sistema para gestionar pedidos
  mediante una lista enlazada. Para cada pedido se almacena: numeroPedido
  (entero), nombreCliente (cadena), direccion (cadena), telefono (cadena),
  montoTotal (flotante), estadoPedido (cadena: "Pendiente", "Preparando", "En
  camino", "Entregado"), tiempoEstimado (entero en minutos). El sistema debe
  calcular automáticamente:
  - Costo de envío: $500 si el monto es menor a $3000, gratis si es mayor o
  igual.
  - Tiempo estimado: Base de 30 minutos + 5 minutos por cada $1000 del monto.
  - Prioridad: "Alta" si el monto > $5000, "Normal" en caso contrario.
  Funcionalidades requeridas:
  a) Crear nuevo pedido (calcular automáticamente costo envío, tiempo y
  prioridad).
  b) Cambiar estado de un pedido (buscar por número de pedido).
  c) Eliminar pedidos entregados.
  d) Buscar pedidos por cliente.
  e) Mostrar todos los pedidos según la prioridad que se desee consultar.
  f) Mostrar el total de pedidos según el estado que se desee consultar.
  g) Calcular y mostrar el monto promedio de pedidos pendientes.
  h) Listado de pedidos con prioridad alta que estén "En camino".
  i) Cliente con mayor cantidad de pedidos.
  j) Tiempo promedio estimado de pedidos no entregados.
  Además:
  k) Aplicar descuento del 10% a pedidos de un cliente específico.
  l) Marcar como "Entregado" todos los pedidos "En camino" de más de 60 minutos.
  Implementar un menú principal completo y asegurar la correcta liberación de
  memoria al finalizar el programa.
*/

// Librerias
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constante
#define MAXSTRING 50
// Tipos
typedef char tString[MAXSTRING];

tString arrayEstadoPedido[4] = {"Pendiente", "Preparando", "En camino",
                                "Entregado"};
// Tipos
typedef struct {
  int numero;
  tString nombreCLiente;
  tString direccion;
  tString telefono;
  float montoTotal;
  tString estadoPedido;
  int tiempoEstimado;

} tDatosPedido;

typedef struct nodo {
  tDatosPedido datos;
  struct nodo* siguiente;
} tNodo;

// Prototipado
// Punto a)
tNodo* crearNodo(tDatosPedido, tNodo*);
void elegirEstadoPedido(tString);
tDatosPedido ingresarDatos();
void push(tNodo** cabecera);

void mostrarOpciones();
void crearMenu(tNodo**);

// Variables globales
tNodo* cabecera;

// Funcion principal
int main() {
  crearMenu(&cabecera);

  return 0;
}

// Funciones
// Punto a)
void elegirEstadoPedido(tString estado) {
  printf("Elija el estado del pedido: \n");
  for (int i = 0; i < 4; i++) {
    printf("[%d]: ", (i + 1));
    printf("%s\n", arrayEstadoPedido[i]);
  }

  bool salir = true;
  do {
    int opcion = 0;
    scanf("%d", &opcion);

    switch (opcion) {
      case 1:
        estado = arrayEstadoPedido[0];
        break;
      case 2:
        estado = arrayEstadoPedido[1];
        break;
      case 3:
        estado = arrayEstadoPedido[2];
        break;
      case 4:
        estado = arrayEstadoPedido[3];
        break;

      default:
        printf("Opcion invalida, porfavor ingresela de nuevo.");
        salir = false;
        break;
    }
  } while (!salir);
}

tDatosPedido ingresarDatos() {
  tDatosPedido elemento;

  printf("Ingreso de pedido: \n");

  printf("Numero: ");
  scanf("%d", &elemento.numero);

  printf("Nombre del cliente: ");
  scanf(" %49[^\n]", elemento.nombreCLiente);

  printf("Direccion: ");
  scanf(" %49[^\n]", elemento.direccion);

  printf("Telefono: ");
  scanf(" %49[^\n]", elemento.telefono);

  printf("Monto total: ");
  scanf("%f", elemento.montoTotal);

  elegirEstadoPedido(elemento.estadoPedido);

  printf("Tiempo estimado en minutos: ");
  scanf("%f", elemento.tiempoEstimado);

  return elemento;
}
tNodo* crearNodo(tDatosPedido elemento, tNodo* enlace) {
  tNodo* nodo;

  nodo = (tNodo*)malloc(sizeof(tNodo));

  if (nodo == NULL) {
    printf("Error al asignar memoria");
  }

  nodo->datos = elemento;
  nodo->siguiente = enlace;

  return nodo;
}
void push(tNodo** cabecera) {
  tDatosPedido elemento = ingresarDatos();

  tNodo* nuevoNodo;
  if (!*cabecera) {
    nuevoNodo = crearNodo(elemento, NULL);
  } else {
    nuevoNodo = crearNodo(elemento, *cabecera);
  }

  *cabecera = nuevoNodo;
}

// Menú
void mostrarOpciones() {
  printf("\n\n========================| Menu |========================\n");
  printf(
      "[a]: Crear nuevo pedido (calcular automáticamente costo envío, tiempo y "
      "prioridad).\n");
  printf("[b]: Cambiar estado de un pedido (buscar por número de pedido).\n");
  printf("[c]: Eliminar pedidos entregados.\n");
  printf("[d]: Buscar pedidos por cliente.\n");
  printf(
      "[e]: Mostrar todos los pedidos según la prioridad que se desee "
      "consultar.\n");
  printf(
      "[f]: Mostrar el total de pedidos según el estado que se desee "
      "consultar.\n");
  printf("[g]: Calcular y mostrar el monto promedio de pedidos pendientes.\n");
  printf("[h]: Listado de pedidos con prioridad alta que estén 'En camino'.\n");
  printf("[i]: Cliente con mayor cantidad de pedidos.\n");
  printf("[j]: Tiempo promedio estimado de pedidos no entregados.\n");
  printf(
      "[k]: Aplicar descuento del 10%% a pedidos de un cliente específico.\n");
  printf(
      "[k]: Marcar como 'Entregado' todos los pedidos 'En camino' de más de 60 "
      "minutos.\n");
  printf("[x]: Salir.\n");
}

void crearMenu(tNodo** cabecera) {
  char opcion;
  bool salir = false;

  do {
    mostrarOpciones();
    printf("Seleccione una opcion: ");
    fflush(stdin);
    scanf("%c", &opcion);
    opcion = tolower(opcion);
    printf("\n\n");

    switch (opcion) {
      case 'a':
        push(cabecera);
        break;
      case 'x':
        salir = true;
        break;

      default:
        printf("Opcion invalida.\n");
    }

  } while (!salir);
}
