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
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAXSTRING 50

// Tipos
typedef char tString[MAXSTRING];

tString arrayEstadoPedido[4] = {"Pendiente", "Preparando", "En camino", "Entregado"};

// Tipos
typedef struct {
  int numero;
  tString nombreCliente;
  tString direccion;
  tString telefono;
  float montoTotal;
  tString estadoPedido;
  float costoEnvio;
  int tiempoEstimado;
  tString prioridad;
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
void push(tNodo**);
void seed(tNodo**);

// Punto b)
void cambiarEstaodDePedido(tNodo**);

// Punto d)
bool estaLaListaVacia(tNodo**);
void mostrarDatos(tDatosPedido);
void mostrarLista(tNodo**);
void convertirMinuscula(tString);
void buscarPorCliente(tNodo**);
void mostrarOpcionesPrioridad();
void buscarPorPrioridad(tNodo**);
void buscarPorEstado(tNodo**);
void montoPromedioPedidosPendientes(tNodo**);
void mostrarPedidosAltaEnCamino(tNodo**);
void calcularClienteConMasPedidos(tNodo**);
void tiempoPromedioDePedidosNoEntregados(tNodo**);

// Menú
void mostrarOpcionesMenuMuestra();
void crearMenuMuestra(tNodo**);
void mostrarOpciones();
void crearMenu(tNodo**);

// Variables globales
tNodo* cabecera;

// Funcion principal
int main() {
  seed(&cabecera);
  crearMenu(&cabecera);

  return 0;
}

// Funciones
// Punto a)
void elegirEstadoPedido(tString estado) {
  printf("Elija el estado del pedido: \n");
  for (int i = 0; i < 4; i++) {
    printf("[%d]: %s\n", i + 1, arrayEstadoPedido[i]);
  }

  int opcion;
  bool valido = false;

  do {
    printf("Ingrese la opcion: ");
    scanf("%d", &opcion);
    printf("\n");
    switch (opcion) {
    case 1:
      strcpy(estado, arrayEstadoPedido[0]);
      valido = true;
      break;
    case 2:
      strcpy(estado, arrayEstadoPedido[1]);
      valido = true;
      break;
    case 3:
      strcpy(estado, arrayEstadoPedido[2]);
      valido = true;
      break;
    case 4:
      strcpy(estado, arrayEstadoPedido[3]);
      valido = true;
      break;
    default:
      printf("Opcion invalida, por favor ingresela de nuevo.\n");
      break;
    }
  } while (!valido);
}

tDatosPedido ingresarDatos() {
  tDatosPedido elemento;

  printf("Ingreso de pedido: \n");

  printf("Numero: ");
  scanf("%d", &elemento.numero);

  printf("Nombre del cliente: ");
  scanf(" %49[^\n]", elemento.nombreCliente);

  printf("Direccion: ");
  scanf(" %49[^\n]", elemento.direccion);

  printf("Telefono: ");
  scanf(" %49[^\n]", elemento.telefono);

  printf("Monto total: ");
  scanf("%f", &elemento.montoTotal);

  if (elemento.montoTotal >= 3000) {
    elemento.costoEnvio = 0;
  } else {
    elemento.costoEnvio = 500;
  }

  elemento.tiempoEstimado = 30 + ((int)(elemento.montoTotal / 1000)) * 5;

  elegirEstadoPedido(elemento.estadoPedido);

  if (elemento.montoTotal > 5000) {
    strcpy(elemento.prioridad, "Alta");
  } else {
    strcpy(elemento.prioridad, "Normal");
  }

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

void insertarNodo(tNodo** cabecera, tDatosPedido elemento) {
  tNodo* nuevoNodo;
  if (!*cabecera) {
    nuevoNodo = crearNodo(elemento, NULL);
  } else {
    nuevoNodo = crearNodo(elemento, *cabecera);
  }

  *cabecera = nuevoNodo;
}

void push(tNodo** cabecera) {
  tDatosPedido elemento = ingresarDatos();
  insertarNodo(cabecera, elemento);
}

void seed(tNodo** cabecera) {
  tDatosPedido pedido;

  pedido.numero = 1;
  strcpy(pedido.nombreCliente, "Oscar");
  strcpy(pedido.direccion, "Calle 1");
  strcpy(pedido.telefono, "123456789");
  pedido.montoTotal = 20000;
  strcpy(pedido.estadoPedido, "Pendiente");
  pedido.costoEnvio = 0;
  pedido.tiempoEstimado = 40;
  strcpy(pedido.prioridad, "Alta");
  insertarNodo(cabecera, pedido);

  pedido.numero = 2;
  strcpy(pedido.nombreCliente, "Pedro");
  strcpy(pedido.direccion, "Calle 2");
  strcpy(pedido.telefono, "123456789");
  pedido.montoTotal = 2000;
  strcpy(pedido.estadoPedido, "Preparando");
  pedido.costoEnvio = 500;
  pedido.tiempoEstimado = 40;
  strcpy(pedido.prioridad, "Normal");
  insertarNodo(cabecera, pedido);

  pedido.numero = 3;
  strcpy(pedido.nombreCliente, "Manuel");
  strcpy(pedido.direccion, "Calle 3");
  strcpy(pedido.telefono, "123456789");
  pedido.montoTotal = 5000;
  strcpy(pedido.estadoPedido, "En camino");
  pedido.costoEnvio = 0;
  pedido.tiempoEstimado = 55;
  strcpy(pedido.prioridad, "Alta");
  insertarNodo(cabecera, pedido);

  pedido.numero = 4;
  strcpy(pedido.nombreCliente, "Jorge");
  strcpy(pedido.direccion, "Calle 4");
  strcpy(pedido.telefono, "123456789");
  pedido.montoTotal = 100;
  strcpy(pedido.estadoPedido, "Entregado");
  pedido.costoEnvio = 500;
  pedido.tiempoEstimado = 30;
  strcpy(pedido.prioridad, "Normal");
  insertarNodo(cabecera, pedido);

  pedido.numero = 5;
  strcpy(pedido.nombreCliente, "Jorge");
  strcpy(pedido.direccion, "Calle 4");
  strcpy(pedido.telefono, "123456789");
  pedido.montoTotal = 60000;
  strcpy(pedido.estadoPedido, "Pendiente");
  pedido.costoEnvio = 0;
  pedido.tiempoEstimado = 200;
  strcpy(pedido.prioridad, "Alta");
  insertarNodo(cabecera, pedido);
}

// Punto d)
bool estaLaListaVacia(tNodo** cabecera) {
  return (*cabecera == NULL) ? true : false;
}
void mostrarDatos(tDatosPedido pedido) {
  printf("Numero de pedido: %d\n", pedido.numero);
  printf("Cliente: %s\n", pedido.nombreCliente);
  printf("Direccion: %s\n", pedido.direccion);
  printf("Telefono: %s\n", pedido.telefono);
  printf("Monto total: $%.2f\n", pedido.montoTotal);
  printf("Estado del pedido: %s\n", pedido.estadoPedido);
  printf("Costo de envio: $%.2f\n", pedido.costoEnvio);
  printf("Tiempo estimado: %d minutos\n", pedido.tiempoEstimado);
  printf("Prioridad: %s", pedido.prioridad);
}

// Punto d.1)
void mostrarLista(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede mostrar la lista por que esta vacia.");
    return;
  }

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux != NULL) {
    printf("\n\n--- Pedido en posicion %d ---\n", pos);
    mostrarDatos(aux->datos);
    aux = aux->siguiente;
    pos++;
  }
}

// Punto d.2)
void convertirMinuscula(tString string) {
  for (int i = 0; string[i] != '\0'; i++) {
    string[i] = tolower(string[i]);
  }
}
void buscarPorCliente(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede buscar, la lista por que esta vacia.");
    return;
  }

  tString busqueda;
  printf("Ingrese el nombre del cliente: ");
  scanf(" %49[^\n]", busqueda);
  convertirMinuscula(busqueda);

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux) {
    tString auxCliente;
    strcpy(auxCliente, aux->datos.nombreCliente);
    convertirMinuscula(auxCliente);
    if (strcmp(auxCliente, busqueda) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d", pos);
      return;
    }
    aux = aux->siguiente;
    pos++;
  }
  printf("No se encontraron resultaodos...");
  return;
}

// Punto d.3)
void mostrarOpcionesPrioridad() {
  printf("\n\n=====================| Prioridad |=====================\n");
  printf("[1]: Alta.\n");
  printf("[2]: Normal.\n");
}
void buscarPorPrioridad(tNodo** cabecera) {
  int opcion;
  bool salir = false;
  tString prioridad;
  do {
    mostrarOpcionesPrioridad();
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    printf("\n\n");

    switch (opcion) {
    case 1:
      strcpy(prioridad, "Alta");
      salir = true;
      break;
    case 2:
      strcpy(prioridad, "Normal");
      salir = true;
      break;
    default:
      printf("Opcion invalida");
    }

  } while (!salir);

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux) {
    if (strcmp(aux->datos.prioridad, prioridad) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d\n\n", pos);
    }
    aux = aux->siguiente;
    pos++;
  }
}

// Punto d.4)
void buscarPorEstado(tNodo** cabecera) {
  tString estado;
  elegirEstadoPedido(estado);

  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux) {
    if (strcmp(aux->datos.estadoPedido, estado) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d\n\n", pos);
    }
    aux = aux->siguiente;
    pos++;
  }
}

// Punto d.5)
void montoPromedioPedidosPendientes(tNodo** cabecera) {
  tNodo* aux = *cabecera;
  int cantidadTotalPendientes = 0;
  float montoTotalPendientes = 0;
  while (aux) {
    if (strcmp(aux->datos.estadoPedido, "Pendiente") == 0) {
      cantidadTotalPendientes++;
      montoTotalPendientes += aux->datos.montoTotal;
    }
    aux = aux->siguiente;
  }
  float promedio = (montoTotalPendientes / cantidadTotalPendientes);
  printf("Promedio de monto total de pedidos pendientes: $%.2f\n", promedio);
}

// Punto d.6)
void mostrarPedidosAltaEnCamino(tNodo** cabecera) {
  tNodo* aux = *cabecera;
  int pos = 0;
  while (aux) {
    if ((strcmp(aux->datos.prioridad, "Alta") == 0) &&
        (strcmp(aux->datos.estadoPedido, "En camino")) == 0) {
      mostrarDatos(aux->datos);
      printf("\nPosicion: %d\n\n", pos);
    }
    aux = aux->siguiente;
    pos++;
  }
}

// Punto d.7)
void calcularClienteConMasPedidos(tNodo** cabecera) {
  typedef struct {
    tString cliente;
    int cantPedidos;
  } tClienteMaxPedidos;

  tNodo* aux = *cabecera;
  tClienteMaxPedidos resultMaxCliente;
  resultMaxCliente.cantPedidos = -1;

  while (aux) {
    int cantPedidosCliente = 0;
    tNodo* aux2 = *cabecera;

    while (aux2) {
      if (strcmp(aux->datos.nombreCliente, aux2->datos.nombreCliente) == 0) {
        cantPedidosCliente++;
      }
      aux2 = aux2->siguiente;
    }

    if (cantPedidosCliente > resultMaxCliente.cantPedidos) {
      strcpy(resultMaxCliente.cliente, aux->datos.nombreCliente);
      resultMaxCliente.cantPedidos = cantPedidosCliente;
    }

    aux = aux->siguiente;
  }

  printf("El cliente con mas pedidos es: %s, teniendo %d pedidos.\n",
         resultMaxCliente.cliente,
         resultMaxCliente.cantPedidos);
}

// Punto d.8)
void tiempoPromedioDePedidosNoEntregados(tNodo** cabecera) {
  tNodo* aux = *cabecera;
  int contTiempo = 0;
  int totalPedidos = 0;
  while (aux) {
    if (!(strcmp(aux->datos.estadoPedido, "Entregado") == 0)) {
      contTiempo += aux->datos.tiempoEstimado;
      totalPedidos++;
    }
    aux = aux->siguiente;
  }

  float promedio = (float)contTiempo / totalPedidos;
  printf("Promedio de tiempo estimado para pedidos no entregados: %.2f minutos", promedio);
}

// Punto b)
void cambiarEstaodDePedido(tNodo** cabecera) {
  if (estaLaListaVacia(cabecera)) {
    printf("Error: no se puede cambiar de estado, la lista está vacía.\n");
    return;
  }

  int busqueda;
  printf("Ingrese el numero de pedido: ");
  scanf("%d", &busqueda);

  if (busqueda < 0) {
    printf("Numero de pedido invalido.");
    return;
  }

  tNodo* aux = *cabecera;
  while (aux) {
    if (aux->datos.numero == busqueda) {
      elegirEstadoPedido(aux->datos.estadoPedido);
      printf("Estado cambiado con exito!");
      mostrarDatos(aux->datos);
      return;
    }
    aux = aux->siguiente;
  }
  printf("No se encontraron resultaodos...");
  return;
}

void mostrarOpcionesMenuMuestra() {
  printf("\n\n========================| Muestra y busqueda |========================\n");
  printf("[1]: Todos los pedidos.\n");
  printf("[2]: Pedidos por cliente.\n");
  printf("[3]: Pedidos por prioridad.\n");
  printf("[4]: Pedidos por estado.\n");
  printf("[5]: Monto promedio de pedidos pendientes.\n");
  printf("[6]: Pedidos con prioridad alta que esten 'En camino'.\n");
  printf("[7]: Cliente con mayor cantidad de pedidos.\n");
  printf("[8]: Tiempo promedio estimado de pedidos no entregados.\n");
  printf("[9]: Volver.\n");
}

void crearMenuMuestra(tNodo** cabecera) {
  int opcion;
  int salir = false;
  do {
    mostrarOpcionesMenuMuestra();
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    printf("\n\n");

    switch (opcion) {
    case 1:
      mostrarLista(cabecera);
      break;
    case 2:
      buscarPorCliente(cabecera);
      break;
    case 3:
      buscarPorPrioridad(cabecera);
      break;
    case 4:
      buscarPorEstado(cabecera);
      break;
    case 5:
      montoPromedioPedidosPendientes(cabecera);
      break;
    case 6:
      mostrarPedidosAltaEnCamino(cabecera);
      break;
    case 7:
      calcularClienteConMasPedidos(cabecera);
      break;
    case 8:
      tiempoPromedioDePedidosNoEntregados(cabecera);
      break;
    case 9:
      salir = true;
      break;
    default:
      printf("Opcion invalida.\n");
    }
  } while (!salir);
}

// Menu
void mostrarOpciones() {
  printf("\n\n========================| Menu |========================\n");
  printf(
      "[a]: Crear nuevo pedido (calcular automaticamente costo envio, tiempo y "
      "prioridad).\n");
  printf("[b]: Cambiar estado de un pedido (buscar por numero de pedido).\n");
  printf("[c]: Eliminar pedidos entregados.\n");
  printf("[d]: Muestra y busqueda.\n"); // Submenú
  printf(
      "[k]: Aplicar descuento del 10%% a pedidos de un cliente especifico.\n");
  printf(
      "[l]: Marcar como 'Entregado' todos los pedidos 'En camino' de mas de 60 "
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
    case 'b':
      cambiarEstaodDePedido(cabecera);
      break;
    case 'd':
      crearMenuMuestra(cabecera);
      break;
    case 'x':
      salir = true;
      break;

    default:
      printf("Opcion invalida.\n");
    }

  } while (!salir);
}