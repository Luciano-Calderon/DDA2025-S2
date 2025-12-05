#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

struct nodo{
	int dato;
	struct nodo *siguiente;
};
typedef struct nodo Nodo;

struct lista{
	Nodo *cabecera;
};
typedef struct lista Lista;

/*------------- funciones -------------*/

Lista *crearLista();
Nodo *crearNodo();

int esListaVacia(Lista *L);                       // return 1 (True) o 0 (False)
void insertarInicio(Lista *L, int valor);         // return void
void insertarFinal(Lista *L, int valor);          // return void
void eliminarInicio(Lista *L);                    // return void
void eliminarFinal(Lista *L);                     // return void
void imprimirLista(Lista *L);                     // return void
int buscarElemento(Lista *L, int elemento);       // return int posicion o (-1) si no está
void eliminarElemento(Lista *L, int elemento);    // return void
int contarElementos(Lista *L);                    // return int cantidad
void invertirLista(Lista *L);                     // return void
Nodo *obtenerUltimoNodo(Lista *L);                // return Nodo *ultimo
void ordenarLista(Lista *L);                      // return void

/*------------- operaciones -------------*/

Lista *crearLista(){
	Lista *L = (Lista*)malloc(sizeof(Lista));  // pido un espacio <malloc> y lo convierto en un puntero a lista <Lista*>
	L->cabecera = NULL;  // digo que esa parte está vacía
	return L;  // devuelvo la lista para usarla después
}

Nodo *crearNodo(){
	Nodo *N = (Nodo*)malloc(sizeof(Nodo));  // pido un espacio <malloc> y lo convierto en un puntero a nodo <Nodo*>
	N->siguiente = NULL;  // digo que esa parte está vacía
	return N;  // devuelvo el nodo para usarlo después
}

int esListaVacia(Lista *L){
	if(L->cabecera == NULL)  // como tiene una sola instrucción, me puedo ahorrar los {}
		return 1;
	else
		return 0;
}

void insertarInicio(Lista *L, int valor){
	Nodo *nvnodo = crearNodo();
	nvnodo->dato = valor;
	
	if(esListaVacia(L)){
		L->cabecera = nvnodo;
	}else{
		nvnodo->siguiente = L->cabecera;
		L->cabecera = nvnodo;
	}
}

void insertarFinal(Lista *L, int valor){
	Nodo *nvnodo = crearNodo();
	nvnodo->dato = valor;
	
	if(esListaVacia(L)){
		L->cabecera = nvnodo;
	}else{
		Nodo *aux = L->cabecera;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente = nvnodo;
		nvnodo->siguiente = NULL;
	}
}

void eliminarInicio(Lista *L){
	Nodo *aux = L->cabecera;
	L->cabecera = aux->siguiente;
	free(aux);
}

void eliminarFinal(Lista *L){
	Nodo *aux = L->cabecera;
	while((aux->siguiente)->siguiente != NULL){
		aux = aux->siguiente;
	}
	free(aux->siguiente);
	aux->siguiente = NULL;
}

void imprimirLista(Lista *L){
	if(esListaVacia(L)){
		printf("La lista esta vacia\n");
	}else{
		Nodo *aux = L->cabecera;
		//printf("\nLa lista impresa es:\n");
		while(aux != NULL){
			printf("%d\n", aux->dato);
			aux = aux->siguiente;
		}
		printf("\n");
	}
}

int buscarElemento(Lista *L, int elemento){
	Nodo *aux = L->cabecera;
	int posicion = 0;
	while(aux != NULL){
		if(aux->dato == elemento){
			return posicion;
		} else {
			posicion++;
			aux = aux->siguiente;
		}
	}
	return -1;
}

void eliminarElemento(Lista *L, int elemento){
	Nodo *aux1 = L->cabecera;
	if(aux1->dato == elemento){
		eliminarInicio(L);
	}else{
		while(aux1 != NULL){
			if(aux1->siguiente != NULL && (aux1->siguiente)->dato == elemento){
				Nodo *aux2 = (aux1->siguiente)->siguiente;
				free(aux1->siguiente);
				aux1->siguiente = aux2;
				break; // para que borre solo el primer elemento que encuentre y no siga
			}else{
				aux1 = aux1->siguiente;
			}
		}
	}
}

int contarElementos(Lista *L){
	Nodo *aux = L->cabecera;
	int contador = 0;
	while(aux != NULL){
		contador++;
		aux = aux->siguiente;
	}
	return contador;
}

void invertirLista(Lista *L){
	Lista *nvlista = crearLista();
	Nodo *aux = L->cabecera;
	
	while(aux != NULL){
		insertarInicio(nvlista, aux->dato);
		aux = aux->siguiente;
		eliminarInicio(L);
	}
	L->cabecera = nvlista->cabecera;
}

Nodo *obtenerUltimoNodo(Lista *L){
	Nodo *aux = L->cabecera;
	while(aux->siguiente != NULL){
		aux = aux->siguiente;
	}
	return aux;
}

void ordenarLista(Lista *L){
	Nodo *aux = L->cabecera;
	int largo = contarElementos(L);
	int array[largo];
	
	int i=0;
	while(aux != NULL){
		array[i] = aux->dato;
		aux = aux->siguiente;
		i++;
	}
	
	for(int i=0; i<largo-1; i++){
		for(int j=0; j<largo-1-i; j++){
			if(array[j]>array[j+1]){
				int a = array[j];
				array[j] = array[j+1];
				array[j+1] = a;
			}
		}
	}
	
	while(!(esListaVacia(L))){
		eliminarInicio(L);
	}
	for(int i=0; i<largo; i++){
		insertarFinal(L, array[i]);
	}
}