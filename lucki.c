#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int valor_absoluto(int numero){
	if(numero < 0){
		return -numero;
	}
	return numero;
}

void ordenar(int arreglo[], int largo){
	for(int i=0; i<largo-1; i++){
		for(int j=0; j<largo-1-i; j++){
			if(arreglo[j] > arreglo[j+1]){
				int aux = arreglo[j];
				arreglo[j] = arreglo[j+1];
				arreglo[j+1] = aux;
			}
		}	
	}
}

int min_pasos_columna(int pair_of_positions[], int prime_number){

	int* filas = (int*)malloc(prime_number*sizeof(int)); 
	int* columnas = (int*)malloc(prime_number*sizeof(int));

	for (int k = 0; k < prime_number; k++) {
		filas[k] = pair_of_positions[2*k];
		columnas[k] = pair_of_positions[2*k + 1];
	}

	//primero se deben ordenar los valores de posicion de fila de cada piedra de forma ascendente
	//de esta forma se podrá calcular el costo de mover cada piedra de forma vertical, y luego asumir
	//que hay una piedra por cada fila, simplificando el calculo de costo de las columnas
	ordenar(filas, prime_number);

	//ahora se define un numero MAX como la menor cantidad de pasos, para ir reemplazandolos cuando
	//se vaya encontrando otro valor menor
	int menor = INT_MAX;

	//se parte iterando
	for(int columna = 1; columna <= prime_number; columna++){
		int costo_columnas = 0;
		int costo_filas = 0;

		for(int piedra = 0; piedra < prime_number; piedra++){

			//primero se calcula el costo de mover una piedra a una columna
			//logrando que quede teoricamente una piedra por cada columna
			costo_columnas += valor_absoluto(columnas[piedra] - columna);

			//luego se calcula el costo de mover la piedra de esa columna a la fila en la que estamos
			costo_filas += valor_absoluto(filas[piedra] - (piedra + 1)); 
		}

		if((costo_columnas + costo_filas) < menor){
			menor = costo_columnas + costo_filas;
		}
	}
	return menor;
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
		printf("Posicion %d: %d %d\n", j, pair_of_positions[i], pair_of_positions[i+1]);
		}

	/*Hasta acá, se extraen los datos requeridos de la entrada txt, donde la 1ra línea es el tamaño n de la cuadrilla nxn,
	 que además es la cantidad de n rocas, mientras que la 2da línea colecciona el par de posiciones de cada roca.
	 */ 
	
	int min = min_pasos_columna(pair_of_positions, prime_number);
	printf("\n%d\n", min);

	return 0;
}

//hola thomas, aquí voy a escribir mi codigo
