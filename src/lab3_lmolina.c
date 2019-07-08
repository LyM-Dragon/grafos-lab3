#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


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

typedef struct{
    int profundidad;
    ProcesoBio* vertices;
}Grafo;


//***OPERACIONES DE ESTRUCTURAS DEFINIDAS***

ListaIndex* crearListaIndex(int newIndex){
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

int crearGen(int idGen){
    Gen* gen = (Gen*)malloc(sizeof(Gen));
    if (gen != NULL){
        gen->idGen = idGen;
        return gen;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear Gen\n");
        return NULL;
    }
}

Gen* crearArregloGenes(int size){
    Gen* arreglo = (Gen*)malloc(sizeof(Gen) * size);
    if (arreglo != NULL){
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de genes\n");
        return NULL;
    }
}

ProcesoBio crearProcesoBio(char idProceso[5], int profundidad){
    ProcesoBio* proceso = (ProcesoBio*)malloc(sizeof(ProcesoBio));
    if (proceso != NULL){
        strcpy(proceso->idProceso, idProceso);
        proceso->profundidad = profundidad;
        proceso->gen = NULL;
        proceso->padres = NULL;

        return proceso;   
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear Proceso biológico\n");
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

Grafo* crearGrafo(int cantidadVertices){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo != NULL){
        ProcesoBio* arregloProcesos = crearArregloProcesoBio(cantidadVertices);
        if(arregloProcesos != NULL){
            grafo->vertices = arregloProcesos;
            grafo->profundidad = -1;
        }else{
            return NULL;
        }

        return grafo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de procesos biológicos\n");
        return NULL;
    }   
}

int obtenerIndiceProcesoBio(char identificador[5], ProcesoBio* grafo, int size){
    for (int i = 0; i < size; i++){
        if (strcmp(grafo[i].idProceso, identificador) == 0){
            return i;
        }
    }

    return -1;
}


//***OPERACIONES DE LIMPIEZA DE MEMORIA***

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

void freeGrafo(Grafo* grafo, int size){
    for (int i = 0; i < size; i++){
        freeContProcesoBio(&grafo->vertices[i]);
    }
    free(&grafo->vertices);
    free(grafo);
}


void printGrafo(ProcesoBio* grafo, int size, int profundidad){

    for (int i = 0; i < size; i++){
        ProcesoBio vertice = grafo[i];
        if (vertice.padres == NULL){
            printf("%s\n", vertice.idProceso);
            continue;
        }

        printf("%s ", vertice.idProceso);
        printf("%s ", vertice.idProceso);
    }
    
}


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


Grafo* cargarGrafo(FILE *archivo){
    int size;
    char idProceso[5];
    char chr;
    fscanf(archivo,"%d",&size);
    fscanf(archivo,"%s", &idProceso);
    Grafo* grafo = crearGrafo(size);
    strcpy(grafo->vertices[0].idProceso, idProceso);
    grafo->vertices[0].profundidad = 0;
    grafo->vertices[0].padres = NULL;
    grafo->vertices[0].gen = NULL;
    int palabraCount = 0;

    for (int i = 1; i < size; i++){
        while(fscanf(archivo, "%s%c", &idProceso, &chr) != EOF){
            if(palabraCount == 0){
                //Es un nuevo vértice
                ProcesoBio newProceso = {idProceso, -1, NULL, NULL};
                grafo->vertices[i] = newProceso;
                palabraCount++;
            }else if(palabraCount == 1){
                //Primer padre del vértice
                int indicePadre = obtenerIndiceProcesoBio(idProceso, grafo->vertices, i+1);
                grafo->vertices[i].padres = crearListaIndex(indicePadre);
                grafo->vertices[i].profundidad = grafo->vertices[indicePadre].profundidad + 1;
            }else{
                //Más padres
                int indicePadre = obtenerIndiceProcesoBio(idProceso, grafo->vertices, i+1);
                grafo->vertices[i].padres = insertar(indicePadre, grafo->vertices[i].padres);
                int profundidadTemp = grafo->vertices[indicePadre].profundidad + 1;
                if(profundidadTemp > grafo->vertices[i].profundidad){
                    grafo->vertices[i].profundidad = profundidadTemp;
                }
            }

            if(chr = '\n'){
                palabraCount = 0;
                break;
            }
        }
    }

    return grafo;
    
}

ProcesoBio* cargarGenes(FILE *archivo){

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


int similitudGenes(){
    FILE *archivoProcesos = fopen("input/procesos.in","r");
    
    if(archivoProcesos==NULL)
    {
        printf("ERROR: El archivo procesos.in no se pudo abrir, escriba el nombre correctamente con su extension.");
        return 1;
    }

    ProcesoBio* grafo = cargarGrafo(archivoProcesos);

    int size;
    fscanf(archivoProcesos,"%d",&size);
    int **matrizAdyacencia=crearMatrizAdy(archivoProcesos,size);
    fclose(archivoProcesos);

    printMatriz(matrizAdyacencia,size);
    
    
    freeMatriz(matrizAdyacencia,size);

    return 0;
}

int main(){
    return similitudGenes();
}