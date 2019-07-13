#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


//***DEFINICIÓN ESTRUCTURAS***

typedef struct ListaIndex{
    int index;
    int largo;
    struct ListaIndex* next;
}ListaIndex;

typedef struct Gen{
    int idGen;
    struct Gen* next;
}Gen;

typedef struct{
    char idProceso[5];
    int distanciaRaiz;
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
    new->largo = 1;
    new->next = NULL;
    return new;
}

// agrega al principio
ListaIndex* apilarListaIndex(int newIndex, ListaIndex* lista){
    ListaIndex* new = crearListaIndex(newIndex);

    if(lista == NULL){
        return new;
    }

    new->largo = lista->largo + 1;
    new->next = lista;
    
    return new;
}

//agrega al final
ListaIndex* encolarListaIndex(int newIndex, ListaIndex* lista){
    ListaIndex* new = crearListaIndex(newIndex);

    if(lista == NULL){
        return new;
    }

    lista->largo = lista->largo + 1;

    while(lista->next != NULL){
        lista = lista->next;
        lista->largo = lista->largo + 1;
    }

    lista->next = new;
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

bool* crearArregloBool(int size){
    bool* arreglo = (bool*)malloc(sizeof(bool) * size);
    if (arreglo != NULL){
        for (int i = 0; i < size; i++){
            arreglo[i] = false;
        }
        
        return arreglo;
    }else{
        printf("ERROR: No se encontro suficiente memoria para crear arreglo de bool\n");
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


//***OPERACIONES PARA MUESTRA DE DATOS***

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
    printf("\nprofundidad grafo: %d \n", grafo->profundidad);
    printf("total vertices: %d \n", grafo->cantidadVertices);
    for (int i = 0; i < grafo->cantidadVertices; i++){
        if (grafo->vertices[i].padres == NULL){
            printf("raiz: %s ", grafo->vertices[i].idProceso);
            printf("| indice: %d ", i);
            printf("| profundidad: %d ", grafo->vertices[i].distanciaRaiz);
            printf("| indice: %d ", i);
            if(grafo->vertices[i].genes != NULL){
                printGenes(grafo->vertices[i].genes);
            }
            printf("%c", '\n');
        }else{
            printf("%s ", grafo->vertices[i].idProceso);
            printf("| indice: %d ", i);
            printf("| profundidad: %d ", grafo->vertices[i].distanciaRaiz);
            if(grafo->vertices[i].genes != NULL){
                printGenes(grafo->vertices[i].genes);
            }
            printf("| padres: ");
            printPadres(grafo->vertices[i].padres, grafo->vertices, grafo->cantidadVertices);
            printf("%c", '\n');
        }
    }
}



//***FUNCIONALIDADES DEL PROGRAMA***

/*
Obtiene indice de ProcesoBio en arreglo principal de grafo
Entradas: char*, ProcesoBio*, int
Salidas: int
 */
int obtenerIndiceProcesoBio(char* identificador, ProcesoBio* vertices, int size){
    for (int i = 0; i < size; i++){
        if (strcmp(vertices[i].idProceso, identificador) == 0){
            return i;
        }
    }

    printf("Proceso %s no encontrado", identificador);
    return -1;
}

/*
Obtiene los vértices en los que se encuentra presente un gen
Entradas: Grafo, int
Salidas: ListaIndex*
 */
ListaIndex* obtenerProcesosGen(Grafo grafo, int idGen){
    ListaIndex* listaIndices = NULL;

    for (int i = 0; i < grafo.cantidadVertices; i++){
        if(grafo.vertices[i].genes == NULL){
            continue;
        }

        Gen genesCopy = *grafo.vertices[i].genes;
        Gen* punteroCopy = &genesCopy;
        while(punteroCopy != NULL){
            if(punteroCopy->idGen == idGen){
                listaIndices = apilarListaIndex(i, listaIndices);
            }
            punteroCopy = punteroCopy->next;
        }
    }

    return listaIndices;
}

/*
Carga grafo desde archivo dado
Entradas: FILE*
Salidas: Grafo*
 */
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
                    grafo->vertices[i].distanciaRaiz = grafo->vertices[indicePadre].distanciaRaiz + 1;
                }else{
                    printf("No se encontro proceso %s para ser padre de proceso %s", idProceso, grafo->vertices[i].idProceso);
                }

                palabraCount++;
                if(grafo->profundidad < grafo->vertices[i].distanciaRaiz + 1){
                    grafo->profundidad = grafo->vertices[i].distanciaRaiz + 1;
                }
            }else{
                //Más padres
                int indicePadre = obtenerIndiceProcesoBio(idProceso, grafo->vertices, i+1);
                if (indicePadre != -1){
                    grafo->vertices[i].padres = apilarListaIndex(indicePadre, grafo->vertices[i].padres);
                }else{
                    printf("No se encontro proceso %s para ser padre de proceso %s", idProceso, grafo->vertices[i].idProceso);
                }
            }

            if(chr == '\n'){
                if(palabraCount == 1){
                    //vertice es raiz
                    grafo->vertices[i].distanciaRaiz = 0;
                    grafo->profundidad = 0;
                }
                palabraCount = 0;
                break;
            }
        }
    }

    return grafo;
}

/* 
Carga genes desde archivo
Entradas: FILE*, Grafo*
Salidas: Grafo*
*/
Grafo* cargarGenes(FILE *archivo, Grafo* grafo){
    int size;
    char id[5];
    char chr;
    int palabraCount = 0;;
    fscanf(archivo,"%d",&size);

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

/* 
Obtiene los ancestros de un vértice dado, recorrido por anchura.
Entradas: char[5], Grafo
Salidas: bool*
*/
bool* obtenerAncestros(char idProceso[5], Grafo grafo){
    int indice = -1;
    bool* indicesVisitados = crearArregloBool(grafo.cantidadVertices);
    ListaIndex* colaVisitados = NULL;

    indice = obtenerIndiceProcesoBio(idProceso, grafo.vertices, grafo.cantidadVertices);
    colaVisitados = crearListaIndex(indice);
    indicesVisitados[indice] = true;
    
    while(colaVisitados != NULL){
        ListaIndex* conjutoAdyacencia = grafo.vertices[colaVisitados->index].padres;
        colaVisitados = colaVisitados->next;
        while(conjutoAdyacencia != NULL){
            if(indicesVisitados[conjutoAdyacencia->index] != true){
                indicesVisitados[conjutoAdyacencia->index] = true;
                colaVisitados = encolarListaIndex(conjutoAdyacencia->index, colaVisitados);
            }
        conjutoAdyacencia = conjutoAdyacencia->next;
        }

    }

    freeListaIndex(colaVisitados);

    return indicesVisitados;
}

/* 
Encuentra el ancestro común mas cercano
Entradas: ProcesoBio, ProcesoBio, Grafo
Salidas: ProcesoBio*
*/
ProcesoBio* encontrarAncenstroComunCercano(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){
    bool* ancestrosVertice1 = obtenerAncestros(vertice1.idProceso, grafo);
    bool* ancestrosVertice2 = obtenerAncestros(vertice2.idProceso, grafo);
    ListaIndex* ancestrosComunes = NULL;
    int indiceAMC = -1;
    int distanciaAMC = -1;

    for (int i = 0; i < grafo.cantidadVertices; i++){
        if((ancestrosVertice1[i] == true) && (ancestrosVertice2[i] == true)){
            //Como mínimo debería contener la raíz
            ancestrosComunes = apilarListaIndex(i, ancestrosComunes);
        }
    }

    free(ancestrosVertice1);
    free(ancestrosVertice2);

    ListaIndex* copyAncestrosComunes = ancestrosComunes;
    while (copyAncestrosComunes != NULL){
        if(grafo.vertices[copyAncestrosComunes->index].distanciaRaiz > distanciaAMC){
            indiceAMC = copyAncestrosComunes->index;
            distanciaAMC = grafo.vertices[copyAncestrosComunes->index].distanciaRaiz;
        }
        copyAncestrosComunes = copyAncestrosComunes->next;
    }

    freeListaIndex(ancestrosComunes);

    return &grafo.vertices[indiceAMC]; 
}

/* 
Calcula similitud para 2 vertices por LeacockChorodow
Entradas: ProcesoBio, ProcesoBio, Grafo
Salidas: double
*/
double calcularLeacockChorodow(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){
    ProcesoBio* ancestroComunMasCercano = encontrarAncenstroComunCercano(vertice1, vertice2, grafo);
    double distanciaAMC = 0;

    if(ancestroComunMasCercano != NULL){
        distanciaAMC = ancestroComunMasCercano->distanciaRaiz;
    }

    double D = grafo.profundidad;
    double D2 = vertice2.distanciaRaiz - distanciaAMC;
    double D1 = vertice1.distanciaRaiz - distanciaAMC;

    double result = -log10((D1 + D2 +1)/(2*D));
    
    return result;
}

/* 
Calcula similitud para 2 genes por LeacockChorodow
Entradas: int, int, Grafo
Salidas: double
*/
double calcularSimilitudLeacockChorodow(int idGen1, int idGen2, Grafo grafo){
    int cantidad_procesos_gen1 = 0;
    int cantidad_procesos_gen2 = 0;
    int total_pares_procesos = 1;
    double resultado = 0;


    ListaIndex* procesosGen1 = obtenerProcesosGen(grafo, idGen1);
    ListaIndex* procesosGen2 = obtenerProcesosGen(grafo, idGen2);

    if (procesosGen1 == NULL || procesosGen2 == NULL){
        return resultado;
    }

    cantidad_procesos_gen1 = procesosGen1->largo;
    cantidad_procesos_gen2 = procesosGen2->largo;
    total_pares_procesos = cantidad_procesos_gen1 * cantidad_procesos_gen2;

    while(procesosGen1 != NULL){
        ListaIndex* procesosGen2Copy = procesosGen2;
        while (procesosGen2Copy != NULL){
            resultado += calcularLeacockChorodow(grafo.vertices[procesosGen1->index], grafo.vertices[procesosGen2Copy->index], grafo);
            procesosGen2Copy = procesosGen2Copy->next;
        }
        procesosGen1 = procesosGen1->next;     
    }

    freeListaIndex(procesosGen1);
    freeListaIndex(procesosGen2);    

    resultado /= total_pares_procesos;

    return resultado;
}

/* 
Calcula similitud para 2 vertices por WuPalmer
Entradas: ProcesoBio, ProcesoBio, Grafo
Salidas: double
*/
double calcularWuPalmer(ProcesoBio vertice1, ProcesoBio vertice2, Grafo grafo){
    ProcesoBio* ancestroComunMasCercano = encontrarAncenstroComunCercano(vertice1, vertice2, grafo);

    if(ancestroComunMasCercano == NULL){
        return 0;
    }

    double D3 = ancestroComunMasCercano->distanciaRaiz;
    double D2 = vertice2.distanciaRaiz - D3;
    double D1 = vertice1.distanciaRaiz - D3;
    
    return (2*D3)/(D1 + D2 + (2*D3));
}


/* 
Calcula similitud para 2 genes por WuPalmer
Entradas: int, int, Grafo
Salidas: double
*/
double calcularSimilitudWuPalmer(int idGen1, int idGen2, Grafo grafo){
    int cantidad_procesos_gen1 = 0;
    int cantidad_procesos_gen2 = 0;
    int total_pares_procesos = 1;
    double resultado = 0;

    ListaIndex* procesosGen1 = obtenerProcesosGen(grafo, idGen1);
    ListaIndex* procesosGen2 = obtenerProcesosGen(grafo, idGen2);

    if (procesosGen1 == NULL || procesosGen2 == NULL){
        return resultado;
    }

    cantidad_procesos_gen1 = procesosGen1->largo;
    cantidad_procesos_gen2 = procesosGen2->largo;
    total_pares_procesos = cantidad_procesos_gen1 * cantidad_procesos_gen2;

    while(procesosGen1 != NULL){
        ListaIndex* procesosGen2Copy = procesosGen2;
        while (procesosGen2Copy != NULL){
            resultado += calcularWuPalmer(grafo.vertices[procesosGen1->index], grafo.vertices[procesosGen2Copy->index], grafo);
            procesosGen2Copy = procesosGen2Copy->next;
        }
        procesosGen1 = procesosGen1->next;
    }

    freeListaIndex(procesosGen1);
    freeListaIndex(procesosGen2);

    resultado /= total_pares_procesos;

    return resultado;
}

/* 
Función genérica para abrir archivos
Entradas: char*
Salidas: FILE*
*/
FILE* cargarArchivo(char* path){
    FILE* archivo = fopen(path,"r");

    if(archivo == NULL){
        printf("ERROR: El archivo %s no se pudo abrir, escriba el nombre correctamente con su extension.", path);
        return NULL;
    }

    return archivo;
}

/* 
Cuerpo principal, calcula similitud entre 2 genes dados por consola
Entradas: No aplica
Salidas: int
*/
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
    //descomentar si se desea verificar estructura generada
    // printGrafo(grafo);

    int gen1;
    int gen2;
    double similitudWP;
    double similitudLC;
    char confirmacion[2];
    int continuar = 1;
    while(continuar != 0){
        printf("Ingrese primer gen: ");
        if(scanf("%d", &gen1) != 1){
            printf("\nDebe indicar el gen con un numero entero\n");
            break;
        }
        printf("Ingrese segundo gen: ");
        if(scanf("%d", &gen2) != 1){
            printf("\nDebe indicar el gen con un numero entero\n");
            break;
        }
        
        similitudWP = calcularSimilitudWuPalmer(gen1, gen2, *grafo);
        similitudLC = calcularSimilitudLeacockChorodow(gen1, gen2, *grafo);
        
        printf("Similitud de genes Wu-Palmer: %lf", similitudWP);
        printf("\nSimilitud de genes Leacok-Chorodow: %lf", similitudLC);
        printf("\n¿Desea ingresar otro par de genes?: ");
        scanf("%s", confirmacion);
        continuar = strcmp(confirmacion, "No");
        printf("\n");
    }

    freeGrafo(grafo);

    return 0;
}


int main(){
    return calcularSimilitudGenes();
}