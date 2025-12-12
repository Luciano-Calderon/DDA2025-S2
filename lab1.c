#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*     Funciones Importantes     */

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

//Notamos que para filas y columnas, una solucion más eficiente se obtiene utilizando matemáticas,
//ya que no importan las posiciones en que quedan, sino los movimientos que realizan

/*     Filas     */

int min_pasos_fila(int pair_of_positions[], int prime_number) { //Función Funciona, valga la redundancia XD. Pensar en una versión recursiva está pendiente
	int* filas = (int*)malloc(prime_number*sizeof(int)); 
	int* columnas = (int*)malloc(prime_number*sizeof(int)); 

	//Separar filas y columnas
	for (int k = 0; k < prime_number; k++) {
		filas[k] = pair_of_positions[2*k];
		columnas[k] = pair_of_positions[2*k + 1];
	}
	
	ordenar(columnas, prime_number); //se ordenan columnas
	int mejor = INT_MAX;

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

/*     Columnas     */

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

/*     Diagonal Descendente     */

void funcion_recursiva_diagonal_descendente(int k, int costo_actual, int* menor, int posiciones[], int* usados, int n) {
    //podamos los casos que no sirven
    if (costo_actual >= *menor) return;

    //retorno si se revisan todas las piedras
    if (k == n) {
        if (costo_actual < *menor) {
            *menor = costo_actual;
        }
        return;
    }

    //como es la diagonal descendente, las posiciones cambian con k
    int obj_f = k + 1;
    int obj_c = k + 1;

    //calculo la distancia a todas las piedras disponibles
    for (int i = 0; i < n; i++) {
        if (usados[i] == 0) {
            
            int piedra_f = posiciones[2 * i];
            int piedra_c = posiciones[2 * i + 1];

            int distancia = valor_absoluto(piedra_f - obj_f) + valor_absoluto(piedra_c - obj_c);

            usados[i] = 1;
            funcion_recursiva_diagonal_descendente(k + 1, costo_actual + distancia, menor, posiciones, usados, n);
            usados[i] = 0;
        }
    }   
}

int min_pasos_diagonal_descendente(int posiciones_en_pares[], int n) {
    int* usados = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        usados[i] = 0; //marco que ninguna posicion ha sido usada
    }

    int menor = INT_MAX;

    funcion_recursiva_diagonal_descendente(0, 0, &menor, posiciones_en_pares, usados, n);

	free(usados);
    return menor;
}

/*     Diagonal Ascendente     */

void funcion_recursiva_diagonal_ascendente(int k, int costo_actual, int* menor, int posiciones[], int* usados, int n) {

    //repetimos los casos de corte
    if (costo_actual >= *menor) return;

    if (k == n) {
        if (costo_actual < *menor) {
            *menor = costo_actual;
        }
        return;
    }

    //en este caso solo la columna asciende en posicion, pero la fila desciende
    int obj_f = n - k;
    int obj_c = k + 1;

    for (int i = 0; i < n; i++) {
        if (usados[i] == 0) {

            int piedra_f = posiciones[2 * i];
            int piedra_c = posiciones[2 * i + 1];

            int distancia = valor_absoluto(piedra_f - obj_f) + valor_absoluto(piedra_c - obj_c);

            usados[i] = 1;
            funcion_recursiva_diagonal_ascendente(k + 1, costo_actual + distancia, menor, posiciones, usados, n);
            usados[i] = 0;
        }
    }
}

int min_pasos_diagonal_ascendente(int posiciones_en_pares[], int n) {
    int* usados = (int*)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++){
        usados[i] = 0;
    }

    int menor = INT_MAX;
	
    funcion_recursiva_diagonal_ascendente(0, 0, &menor, posiciones_en_pares, usados, n);
	
	free(usados);
    return menor;
}

/*     Main     */

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

	/*Hasta acá, se extraen los datos requeridos de la entrada txt, donde la 1ra línea es el tamaño n de la cuadrilla nxn,
	 que además es la cantidad de n rocas, mientras que la 2da línea colecciona el par de posiciones de cada roca.
	*/ 
	
	//ahora se hará una busqueda para filas, columnas y diagonales y se determinará cual es menor
	int min_f = min_pasos_fila(pair_of_positions, prime_number);
	int min_c = min_pasos_columna(pair_of_positions, prime_number);
	int min_da = min_pasos_diagonal_ascendente(pair_of_positions, prime_number);
	int min_dd = min_pasos_diagonal_descendente(pair_of_positions, prime_number);

	int min = min_f;

	if(min_c < min_f){
		min_f = min_c;
	}
	if(min_da < min_f){
		min_f = min_da;
	}
	if(min_dd < min_f){
		min_f = min_dd;
	}

	printf("%d\n", min_f);
	
	return 0;
}
