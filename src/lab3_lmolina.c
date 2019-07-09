#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct ListaIndex{
    int index;
    struct ListaIndex* next;
}ListaIndex;

typedef struct Gen{
    int idGen;
    struct Gen* next;
}Gen;

typedef struct{
    char idProceso[5];
    int profundidad;
    Gen* genes;
    ListaIndex* padres;
}ProcesoBio;

typedef struct{
    int cantidadVertices;
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


ListaIndex* insertarListaIndex(int newIndex, ListaIndex* lista){
    ListaIndex* new = (ListaIndex*)malloc(sizeof(ListaIndex));
    new->index = newIndex;
    new->next = lista;
    return new;
}

ListaIndex* siguienteListaIndex(ListaIndex* lista, int posicion){

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

Gen* crearListaGen(int idGen){
    Gen* new = (Gen*)malloc(sizeof(Gen));
    new->idGen = idGen;
    new->next = NULL;
    return new;
}

Gen* insertarListaGen(int idGen, Gen* lista){
    Gen* new = (Gen*)malloc(sizeof(Gen));
    new->idGen = idGen;
    new->next = lista;
    return new;
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
    ProcesoBio newProceso = {"", profundidad, NULL, NULL};
    strcpy(newProceso.idProceso, idProceso); 
    return newProceso;
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
            grafo->cantidadVertices = cantidadVertices;
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

    printf("Proceso %s no encontrado", identificador);
    return -1;
}


//***OPERACIONES DE LIMPIEZA DE MEMORIA***

void freeGenes(Gen* genes){
    int i;
    while(genes != NULL){
        Gen* old = genes;
        genes = genes->next;
        free(old);
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
        freeGenes(procesoBio->genes);
        freeListaIndex(procesoBio->padres);
    }
}

void freeGrafo(Grafo* grafo){
    for (int i = 0; i < grafo->cantidadVertices; i++){
        freeContProcesoBio(&grafo->vertices[i]);
    }
    free(grafo->vertices);
    free(grafo);
}


void printGenes(Gen* genes){
    printf("| genes: ");
    while(genes != NULL){
        printf("%d ", genes->idGen);
        genes = genes->next;
    }
}

void printPadres(ListaIndex* padres, ProcesoBio* vertices, int cantidadVertices){
    while(padres != NULL){
        for (int i = 0; i < cantidadVertices; i++){
            if(padres->index == i){          
                printf("%s ", vertices[i].idProceso);
            }
        }
        padres = padres->next;
    }
}

void printGrafo(Grafo* grafo){
    printf("profundidad grafo: %d \n", grafo->profundidad);
    printf("total vertices: %d \n", grafo->cantidadVertices);
    for (int i = 0; i < grafo->cantidadVertices; i++){
        if (grafo->vertices[i].padres == NULL){
            printf("raiz: %s ", grafo->vertices[i].idProceso);
            printf("| profundidad: %d ", grafo->vertices[i].profundidad);
            if(grafo->vertices[i].genes != NULL){
                printGenes(grafo->vertices[i].genes);
            }
            printf("%c", '\n');
        }else{
            printf("%s ", grafo->vertices[i].idProceso);
            printf("| profundidad: %d ", grafo->vertices[i].profundidad);
            if(grafo->vertices[i].genes != NULL){
                printGenes(grafo->vertices[i].genes);
            }
            printf("| padres: ");
            printPadres(grafo->vertices[i].padres, grafo->vertices, grafo->cantidadVertices);
            printf("%c", '\n');
        }
    }
}

Grafo* cargarGrafo(FILE *archivo){
    int size;
    char idProceso[5];
    char chr;
    fscanf(archivo,"%d",&size);
    Grafo* grafo = crearGrafo(size);
    int palabraCount = 0;

    for (int i = 0; i < size; i++){
        while(fscanf(archivo, "%s%c", idProceso, &chr) != EOF){
            if(palabraCount == 0){
                //Es un nuevo vértice
                ProcesoBio newProceso = crearProcesoBio(idProceso, -1);
                grafo->vertices[i] = newProceso;
                palabraCount++;
            }else if(palabraCount == 1){
                //Primer padre del vértice
                int indicePadre = obtenerIndiceProcesoBio(idProceso, grafo->vertices, i+1);
                if (indicePadre != -1){
                    grafo->vertices[i].padres = crearListaIndex(indicePadre);
                    grafo->vertices[i].profundidad = grafo->vertices[indicePadre].profundidad + 1;
                }else{
                    printf("No se encontro proceso %s para ser padre de proceso %s", idProceso, grafo->vertices[i].idProceso);
                }

                palabraCount++;
                if(grafo->profundidad < grafo->vertices[i].profundidad){
                    grafo->profundidad = grafo->vertices[i].profundidad;
                }
            }else{
                //Más padres
                int indicePadre = obtenerIndiceProcesoBio(idProceso, grafo->vertices, i+1);
                if (indicePadre != -1){
                    grafo->vertices[i].padres = insertarListaIndex(indicePadre, grafo->vertices[i].padres);
                }else{
                    printf("No se encontro proceso %s para ser padre de proceso %s", idProceso, grafo->vertices[i].idProceso);
                }
            }

            if(chr == '\n'){
                if(palabraCount == 1){
                    //vertice es raiz
                    grafo->vertices[i].profundidad = 0;
                    grafo->profundidad = 0;
                }
                palabraCount = 0;
                break;
            }
        }
    }

    return grafo;
}

// Función para cargar genes en grafo
Grafo* cargarGenes(FILE *archivo, Grafo* grafo){
    int size;
    char id[5];
    char chr;
    int palabraCount = 0;;
    fscanf(archivo,"%d",&size);
    // printf("cantidad genes: %d", size);
    // Gen* genes = crearArregloGenes(size);

    for (int i = 0; i < size; i++){
        while(fscanf(archivo, "%s%c", id, &chr) != EOF){
            if(palabraCount == 0){
                //Es un nuevo gen
                palabraCount++;
                continue;
            }else if(palabraCount >= 1){
                //Proceso al que pertenece el gen
                int indiceProceso = obtenerIndiceProcesoBio(id, grafo->vertices, grafo->cantidadVertices);
                if(indiceProceso != -1){
                    if(grafo->vertices[indiceProceso].genes == NULL){
                        grafo->vertices[indiceProceso].genes = crearListaGen(i+1);
                    }else{
                        grafo->vertices[indiceProceso].genes = insertarListaGen(i+1, grafo->vertices[indiceProceso].genes);    
                    }
                }else{
                    printf("No se encontro proceso %s para relacionar con gen G%d", id, i+1);
                }
                palabraCount++;
            }

            if(chr == '\n'){
                palabraCount = 0;
                break;
            }
        }
    }

    return grafo;

}

ListaIndex* obtenerProcesosGen(Grafo grafo, int idGen){
    ListaIndex* listaIndices = NULL;
    int encontrados = 0;

    for (int i = 0; i < grafo.cantidadVertices; i++){
        while(grafo.vertices[i].genes != NULL){
            if(grafo.vertices[i].genes->idGen == idGen){
                if(encontrados == 0){
                    listaIndices = crearListaIndex(i);
                }else{
                    listaIndices = insertarListaIndex(i, listaIndices);
                }
            }

            grafo.vertices[i].genes = grafo.vertices[i].genes->next;
        }
    }

    return listaIndices;
}


ProcesoBio encontrarAncenstroComun(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){
    
}

double calcularWuPalmer(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){

}

double calcularLeacockChorodow(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){

}

double calcularSimilitudLeacockChorodow(int idGen1, int idGen2, Grafo grafo){
    double resultado = -1;
    ListaIndex* procesosGen1 = obtenerProcesosGen(grafo, idGen1);
    ListaIndex* procesosGen2 = obtenerProcesosGen(grafo, idGen2);

    if (!(procesosGen1 != NULL && procesosGen2 != NULL)){
        return resultado;
    }

    while(procesosGen1 != NULL){
        ListaIndex* procesosGen2Cpy = procesosGen2;
        while (procesosGen2Cpy != NULL){
            resultado += calcularWuPalmer(grafo.vertices[procesosGen1->index], grafo.vertices[procesosGen2->index], grafo);
        }
        
    }
    
    return resultado;
}

double calcularSimilitudWuPalmer(int idGen1, int idGen2, Grafo grafo){
    double resultado = -1;
    ListaIndex* procesosGen1 = obtenerProcesosGen(grafo, idGen1);
    ListaIndex* procesosGen2 = obtenerProcesosGen(grafo, idGen2);

    if (!(procesosGen1 != NULL && procesosGen2 != NULL)){
        return resultado;
    }

    while(procesosGen1 != NULL){
        ListaIndex* procesosGen2Cpy = procesosGen2;
        while (procesosGen2Cpy != NULL){
            resultado += calcularLeacockChorodow(grafo.vertices[procesosGen1->index], grafo.vertices[procesosGen2->index], grafo);
        }
        
    }
    
    return resultado;
}

FILE* cargarArchivo(char* path){
    FILE* archivo = fopen(path,"r");

    if(archivo == NULL){
        printf("ERROR: El archivo %s no se pudo abrir, escriba el nombre correctamente con su extension.", path);
        return NULL;
    }

    return archivo;
}

int calcularSimilitudGenes(){
    FILE* archivoProcesos = cargarArchivo("input/procesos.in");
    FILE* archivoGenes = cargarArchivo("input/genes.in");
    
    if(archivoProcesos == NULL || archivoGenes == NULL){
        return 1;
    }

    Grafo* grafo = cargarGrafo(archivoProcesos);
    fclose(archivoProcesos);
    grafo = cargarGenes(archivoGenes, grafo);
    fclose(archivoGenes);
    printGrafo(grafo);

    int gen1;
    int gen2;
    double similitudWP;
    double similitudLC;
    char* confirmacion; 
    do{
        printf("Ingrese primer gen: ");
        scanf("%d", &gen1);
        printf("\nIngrese segundo gen: ");
        scanf("%d", &gen2);
        
        similitudWP = calcularSimilitudWuPalmer(gen1, gen2, *grafo);
        similitudLC = calcularSimilitudLeacockChorodow(gen1, gen2, *grafo);
        
        printf("\nSimilitud de genes Wu-Palmer: %lf", similitudWP);
        printf("\nSimilitud de genes Leacok-Chorodow: %lf", similitudLC);
        printf("\n¿Desea ingresar otro par de genes?: ");
        scanf("%s", confirmacion);

    } while (strcmp(confirmacion, "No") != 0);

    freeGrafo(grafo);

    return 0;
}

int main(){
    return calcularSimilitudGenes();
}