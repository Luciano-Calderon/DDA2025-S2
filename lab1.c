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

/*     Contadora de movimientos     */

int min_movimientos(int *pair_of_positions, int n){

    int min_f = min_pasos_fila(pair_of_positions, n);
	int min_c = min_pasos_columna(pair_of_positions, n);
	int min_da = min_pasos_diagonal_ascendente(pair_of_positions, n);
	int min_dd = min_pasos_diagonal_descendente(pair_of_positions, n);

	int min = min_f;

	if(min_c < min){
		min = min_c;
	}
	if(min_da < min){
		min = min_da;
	}
	if(min_dd < min){
		min = min_dd;
	}

    return min;
}

/*     Main     */

int main(int argc, char* argv[]){
    
    //asumo que el maximo de casos por entrada al inicio es 10
    int max_casos = 10; 
    int casos = 0;

    int** arreglo_pair_of_positions = (int**)malloc(max_casos * sizeof(int*));
    int* largo_casos = (int*)malloc(max_casos * sizeof(int));

    //comienzo a leer y a guardar hasta llegar al 0
    int dato;
    while(scanf("%d", &dato) && dato != 0) {
        
        //reviso si se acabó el espacio por la cantidad de casos leídos
        if (casos == max_casos) {

            //en caso de que si se acabó, creo arreglos mas grandes
            int max_casos_nuevo = max_casos * 2;
            int** arreglo_posiciones_nuevo = (int**)malloc(max_casos_nuevo*sizeof(int*));
            int* largo_casos_nuevo = (int*)malloc(max_casos_nuevo*sizeof(int));
            
            //ahora muevo todo a los nuevos arreglos
            for(int i = 0; i < casos; i++){
                arreglo_posiciones_nuevo[i] = arreglo_pair_of_positions[i];
                largo_casos_nuevo[i] = largo_casos[i];
            }
            
            //borro los arreglos antiguos
            free(arreglo_pair_of_positions);
            free(largo_casos);
            
            //redirijo los punteros
            arreglo_pair_of_positions = arreglo_posiciones_nuevo;
            largo_casos = largo_casos_nuevo;
            max_casos = max_casos_nuevo;
        }

        largo_casos[casos] = dato;

        //reservo memora para este "pair_of_positions"
        arreglo_pair_of_positions[casos] = (int*)malloc(dato*2*sizeof(int));

        //leo y guardo en el arreglo
        for(int i = 0; i < dato * 2; i++) {
            scanf("%d", &arreglo_pair_of_positions[casos][i]);
        }

        casos++;
    }

    //ahora se realiza el print de movimientos por cada caso
    for(int i = 0; i < casos; i++) {
        int movimientos = min_movimientos( arreglo_pair_of_positions[i], largo_casos[i]);
        printf("%d\n", movimientos);
    }

    //por ultimo se liberaa el espacio de cada arreglo
    for(int j = 0; j < casos; j++) {
        free(arreglo_pair_of_positions[j]);
    }
    free(arreglo_pair_of_positions);
    free(largo_casos);

    return 0;
}