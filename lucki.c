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

void ordenar_ambas(int arreglo1[], int arreglo2[], int largo){
	for(int i=0; i<largo-1; i++){
		for(int j=0; j<largo-1-i; j++){
			if(arreglo1[j] > arreglo1[j+1]){
				int aux = arreglo1[j];
				arreglo1[j] = arreglo1[j+1];
				arreglo1[j+1] = aux;

				aux = arreglo2[j];
				arreglo2[j] = arreglo2[j+1];
				arreglo2[j+1] = aux;
			}
		}	
	}
}

int min_pasos_columna(int posiciones_en_pares[], int n){

	int* filas = (int*)malloc(n*sizeof(int)); 
	int* columnas = (int*)malloc(n*sizeof(int));

	for (int k = 0; k < n; k++) {
		filas[k] = posiciones_en_pares[2*k];
		columnas[k] = posiciones_en_pares[2*k + 1];
	}

	//primero se deben ordenar los valores de posicion de fila de cada piedra de forma ascendente
	//de esta forma se podrá calcular el costo de mover cada piedra de forma vertical, y luego asumir
	//que hay una piedra por cada fila, simplificando el calculo de costo de las columnas
	ordenar(filas, n);

	//ahora se define un numero MAX como la menor cantidad de pasos, para ir reemplazandolos cuando
	//se vaya encontrando otro valor menor
	int menor = INT_MAX;

	//se parte iterando
	for(int columna = 1; columna <= n; columna++){
		int costo_columnas = 0;
		int costo_filas = 0;

		for(int piedra = 0; piedra < n; piedra++){

			//primero se calcula el costo de mover una piedra a una fila
			//logrando que quede teoricamente una piedra por cada fila
			costo_columnas += valor_absoluto(columnas[piedra] - columna);

			//luego se calcula el costo de mover la piedra de esa columna a la columna en la que estamos
			costo_filas += valor_absoluto(filas[piedra] - (piedra + 1)); 
		}

		if((costo_columnas + costo_filas) < menor){
			menor = costo_columnas + costo_filas;
		}
	}
	return menor;
}

int min_pasos_diagonal_subida(int posiciones_en_pares[], int n){

	int* filas = (int*)malloc(n*sizeof(int)); 
	int* columnas = (int*)malloc(n*sizeof(int));

	for (int k = 0; k < n; k++) {
		filas[k] = posiciones_en_pares[2*k];
		columnas[k] = posiciones_en_pares[2*k + 1];
	}

	ordenar_ambas(filas, columnas, n);
	int menor = INT_MAX;

	for(int columna = 1; columna <= n; columna++){
		int costo_columnas = 0;
		int costo_filas = 0;
		
		for(int piedra = 0; piedra < n; piedra++){
			
			//repito el proceso de ordenar, de forma teórica, una piedra por fila
			//lo que me entrega la cantidad de movimeintos entre filas
			costo_filas += valor_absoluto(columnas[piedra] - columna);
			if(costo_filas > 0){
				columnas[piedra] = columna;
			}
			
			//luego se calcula el costo de mover la piedra de esa columna a la columna en la que estamos
			for(int i = 0; i < n; i++){
				if(filas[i] == piedra){
					costo_columnas += valor_absoluto(columnas[i] - (piedra + 1)); 
				}
			}
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
	
	//int min = min_pasos_columna(pair_of_positions, prime_number);
	int min = min_pasos_diagonal_subida(pair_of_positions, prime_number);
	printf("\n%d\n", min);

	return 0;
}

//hola thomas, aquí voy a escribir mi codigo
