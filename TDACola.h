#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico{
  int dato;
  struct nodoGenerico *puntero;
}nodo;

typedef struct {
  int capacidad;
  int size;
  nodo *frente;
  nodo *final;
}Cola;

/*------------- funciones -------------*/

Cola *crearColaVacia();
nodo *crearNodoGenerico();

nodo *frente();
nodo *final();

int esColaVacia();                       //return 1 (True) o 0 (False)
void imprimirCola();                     //return void
void encolar();                          //return void
int descolar();                          //return int del primer valor añadido a la cola
int numElementosCola();                  //return int
Cola *reemplazarOcurrenciasSuma();       //return Cola *colaIngresada (no es necesario redefinirla, la ordena de base)
int encontrarMenor();                    //return int valor menor (->dato)
int encontrarMayor();                    //return int valor mayor (->dato)
void eliminarValor();                    //return void
Cola *ordenarAscendente();               //return Cola *colaIngresada (no es necesario redefinirla, la ordena de base)
void eliminarUltimo();                   //return void

/*------------- operaciones -------------*/

Cola *crearColaVacia(int capacidad){
  Cola *cola=(Cola*)malloc(sizeof(Cola));
  cola->capacidad=capacidad;
  cola->size=0;
  cola->frente=NULL;
  cola->final=NULL;
  return cola;
}

nodo *crearNodoGenerico(){
	nodo *N = (nodo*)malloc(sizeof(nodo));
	N->puntero = NULL;
	return N;
}

int esColaVacia(Cola *cola){
  if (cola->size == 0)
    return 1;
  else
    return 0;
}

nodo *frente(Cola *cola){
  if (esColaVacia(cola)){
    printf("La cola está vacía\n");
    return NULL;
  }
  else
    return cola->frente;
}

nodo *final(Cola *cola){
  if (esColaVacia(cola)){
    printf("La cola está vacía\n");
    return NULL;
  }
  else
    return cola->final;
}

void imprimirCola(Cola *cola){
	if(esColaVacia(cola))
		printf("La cola esta vacia\n");
	else{
		nodo *aux = cola->frente;
		int i = 1;
		printf("\n");
		while(aux != NULL){
			printf("Dato %d es: %d\n", i, aux->dato);
			i++;
			aux = aux->puntero;
		}
		printf("\n");
	}
}

/*------------ Actividad 2 ------------*/
void encolar(Cola *cola, int dato){
	nodo *aux1 = crearNodoGenerico();
	aux1->dato = dato;
	if((esColaVacia(cola))){
		cola->frente = aux1;
		cola->final = aux1;
		cola->size = cola->size + 1;
	}else{
		nodo *aux2 = cola->final;
		aux2->puntero = aux1;
		cola->final = aux1;
		aux1->puntero = NULL;
		cola->size = cola->size + 1;
	}
}
/*------------ Actividad 3 ------------*/
int descolar(Cola *cola){
	nodo *aux1 = cola->frente;
	if(aux1->puntero == NULL){
		cola->frente = NULL;
		cola->final = NULL;
		cola->size = 0;
		int valor = aux1->dato;
		free(aux1);
		return valor;
	}else{
		nodo *aux2 = aux1->puntero;
		cola->frente = aux2;
		int valor = aux1->dato;
		free(aux1);
		cola->size = cola->size - 1;
		return valor;
	}
}
/*------------ Actividad 4 ------------*/
int numElementosCola(Cola *cola){
	nodo *aux = cola->frente;
	int contador = 0;
	while(aux != NULL){
		contador++;
		aux = aux->puntero;
	}
	return contador;
}
/*------------ Actividad 5 ------------*/
Cola *reemplazarOcurrenciasSuma(Cola *cola, int v1, int v2){
	nodo *aux = cola->frente;
	while(aux != NULL){
		if(aux->dato == v1){
			aux->dato = v1+v2;
		}
		aux = aux->puntero;
	}
	return cola;
}
/*------------- funciones auxiliares -------------*/
int encontrarMenor(Cola *cola){
	nodo *aux = cola->frente;
	int valor = aux->dato;
	while(aux != NULL){
		if(aux->dato < valor){
			valor = aux->dato;
			aux = aux->puntero;
		}else{
			aux = aux->puntero;
		}
	}
	return valor;
}

int encontrarMayor(Cola *cola){
	nodo *aux = cola->frente;
	int valor = aux->dato;
	while(aux != NULL){
		if(aux->dato > valor){
			valor = aux->dato;
			aux = aux->puntero;
		}else{
			aux = aux->puntero;
		}
	}
	return valor;
}

void eliminarValor(Cola *cola, int valor){
	nodo *aux1 = cola->frente;
	if(aux1->dato == valor){
		cola->frente = aux1->puntero;
		free(aux1);
		cola->size = cola->size-1;
	}else{
		while(aux1->puntero != NULL){
			if((aux1->puntero)->dato == valor){
				nodo *aux2 = aux1->puntero;
				aux1->puntero = aux2->puntero;
				free(aux2);
				cola->size = cola->size-1;
				break;
			}else{
			aux1 = aux1->puntero;
			}
		}
	}
}
/*------------ Actividad 6 ------------*/
Cola *ordenarAscendente(Cola *cola){
	int capacidad = numElementosCola(cola);
	Cola *colaAux = crearColaVacia(capacidad);
	nodo *aux = cola->frente;
	while(!esColaVacia(cola)){
		int valor = encontrarMenor(cola);
		encolar(colaAux, valor);
		eliminarValor(cola, valor);
	}
	while(!esColaVacia(colaAux)){
		encolar(cola, colaAux->frente->dato);
		descolar(colaAux);
	}
	free(colaAux);
	return cola;
}

/*------------- funciones auxiliares -------------*/

void eliminarUltimo(Cola *cola){
	nodo *aux1 = cola->frente;
	if(aux1->puntero == NULL){
		cola->frente = NULL;
		cola->final = NULL;
		cola->size = 0;
		free(aux1);
	}else{
		while((aux1->puntero)->puntero != NULL){
			aux1 = aux1->puntero;
		}
		nodo *aux2 = aux1->puntero;
		aux1->puntero = NULL;
		cola->final = aux1;
		free(aux2);
		cola->size = cola->size - 1;
	}
}