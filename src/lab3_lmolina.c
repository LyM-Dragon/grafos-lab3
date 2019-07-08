#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct{
    int index;
    ListaIndex* next;
}ListaIndex;

typedef struct{
    int idGen;
}Gen;

typedef struct{
    char idProceso[5];
    int profundidad;
    Gen* gen;
    ListaIndex* padres;
}ProcesoBio;

ListaIndex* crearLista(int newIndex){
    ListaIndex* new = (ListaIndex*)malloc(sizeof(ListaIndex));
    new->index = newIndex;
    new->next = NULL;
    return new;
}


ListaIndex* insertar(int newIndex, ListaIndex* lista){
    ListaIndex* new = (ListaIndex*)malloc(sizeof(ListaIndex));
    new->index = newIndex;
    new->next = lista;
    return new;
}

ListaIndex* siguiente(ListaIndex* lista, int posicion){

    if(posicion < 0 || lista == NULL){
        return NULL;
    }

    int contador = 1;
    while (contador <= posicion){
        contador++;
        lista = lista->next;
        if(lista == NULL){
            return NULL;
        }
    }

    return lista;
}

int* crearArregloGenes(int size){
    int* arreglo = (int*)malloc(sizeof(int) * size);
    if (arreglo != NULL){
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de genes\n");
        return NULL;
    }
}

ProcesoBio* crearArregloProcesoBio(int size){
    ProcesoBio* arreglo = (ProcesoBio*)malloc(sizeof(ProcesoBio) * size);
    if (arreglo != NULL){
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de procesos biológicos\n");
        return NULL;
    }
}

void freeListaIndex(ListaIndex* lista){
    int i;

    while(lista != NULL){
        ListaIndex* old = lista;
        lista = lista->next;
        free(old);
    }
}

void freeContProcesoBio(ProcesoBio* procesoBio){
    if (procesoBio != NULL){
        free(procesoBio->gen);
        freeListaIndex(procesoBio->padres);
    }
}

void freeGrafo(ProcesoBio* procesoBio, int size){
    for (int i = 0; i < size; i++){
        freeContProcesoBio(&procesoBio[i]);
    }
    free(procesoBio);
}


void printGrafo(ProcesoBio* grafo, int size){

    for (int i = 1; i < size; i++){
        ProcesoBio vertice = grafo[i];
        printf("%s ", vertice.idProceso);
        printf("%s ", vertice.idProceso);
    }
    
}

// void printMatriz(int** matriz, int size){
// 	int i,j;
// 	for(i=0;i<size;i++){
// 		for(j=0;j<size;j++){
// 			printf("%d ",matriz[i][j]);
// 		}
// 		printf("\n");
// 	}
// }


// int main(){
//     FILE *archivo = fopen("grafo.in","r");

//     if(archivo==NULL)
//     {
//         printf("ERROR: El archivo no se pudo abrir, escriba el nombre correctamente con su extension.");
//         return 1;
//     }
//     int size;
//     fscanf(archivo,"%d",&size);
//     int **matrizAdyacencia=crearMatrizAdy(archivo,size);
//     fclose(archivo);

//     printMatriz(matrizAdyacencia,size);
    
    
//     freeMatriz(matrizAdyacencia,size);

//     return 0;
// }


ProcesoBio* cargarGenes(FILE *archivo){

}

ProcesoBio* cargarGrafo(FILE *archivo){

}

void imprimirGrafo(ProcesoBio* grafo){

}

ProcesoBio encontrarAncenstroComun(ProcesoBio vertice1, ProcesoBio vertice2, int size){

}

int determinarLongitudCamino(ProcesoBio hijo, ProcesoBio ancestro, int size){

}

int determinarProfundidadGrafo(ProcesoBio* grafo){

}

double calcularWuPalmer(ProcesoBio vertice1, ProcesoBio vertice2, int size){

}

double calcularLeacockChorodow(ProcesoBio vertice1, ProcesoBio vertice2, int size){

}

//retorna indice de proceso si existe, sino retorna -1
int existeProceso(char idProceso[5], ProcesoBio* grafo){

}

bool existeGen(Gen gen, ProcesoBio* grafo){

}

double calcularSimilitudGenes(Gen gen1, Gen gen2, ProcesoBio* grafo){
    if (!(existeGen(gen1, grafo) && existeGen(gen2, grafo))){
        return -1;
    }
}

int main(){
    return 0;
}