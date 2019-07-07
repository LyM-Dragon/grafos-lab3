#include <stdlib.h>
#include <stdio.h>


typedef struct{
    int index;
    int* next;
}ListaIndices;

typedef struct{
    int id;
}Gen;

typedef struct{
    char[5];
    Gen* gen; // si no inicializo esto es igual a NULL?
    ListaIndices* padres; // si no inicializo esto es igual a NULL?
}ProcesoBio;


ProcesoBio* crearArregloProcesoBio(int size){
    ProcesoBio* arreglo = (int*)malloc(sizeof(ProcesoBio) * size);
    if (arreglo != NULL){
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de procesos biológicos\n");
        return NULL;
    }
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
    ProcesoBio* arreglo = (int*)malloc(sizeof(ProcesoBio) * size);
    if (arreglo != NULL){
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de procesos biológicos\n");
        return NULL;
    }
}

ProcesoBio* cargarGenes(FILE *archivo){

}

ProcesoBio* cargarGrafo(FILE *archivo){

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
int existeProceso(char[5] idProceso, ProcesoBio* grafo){

}

bool existeGen(Gen gen, ProcesoBio* grafo){

}

double calcularSimilitudGenes(Gen gen1, Gen gen2, ProcesoBio* grafo){
    if !(existeGen(gen1, grafo) && existeGen(gen2, grafo)){
        return -1;
    }
}

int main(){
    return 0;
}