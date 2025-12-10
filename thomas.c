#include <stdio.h>
#include <stdlib.h>

//Funciones para organizar posiciones de n piedras en grilla nxn
 
int valor_absoluto(int x) {
	if (x>=0){return x;}
	else{return -x;}
}
//Ordenar un arreglo ascendentemente (con ordenamiento bubble sort)
void bubble_sort(int arreglo[], int prime_number){
	int aux=0;
	while (aux < prime_number){
		int aux2=aux;
		while (aux2 < prime_number){
			if (arreglo[aux]>arreglo[aux2]){
				int temp = arreglo[aux];
				arreglo[aux] = arreglo[aux2];
				arreglo[aux2] = temp;
				}
			aux2 += 1;
			}
		aux += 1;
		}
	return;
}

int min_pasos_fila(int pair_of_positions[], int prime_number) { //Función Funciona, valga la redundancia XD. Pensar en una versión recursiva está pendiente
	int* filas = (int*)malloc(prime_number*sizeof(int)); 
	int* columnas = (int*)malloc(prime_number*sizeof(int)); 

	//Separar filas y columnas
	for (int k = 0; k < prime_number; k++) {
		filas[k] = pair_of_positions[2*k];
		columnas[k] = pair_of_positions[2*k + 1];
	}
	
	bubble_sort(columnas, prime_number); //se ordenan columnas
	int mejor = 1000000000;

	for (int fila_obj = 1; fila_obj <= prime_number; fila_obj++) {
		int costo_filas = 0;
		int costo_columnas = 0;

		for (int k = 0; k < prime_number; k++) {
			costo_filas += valor_absoluto(filas[k] - fila_obj);
			costo_columnas += valor_absoluto(columnas[k] - (k + 1));
		}

		int total = costo_filas + costo_columnas;

		if (total < mejor) {
			mejor = total;
		}
	}

	return mejor;
	}

int main(int argc, char* argv[]){
	//Extracción de Input
	FILE* archivo = fopen(argv[1],"r");
	int prime_number;
	fscanf(archivo, "%d", &prime_number);
	int* pair_of_positions = (int*)malloc(prime_number*2*sizeof(int));
	for (int i=0; i<prime_number*2; i++){
		int n;
		fscanf(archivo,"%d",&n);
		pair_of_positions[i] = n;
	}
	printf("El orden de la cuadrilla es %dx%d\n",prime_number,prime_number);
	int j=0;
	for (int i=0; i<(prime_number*2)-1; i=i+2){
		j++;
		printf("Posición %d: %d %d\n", j, pair_of_positions[i], pair_of_positions[i+1]);
		}

	/*Hasta acá, se extraen los datos requeridos de la entrada txt, donde la 1ra línea es el tamaño n de la cuadrilla nxn,
	 que además es la cantidad de n rocas, mientras que la 2da línea colecciona el par de posiciones de cada roca.
	 */ 
	 int valor;
	 valor = min_pasos_fila(pair_of_positions, prime_number);
	 printf("\n%d\n",valor);

	return 0;
}