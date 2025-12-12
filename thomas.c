#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
	int mejor = INT_MAX;

	for (int fila_obj = 1; fila_obj <= prime_number; fila_obj++) {
		int costo_filas = 0;
		int costo_columnas = 0;

		for (int k = 0; k < prime_number; k++) {
			costo_filas += valor_absoluto(filas[k] - fila_obj);
			costo_columnas += valor_absoluto(columnas[k] - (k+1));
		}

		int total = costo_filas + costo_columnas;

		if (total < mejor) {
			mejor = total;
		}
	}

	return mejor;
	}
	
void ordenar_por_columna(int pair_positions[], int n) {
    //n es el número de piedras (pares)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            int fila1 = pair_positions[2*j];          //fila del par j
            int col1  = pair_positions[2*j + 1];      //columna del par j

            int fila2 = pair_positions[2*(j+1)];      //fila del par j+1
            int col2  = pair_positions[2*(j+1) + 1];  //columna del par j+1

            // Ordenar por columna
            if (col1 > col2 || (col1 == col2 && fila1 > fila2)) {

                // Intercambiar pares completos
                int tmp_f = fila1;
                int tmp_c = col1;
                pair_positions[2*j] = fila2;
                pair_positions[2*j + 1] = col2;
                pair_positions[2*(j+1)] = tmp_f;
                pair_positions[2*(j+1) + 1] = tmp_c;
            }
        }
    }
}

int min_pasos_diagonal_desc(int pair_positions[], int n) {
    // Primero ordenamos las piedras por columna ascendente
    ordenar_por_columna(pair_positions, n);
    int costo_total = 0;

    for (int k = 0; k < n; k++) {
        int fila_actual = pair_positions[2*k];
        int col_actual  = pair_positions[2*k + 1];

        costo_total += abs(fila_actual - (k+1));
        costo_total += abs(col_actual - (k+1));
    }

    return costo_total;
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
		pair_of_positions[i] = n; //índices van originalmente del 1 al n
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
	 int valor, valor2;
	 valor = min_pasos_fila(pair_of_positions, prime_number);
	 valor2 = min_pasos_diagonal_desc(pair_of_positions, prime_number);
	 printf("\nLa cantidad mínima de pasos para formar una fila son: %d pasos\n",valor);
	 printf("\n Los pasos mínimos para realizar una diagonal descendente son: %d pasos \n", valor2);

	return 0;
}