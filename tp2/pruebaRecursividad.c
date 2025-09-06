// Librerias
#include <stdio.h>
#include <stdlib.h>

// Prototipado
int sumatoria(int);

// Funcion principal
int main(){
	int n;
	printf("Ingrese el n base de la sumatoria: ");
	scanf("%d", &n);

	printf("El termino en la posicion %d es: %d\n", n, sumatoria(n));


	return 0;
}

int sumatoria(int n){
	if(n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		return sumatoria(n - 1) + sumatoria(n);
	}
}







