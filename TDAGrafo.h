#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "TDALista.h"
#include "TDACola.h"

/*------------- estructura de datos -------------*/

typedef struct matrizGrafo{
	int cvertices;
	int** MA;
}Grafo;

/*------------- funciones -------------*/

Grafo *crearGafoVacio();

void imprimirMatrizAdyacencia();         //printf matriz de adyacencia
int adyacenciaNodos();                   //return 1 (True) o 0 (False)
Grafo *leerGrafoNoDirigido();            //rerurn Grafo leído
Lista *obtenerAdyacentes();              //return Lista con adyacentes
int esCamino();                          //return 1 (True) o 0 (False)
int esCompleto();                        //return 1 (True) o 0 (False)
int esComplemento();                     //return 1 (True) o 0 (False)
int gradoVertice();                      //return cantidad de aristas que tiene el vértice
int gradoPromedio();                     //return promedio del grado de los vértices
int esRegular();                         //return 1 (True) o 0 (False)  (True es que todos los vertices tienen el mismo grado)
Grafo *leerGrafoDirigidoPonderado();     //return Grafo leído
void BFS();                              //return void pero necesita los punteros de visitados, distancia y procedencia, aparte del grafo y el vertice
void DFS();                              //return void pero necesita el puntero de visitados, aparte del grafo y el vertice
int quedanSinVisitar();                  //return 1 (True) o 0 (False)
int extraerMinimo();                     //return int vertice con distancia minima que no ha sido visitado, si están todos visitados devuelve -1
void Dijkstra();                         //return void, modifica procedencia para obtener el camino mínimo
void imprimirCamino();                   //return void con el camino generado por dijkstra o bfs, necesita un puntero a precedencia
int contarVerticesDeGrado();             //return int con la cantidad de vertices que tienen ese grado
int hayCamino();                         //return 1 (True) o 0 (False), si es que hay un camino entre 2 vertices, necesita un puntero a precedencia
int esConexo();                          //return 1 (True) o 0 (False), necesita un puntero a precedencia

/*----------------- operaciones -----------------*/

Grafo *crearGrafoVacio(int vertices){
	Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
	grafo->cvertices = vertices;
	grafo->MA = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++){
		grafo->MA[i] = (int*)malloc(vertices * sizeof(int));
		//Inicializa en cero
		for(j=0;j<vertices;j++){
			grafo->MA[i][j] = 0;
		}	
	}
	return grafo;
}

void imprimirMatrizAdyacencia(Grafo *grafo){
	int i, j;
	for (i = 0; i < grafo->cvertices; i++) {
		for (j = 0; j < grafo->cvertices; j++){
			printf("%d ", grafo->MA[i][j]);
		}
		printf("\n");
	}
}

int adyacenciaNodos(Grafo *grafo, int vertA, int vertB){
	if (grafo->MA[vertA][vertB] != 0){
		return 1;
	}
	return 0;
}

//NoDirigido NoPonderado
Grafo *leerGrafoNoDirigido(char *nombreArchivo){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		Grafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d",&i, &j);
			G->MA[i][j] = 1;
			G->MA[j][i] = 1;
		}
		fclose(pf);
		return  G;	
	}
}

// para vértices enteros del 0 a n
Lista *obtenerAdyacentes(Grafo *grafo, int vertice){
	Lista *adyacencia = crearLista();
	for(int i=0; i<grafo->cvertices; i++){
		if(adyacenciaNodos(grafo, vertice, i)){
			insertarFinal(adyacencia, i);
		}
	}
	return adyacencia;
}

int esCamino(Grafo *grafo, Lista *secuencia){
	int bandera = 1;
	Nodo *aux = secuencia->cabecera;
	if(aux != NULL){
		int vertice = aux->dato;
		while(aux->siguiente != NULL){
			if(adyacenciaNodos(grafo, vertice, aux->siguiente->dato)){
				vertice = aux->siguiente->dato;
			}else{
				bandera = 0;
				break;
			}
			aux = aux->siguiente;
		}
	}
	return bandera;
}

int esCompleto(Grafo *grafo){
	int bandera = 1;
	for(int i=0; i<grafo->cvertices; i++){
		for(int j=0; j<grafo->cvertices; j++){
			if(i!=j && grafo->MA[i][j] == 0){
				bandera = 0;
			}
		}
	}
	return bandera;
}

int esComplemento(Grafo *grafo1, Grafo *grafo2){
	if(grafo1->cvertices != grafo2->cvertices){
		return 0;
	}else{
		for(int i=0; i<grafo1->cvertices; i++){
			for(int j=0; j<grafo1->cvertices; j++){
				if(i!=j && (grafo1->MA[i][j]!=0) == (grafo2->MA[i][j]!=0)){
					return 0;
				}
			}
		}
	}
	return 1;
}

int gradoVertice(Grafo *grafo, int vertice){
	int grado = 0;
	for(int i=0; i<grafo->cvertices; i++){
		if(grafo->MA[vertice][i] != 0){
			grado++;
		}
	}
	return grado;
}

int gradoPromedio(Grafo *grafo){
	int grado = 0;
	for(int i=0; i<grafo->cvertices; i++){
		grado = grado + gradoVertice(grafo, i);
	}
	return grado/grafo->cvertices;
}

int esRegular(Grafo *grafo){
	int grado = gradoVertice(grafo, 0);
	for(int i=1; i<grafo->cvertices; i++){
		if(gradoVertice(grafo, i) != grado){
			return 0;
		}
	}
	return 1;
}

Grafo *leerGrafoDirigidoPonderado(char *nombreArchivo){
	FILE *pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k,l;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		Grafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(l=0;l<m_aristas;l++){
			fscanf(pf,"%d %d %d",&i, &j, &k);
			G->MA[i][j] = k;
		}
		fclose(pf);
		return  G;	
	}
}

void BFS(Grafo *grafo, int *visitados, int *distancia, int *precedencia, int vertice){
	for(int i=0; i<grafo->cvertices; i++){
		visitados[i] = 0;
		distancia[i] = INT_MAX;
		precedencia[i] = -1;
	}
	visitados[vertice] = 1;
	distancia[vertice] = 0;
	Cola *cola = crearColaVacia(grafo->cvertices);
	encolar(cola, vertice);
	while(cola->size != 0){
		int u = descolar(cola);
		Nodo *aux = obtenerAdyacentes(grafo, u)->cabecera;
		while(aux != NULL){
			if(visitados[aux->dato] == 0){
				visitados[aux->dato] = 1;
				distancia[aux->dato] = distancia[u] + 1;
				precedencia[aux->dato] = u;
				encolar(cola, aux->dato);
			}
			aux = aux->siguiente;
		}
	}
}

void DFS(Grafo *grafo, int *visitados, int vertice){
	for(int i=0; i<grafo->cvertices; i++){
		visitados[i] = 0;
	}
	Lista *pila = crearLista();
	insertarInicio(pila, vertice);
	while(pila->cabecera != NULL){
		int u = pila->cabecera->dato;
		eliminarInicio(pila);
		if(!visitados[u]){
			visitados[u] = 1;
			Lista *lista = obtenerAdyacentes(grafo, u);
			Nodo *aux2 = lista->cabecera;
			while(aux2 != NULL){
				if(!visitados[aux2->dato]){
					insertarInicio(pila, aux2->dato);
				}
				aux2 = aux2->siguiente;
			}
		}
	}
}

int quedanSinVisitar(int *visitados, int largo){
	for(int i=0; i<largo; i++){
		if(visitados[i] == 0){
			return 1;
		}
	}
	return 0;
}

int extraerMinimo(int *visitados, int *distancia, int largo){
	int minimo = INT_MAX;
	int vertice = -1;
	for(int i=0; i<largo; i++){
		if(visitados[i] == 0 && distancia[i]<minimo){
			minimo = distancia[i];
			vertice = i;
		}
	}
	return vertice;
}

void Dijkstra(Grafo *grafo, int *visitados, int *distancia, int *precedencia, int vertice){
	for(int i=0; i<grafo->cvertices; i++){
		visitados[i] = 0;
		precedencia[i] = -1;
		if(grafo->MA[vertice][i]>0){
			distancia[i] = grafo->MA[vertice][i];
			precedencia[i] = vertice;
		}else{
			distancia[i] = INT_MAX;
		}
	}
	distancia[vertice] = 0;
	visitados[vertice] = 1;
	while(quedanSinVisitar(visitados, grafo->cvertices)){
		int u = extraerMinimo(visitados, distancia, grafo->cvertices);
		if(u == -1){  //cuando no hay ninguno sin visitar, extraerMinimo devuelve -1
			break;
		}
		visitados[u] = 1;
		Lista *lista = obtenerAdyacentes(grafo, u);
		Nodo *aux = lista->cabecera;
		while(aux != NULL){
			if(distancia[aux->dato] > distancia[u]+grafo->MA[u][aux->dato]){
				distancia[aux->dato] = distancia[u]+grafo->MA[u][aux->dato];
				precedencia[aux->dato] = u;
			}
			aux = aux->siguiente;
		}
	}
}

void imprimirCamino(int *precedencia, int v1, int v2){
	if(v1 == v2){
		printf("%d", v1);
		return;
	}else{
		if(precedencia[v2] == -1){
			printf("No hay camino");
			return;
		}else{
			imprimirCamino(precedencia, v1, precedencia[v2]);
			printf(" -> %d", v2);
		}
	}
}

int contarVerticesDeGrado(Grafo *grafo, int grado){
	int vertices = 0;
	for(int i=0; i<grafo->cvertices; i++){
		if(gradoVertice(grafo, i) == grado){
			vertices++;
		}
	}
	return vertices;
}

int hayCamino(int *precedencia, int v1, int v2){
	if(v1 == v2){
		return 1;
	}else{
		if(precedencia[v2] == -1){
			return 0;
		}else{
			return hayCamino(precedencia, v1, precedencia[v2]);
		}
	}
}

int esConexo(Grafo *grafo, int *precedencia, int vertice){
	for(int i=0; i<grafo->cvertices; i++){
		if(hayCamino(precedencia, vertice, i) == 0){
			return 0;
		}
	}
	return 1;
}