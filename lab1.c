#include <stdio.h>
#include <stdlib.h>

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
	 
	return 0;
}
