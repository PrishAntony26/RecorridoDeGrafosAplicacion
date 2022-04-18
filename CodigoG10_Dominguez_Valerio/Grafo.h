/*
 * nomProgram: Grafo.h
 * descripcion:
 *     Implementacion de las operaciones basicas del grafo dirigido
 *     y no dirigido: crear, insertar, editar, eliminar, mostrar
 *     - Operaciones de salvar y recuperar (serialización).
 *     - Recorridos de profundidad y anchura.
 *     - Algoritmos de Dijktra, Prim y Kruskal.
 *
 * INTEGRANTES:
 *	DOMINGUEZ ACOSTA, Prish Antony
 *	GUTIERREZ CARUAJULCA, Javier Antonio
 *	MALCA RAMIREZ, Jhonattan David
 *	VALERIO GAMBOA, Pedro Luis
 *
 * fecha: 26/08/2021
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <queue>
#include <stack>
#include <iomanip>

#include "Arista.h"

#define maxWT 1
using namespace std;

class Grafo
{

private:
    int numVertices;
    int elementos;
    float **matriz;
    bool dirigido;//Comprobar si el grafo a construir es dirigido o no

    //Para trayectoria
    int *visited;
    int **visitedDirigido;//Trayectoria grafo dirigido
    //Para recorrido en profundidad
    int *pre;
    float *pesos;
    int contador;
    //Para almacenar los padres
    int *padre;
    int **padreRecorrido;//Trayectoria grafo dirigido
    //Para recorrido en extension
    queue<Arista> cola;
    //Para Dijkstra
    int *DistaMenosDe;
    float *pesosDijstra;
    //Para Prim
    float *pesosPrim;
    //Para Kruskal
    int *foresta;
    Arista *mst;
    int cntf;
    int *id,*sz;

public:
    Grafo();
    Grafo(int numeroVertices, bool dirigido);
    //~Grafo();
    float **crearMatriz(int vertice,float peso);
    void ingresarElemento(Arista arist);
    void eliminarElemento(Arista arist);
    void mostrarListaVertices();
    void mostrarMatrizIncidencias();
    int numElementos(Arista a[]);
    void editarPesoGrafo(Arista arist);
    int trayectoria(int vIni,int vFin);//Funcion recursiva
    int mostrarTrayectoria(int vIni,int vFin);
    void BusquedaEnProfundidadDirigido(Arista arist);//Funcion recursiva
    void BusquedaEnProfundidadNODirigido(Arista arist);
    void BusquedaEnProfundidadNODirigidoDetalle(Arista arist);
    void BusquedaProfundidadPila(Arista e);
    void MostrarBusquedaProfundidad();
    void EjecucionBusquedaEnProfundidad();//Efectua la busqueda en profundidad
    void salvarGrafo(char nombre[]);//Salvar aristas
    void recuperarGrafo(char nombre[]);
    void BusquedaEnExtension(Arista arist);
    void MostrarBusquedaEnExtension();

    //RECUPERAR Y SALVAR GRAFO
    Grafo GrafoRecuperar(char nombreFile[],bool dirigido);
    //ALGORITMO PRIM
    void Prim(int raiz);
    void MostrarPrim(int raiz);

    //ALGORITMO KRUSKAL
    void MostrarKruskalP(Arista *arist);
    void UneSubArboles(int p, int q);
    int NoPertenece(int p, int q);
    void MostrarKruskal(Arista *arist);
    void qsortnw(Arista *arist, int l, int r);
    void GRAPHmstKruskal(Arista *arist);
    void UFinit(int n);
    int Find(int x);
    int UFfind(int p,int q);
    void UFunion(int p,int q);
    void UFdestroy(void);
    int UFfind1(int p,int q);
    void UFunion1(int p,int q, int n);

    void Dijkstra(int raiz);
    void MostrarDijkstra(int raiz);

    friend ostream& operator << (ostream& os, Grafo& m);

    //getter
    int getnumVertices()
    {
        return this->numVertices;
    }
    int getelementos()
    {
        return this->elementos;
    }
    //setter
    void setnumVertices(int numVertices)
    {
        this->numVertices = numVertices;
    }
    void setelementos(int elementos)
    {
        this->elementos = elementos;
    }
    void setcontador(int contador)
    {
        this->contador = contador;
    }
/*
private:
    int numVertices;
    int elementos;
    float **matriz;
    bool dirigido;//Comprobar si el grafo a construir es dirigido o no

    //Para trayectoria
    int *visited;
    int **visitedDirigido;//Trayectoria grafo dirigido
    //Para recorrido en profundidad
    int *pre;
    float *pesos;
    int contador;
    //Para almacenar los padres
    int *padre;
    int **padreRecorrido;//Trayectoria grafo dirigido
    //Para recorrido en extension
    queue<Arista> cola;
    //Para Dijkstra
    int *DistaMenosDe;
    float *pesosDijstra;
    //Para Prim
    float *pesosPrim;
    //Para Kruskal
    int *foresta;
    Arista *mst;
    int cntf;
    int *id,*sz;*/
};

Grafo::Grafo(){

}

Grafo::Grafo(int numeroVertices, bool dirigido)
{
    setnumVertices(numeroVertices);
    setelementos(0);
    //Tipo de grafo
    this->dirigido = dirigido;
    //Creamos la matriz con todos los elementos auxiliares para desarrollar los metodos
    this->matriz = crearMatriz(numeroVertices,0);
    this->padre = new int[numeroVertices];
    this->visited = new int[numeroVertices];
    this->pre = new int[numeroVertices];
    this->pesos = new float[numeroVertices];
    this->DistaMenosDe = new int[numeroVertices];
    this->pesosDijstra = new float[numeroVertices+1];
    this->foresta = new int[numeroVertices];
    this->mst = new Arista[numeroVertices-1];
    this->pesosPrim = new float[numeroVertices];
}

float** Grafo::crearMatriz(int vertice,float peso)
{
    int i=0,j=0;
    float **t = new float*[vertice];
    for(i = 0; i<vertice; i++)
    {
        t[i] = new float[vertice];
    }
    for(i=0; i<vertice; i++)
    {
        for(j=0; j<vertice; j++)
        {

                t[i][j] = peso;//Cuando no exista arista se marcara 1 (MAXWT)

        }
    }
    return t;
}

/*********************************TO STRING************************************************************/
ostream& operator << (ostream& os, Grafo& m)
{
    os<<" MOSTRANDO DATOS DEL GRAFO....."<<endl;
    os<<" Vertices: "<<m.getnumVertices()<<" Aristas: "<<m.getelementos()<<endl;
    return os;
}

/*****************************INSERCION DE ELEMENTO**********************************************/

void Grafo::ingresarElemento(Arista arist)
{
    if(this->matriz[arist.getvInicial()][arist.getvFinal()]==0)
    {
        this->elementos++;
        this->matriz[arist.getvInicial()][arist.getvFinal()] = arist.getpeso();//Cuando es dirigido
        if(!this->dirigido) //Si no es dirigido
        {
        this->matriz[arist.getvFinal()][arist.getvInicial()] = arist.getpeso();
        }
    }
}

/***************************ELIMINACION DE ELEMENTO**********************************************/

void Grafo::eliminarElemento(Arista arist)
{
    printf("\n\tDatos de eliminacion: ");
    printf("\n\tVertice inicial  %d Vertice Final %d Peso %.2f",arist.getvInicial(),arist.getvFinal(),
           this->matriz[arist.getvInicial()][arist.getvFinal()]);
    if(this->matriz[arist.getvInicial()][arist.getvFinal()]!=0)
    {
        this->elementos--;
    }
    this->matriz[arist.getvInicial()][arist.getvFinal()] = 0;//Cuando es dirigido
    if(!this->dirigido) //Si no es dirigido
    {
        this->matriz[arist.getvFinal()][arist.getvInicial()] = 0;
    }
    printf("\n\tEliminacion completada ");
}

/***************************** EDITAR PESO DE UNA ARISTA ***********************************************/
void Grafo::editarPesoGrafo(Arista arist)
{
    if(this->matriz[arist.getvInicial()][arist.getvFinal()]!=0)
    {
        printf("\n\tDatos de cambio: ");
        printf("\n\tVertice inicial  %d Vertice Final %d Peso antiguo %.2f",arist.getvInicial(),arist.getvFinal(),
               this->matriz[arist.getvInicial()][arist.getvFinal()]);
        printf("\n\tNuevo peso: %.2f",arist.getpeso());
        this->matriz[arist.getvInicial()][arist.getvFinal()] = arist.getpeso();
        if(!this->dirigido)
        {
            this->matriz[arist.getvFinal()][arist.getvInicial()] = arist.getpeso();
        }
    }
    else
    {
        printf("La arista no pertence al grafo....");
    }
}


/*************************** TABLA DE INCIDENCIAS ****************************************************/

void Grafo::mostrarListaVertices()
{
    int i,j;
    for(i=0; i<getnumVertices(); i++)
    {
        cout<<i<<" :";
        for(j=0; j<getnumVertices(); j++)
        {
            if(!this->dirigido)
            {
                //Cuando el grafo es no dirigido
                if(this->matriz[i][j]!=0) //Comprobamos que entre las arista exista una red
                {
                    cout<<this->matriz[i][j]<<"  ";
                }
            }
            else
            {
                //Cuando el grafo es dirigido
                if(this->matriz[i][j] != 0)
                {
                    cout<<j<<" - "<<this->matriz[i][j]<<" ";
                }
            }
        }
        cout<<endl;
    }
}

/******************************** MATRIZ DE ADYACENCIA ***************************************************/
//CAMBIAR NOMBRE AL METODO OJO!!!!
void Grafo::mostrarMatrizIncidencias()
{
    int i,j;
    cout<<"Vertices: "<<getnumVertices()<<" Aristas: "<<getelementos()<<endl;
    printf("    ");
    for(j=0; j<getnumVertices(); j++)
    {
        printf("%4d ", j);
    }
    //cout<<endl;
    putchar('\n');
    for(i=0; i<getnumVertices(); i++)
    {
        printf("%2d:", i);
        for(j=0; j<getnumVertices(); j++)
        {
            if(this->matriz[i][j]!=0)
            {
                printf(" %0.2f", this->matriz[i][j]);
            }
            else
            {
                printf("  *  ");
            }
        }
        //cout<<endl;
        putchar('\n');
    }
}

/*************** GENERACION DE ELEMENTOS A PARTIR DE MATRIZ DE INCIDENCIAS****************************/

int Grafo::numElementos(Arista a[])//Se crea un arreglo de aristas a partir de G
{
    int v,w,E=0;
    for(v=0; v<getnumVertices(); v++)
    {
        if(this->dirigido)
        {
            for(w=0; w<getnumVertices(); w++)
            {
                if(this->matriz[v][w]!=0)
                {
                    a[E++] = Arista(v,w,this->matriz[v][w]);
                }
            }
        }
        else
        {
            //Si no es dirigido
            for(w=v+1; w<getnumVertices(); w++)
            {
                if(this->matriz[v][w]!=0)
                {
                    float num = this->matriz[v][w];
                    a[E++] = Arista(v,w,this->matriz[v][w]);
                }
            }
        }
    }
    return E;//Devuelve el tamaño del arreglo Arista a[]
}


/***************************** TRAYECTORIA DE UN GRAFO ********************************/
int Grafo::trayectoria(int vIni,int vFin)
{
    int t,j;
    if(vIni==vFin)
    {
        return 1;
    }
    this->visited[vIni] = 1;//Marcamos que el vertice Ini ya ha sido visitado
    for(t=0; t<getnumVertices(); t++)
    {
        if(this->matriz[vIni][t]!=0) //Si existe un vertice entre vIni con t
        {
            if(this->visited[t]==0||this->padreRecorrido[vIni][t]!=1) //Si el vertice t aun no ha sido visitado
            {
                this->padreRecorrido[vIni][t] = 1;//En las filas se almacena el hijo y
                //en la columna el padre vIni = 5 t = 1
                cout<<vIni<<"-"<<t<<" ";
                if(trayectoria(t,vFin)==1) //Tambien puede ser if(trayectoria(t,vFin), no es necesario el ==1
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Grafo::mostrarTrayectoria(int vIni,int vFin)
{
    int t,j;
    for(t=0; t<getnumVertices(); t++)
    {
        this->visited[t] =0;//Inicializa todos los espacios del vector visited a 0
    }
    this->padreRecorrido = new int*[getnumVertices()];
    for(j=0; j<getnumVertices(); j++)
    {
        this->padreRecorrido[j] = new int[getnumVertices()];
    }
    for(t=0; t<getnumVertices(); t++)
    {
        for(j=0; j<getnumVertices(); j++)
        {
            this->padreRecorrido[t][j] = 0;
        }
    }
    return trayectoria(vIni,vFin);//LLamada a la funcion trayectoria
}

/************************** BUSQUEDA EN PROFUNDIDAD DFS*********************************/
void Grafo::BusquedaEnProfundidadDirigido(Arista arist)
{
    int j,t, w = arist.getvFinal();
    this->pre[w] = this->contador++;//Marcar contador creciente
    this->padre[w] = arist.getvInicial();
    float aux = this->pesos[arist.getvInicial()];
    float aux2 = this->matriz[arist.getvInicial()][arist.getvFinal()];
    this->pesos[w] = aux + aux2;
    for(t=0; t<getnumVertices(); t++)
    {
        if(this->matriz[w][t]!=0) //Si no existe conexion entre w y t
        {
            if(pre[t]==-1) //NOVISITADO
            {
                Arista aux(w,t,0);
                BusquedaEnProfundidadDirigido(aux);
                printf(" %d-%d",w,t);
            }
        }
    }
}

void Grafo::BusquedaEnProfundidadNODirigidoDetalle(Arista arist)
{
    static int indente = 0;
    int j,t, w = arist.getvFinal();
    this->pre[w] = this->contador++;//Marcar contador creciente
    this->padre[arist.getvFinal()] = arist.getvInicial();
    for(t=0; t<getnumVertices(); t++)
    {
        if(this->matriz[w][t]!=0) //Si no existe conexion entre w y t
        {
            for(j=0; j<indente; j++)
            {
                cout<<" ";
            }
            cout<<w<<"-"<<t<<endl;
            if(this->pre[t]==-1)
            {
                indente++;
                putchar('*');
                Arista aux(w,t,this->matriz[w][t]);//Construimos un nuevo objeto arista vInicial: w vFinal: t
                BusquedaEnProfundidadNODirigido(aux);//Recursividad
                indente--;
            }
            else
                putchar(' ');
        }
    }
}

void Grafo::BusquedaEnProfundidadNODirigido(Arista arist)
{
    int j,t, w = arist.getvFinal();
    this->pre[w] = this->contador++;//Marcar contador creciente
    this->padre[arist.getvFinal()] = arist.getvInicial();
    this->pesos[w] = this->matriz[arist.getvFinal()][arist.getvInicial()];
    for(t=0; t<getnumVertices(); t++)
    {
        if(this->matriz[w][t]!=0) //Si no existe conexion entre w y t
        {
            if(this->pre[t]==-1)
            {
                Arista aux(w,t,this->matriz[w][t]);//Construimos un nuevo objeto arista vInicial: w vFinal: t
                BusquedaEnProfundidadNODirigido(aux);//Recursividad
                printf(" %d-%d ",arist.getvFinal(),t);
            }
        }
    }
}


void Grafo::MostrarBusquedaProfundidad()
{
    int i;
    printf("\n\t Tabla Busqueda Profundidad\n");
    for(i=0;i<getnumVertices();i++)
    {
        printf("    %d",i);
    }
    printf("    Vertice\n");
    for(i=0;i<getnumVertices();i++)
    {
        printf("    %d",this->padre[i]);
    }
    printf("    Padre de vertice\n");
    for(i=0;i<getnumVertices();i++)
    {
        printf(" %.2f",this->pesos[i]);
    }
    printf("    Peso del elemento entre vertice y su padre\n");
}

void Grafo::BusquedaProfundidadPila(Arista e)//DFT
{
   printf("\n");
   int t, v, w, f,cnt=0;
   stack<int> s;
   s.push(e.getvInicial());
   s.push(e.getvFinal()); //empuja los vértices del elemento
   printf(" [%d]",e.getvInicial());
   while(!s.empty()){
      w=s.top();
      s.pop();
      v=s.top();
      s.pop();
      s.push(v);
      f=1; //guarda ruta en el árbol
      this->pre[w] = cnt++;
      this->padre[w] = v; // se guarda el vértice padre de w.
      while(f){
         for (t = 0; t < this->getnumVertices(); t++){
            if (this->matriz[w][t] != 0){
               if (pre[t] == -1){
                  s.push(w);
                  s.push(t);
                  printf(" [%d]", t);
                  f=0;
                  break;
               }
            }
         }
         if (f){ //llegó al final de un recorrido en el árbol.
            if (!s.empty()){
               w=s.top();
               s.pop(); //extrae vértice anterior del árbol
            }
            else{
               f=0;
            }
         }
      }
   }
}

void Grafo::EjecucionBusquedaEnProfundidad()
{
    int v;
    this->contador=0;
    for(v=0; v<getnumVertices(); v++)
    {
        this->pre[v] = -1;
        this->padre[v] = -1;
        this->pesos[v] = 0;
    }
    for(v=0; v<getnumVertices(); v++)
    {
        if(this->pre[v]==-1) //NOVISITADO
        {
            Arista aux(v,v,0);
                BusquedaProfundidadPila(aux);
        }
    }
    for(v=0; v<getnumVertices(); v++)
    {
        this->pre[v] = -1;
        this->padre[v] = -1;
        this->pesos[v] = 0;
    }
    printf("\n");
    for(v=0; v<getnumVertices(); v++)
    {
        if(this->pre[v]==-1) //NOVISITADO
        {
            Arista aux(v,v,0);
            if(this->dirigido)
            {
                //BusquedaEnProfundidadDirigido(aux);
                BusquedaEnProfundidadDirigido(aux);
            }
            else
            {
                BusquedaEnProfundidadNODirigido(aux);
            }
        }
    }
    MostrarBusquedaProfundidad();
}

/**************************** RECORRIDO POR ANCHURA ***********************************************/
void Grafo::BusquedaEnExtension(Arista arist)//BFT
{
    int v;
    cola.push(arist);
    while(!cola.empty())
    {
        //Almacenamos el primer elemento de la cola
        Arista aux = cola.front();
        //Decolamos
        cola.pop();
        if(pre[aux.getvFinal()]==-1)
        {
            printf(" [%d] ",aux.getvFinal());
            pre[aux.getvFinal()] = this->contador++;
            padre[aux.getvFinal()] = aux.getvInicial();
            for(v=0; v<getnumVertices(); v++)
            {
                if(this->matriz[aux.getvFinal()][v]!=0)
                {
                    if(pre[v]==-1)
                    {
                        Arista aux2(aux.getvFinal(),v,0);
                        cola.push(aux2);
                    }
                }
            }
        }

    }
}

void Grafo::MostrarBusquedaEnExtension()
{
    int v;
    this->contador=0;
    for(v=0; v<getnumVertices(); v++)
    {
        this->pre[v] = -1;
        this->padre[v] = -1;
    }
    for(v=0; v<getnumVertices(); v++)
    {
        if(pre[v]==-1)
        {
            Arista aux(v,v,0);
            BusquedaEnExtension(aux);
        }
    }
}

/*********************************SALVAR Y RECUPERAR GRAFO ARCHIVO BINARIO*******************************/
void Grafo::salvarGrafo(char nombre[])
{
    //LEER EL ARCHIVO
    cout<<"COMENZANDO SALVADO DE ARCHIVO...."<<endl;
    FILE *F;
    //Abre el archivo F para añadir
    F = fopen(nombre,"a");
    //Consistencia exito de apertura de archivo
    if(F==NULL)
    {
        cout<<"NO SE PUDO CREAR ARCHIVO "<<endl;
        exit(1);
    }
    if(getelementos()==0)
    {
        cout<<"No se puede realizar la accion, no existe ninguna arista"<<endl;
    }
    else
    {
        //Creamos un vector con las aristas que contiene el grafo
        Arista aux[15];
        //Hallamos el total de aristas que posee el grafo y obtenemos las aristas
        int total = numElementos(aux),i=0;
        //Almacenamos las aristas
        while(i<total)
        {
            Arista b = aux[i];
            fwrite(&b,sizeof(b),1,F);
            i++;
        }
        fclose(F);
        cout<<"Se ha salvado el archivo....."<<endl;
    }
    fclose(F);
}

void Grafo::recuperarGrafo(char nombre[])
{
    cout<<"COMENZANDO RECUPERACION DE ARCHIVO...."<<endl;
    FILE *F;
    F = fopen(nombre,"r");
    if(F==NULL)
    {
        printf("No se pudo abrir el file....");
        exit(1);
    }
    Arista aux,recp[15];
    fread(&aux,sizeof(aux),1,F);
    while(!feof(F))
    {
        ingresarElemento(aux);
        fread(&aux,sizeof(aux),1,F);
    }
    fclose(F);
    cout<<"Se ha recuperado el archivo...."<<endl;
}

/******************************* RECUPERAR GRAFO ARCHIVO DE TEXTO *****************************/

Grafo Grafo::GrafoRecuperar(char nombreFile[],bool dirigido)
{
    FILE *f;
    int i=-1, vInicial, vFinal;
    float peso;
    int vertices;
    int elementos;
    int val;
    Arista aux;

    f=fopen(nombreFile, "r");//Modo lectura
    if(f==NULL){
        printf("No existe el archivo...!");
        exit(1);
    }
    fscanf(f,"%d",&vertices);
    fscanf(f,"%d",&elementos);
    Arista arist[elementos];
    while(!feof(f)){
        i++;
        fscanf(f,"%d",&vInicial);
        fscanf(f,"%d",&vFinal);
        fscanf(f,"%f",&peso);
        Arista aux(vInicial,vFinal,peso);
        arist[i]=aux;
    }
    printf("\nVertices %d , Elementos %d ",vertices,elementos);
    fclose(f);
    Grafo grafo(vertices,dirigido);
    for(int x=0; x<elementos; x++){
        grafo.ingresarElemento(arist[x]);
    }
    printf("\nGrafo recuperado.....");
    return grafo;
}

/***************************** ALGORITMO DE PRIM**********************************/

void Grafo::Prim(int raiz)
{//maxWT
    int v, w,cnt, minim=raiz;
    float PesoRuta,Peso;

    for (v = 0; v < getnumVertices(); v++)
    {
        this->padre[v] = -1;
        this->DistaMenosDe[v] = v;
        this->pesosPrim[v] = maxWT;
    }
    this->pesosPrim[getnumVertices()] = maxWT;
    this->pesosPrim[minim]=0;
    for (cnt=0; cnt< getnumVertices(); cnt++)
    {
        v = minim;
        this->padre[v] = this->DistaMenosDe[v];
        for (w = 0, minim = getnumVertices(); w < getnumVertices(); w++)
        {
            if (this->padre[w] == -1)
            {
                Peso =this->matriz[v][w];
                PesoRuta=this->pesosPrim[v]+Peso;
                if (Peso < this->pesosPrim[w]&&Peso!=0)
                {
                    this->pesosPrim[w] = Peso;
                    this->DistaMenosDe[w] = v;
                }
                if (this->pesosPrim[w] < this->pesosPrim[minim])
                {
                    minim = w;
                }
            }
        }
    }

}

void Grafo::MostrarPrim(int raiz)
{
    Prim(raiz);
    int i;
    printf(" Mostrando resultados algoritmo PRIM...\n ");
    for(i=0; i<getnumVertices(); i++)
    {
        printf("%d    ",i);
    }
    printf(" Vertices\n ");
    for(i=0; i<getnumVertices(); i++)
    {
        printf("%d    ",this->padre[i]);
    }
    printf(" Padre del vertice\n ");
    for(i=0; i<getnumVertices(); i++)
    {
        printf("%.2f ",this->pesosPrim[i]);
    }
    printf(" Peso trayecto entre vertice y raiz\n ");
    for(i=0; i<getnumVertices(); i++)
    {
        printf("%d    ",this->DistaMenosDe[i]);
    }
    printf(" Vertice que dista menos del vertice del arbol\n");
}

/******************************* ALGORITMO DE DIJKSTRA ******************************************/

void Grafo::Dijkstra(int raiz)
{
    int v,w,cnt, m = raiz;
    float PesoRuta,Peso;
    for(v=0; v<getnumVertices(); v++)
    {
        this->padre[v] = -1;
        this->DistaMenosDe[v] = v;
        this->pesosDijstra[v] = getnumVertices();
    }
    this->pesosDijstra[m] = 0;
    this->pesosDijstra[getnumVertices()]=getnumVertices();

    for(cnt=0; cnt<getnumVertices(); cnt++)
    {
        v = m;
        this->padre[m] = this->DistaMenosDe[m];
        for(w=0,m=getnumVertices(); w<getnumVertices(); w++)
        {
            if(this->padre[w]==-1)
            {
                Peso = this->matriz[v][w];
                PesoRuta = this->pesosDijstra[v] + Peso;
                if((Peso!=0)&&(PesoRuta<this->pesosDijstra[w]))
                {
                    this->pesosDijstra[w] = PesoRuta;
                    this->DistaMenosDe[w] = v;
                }
                if(this->pesosDijstra[w]<this->pesosDijstra[m])
                {
                    m = w;
                }
            }
        }
    }
}

void Grafo::MostrarDijkstra(int raiz)
{
    Dijkstra(raiz);
    int i;
    printf(" \nMostrando resultados algoritmo Dijkstra...\n");
    for(i=0; i<getnumVertices(); i++)
    {
        printf(" %d    ",i);
    }
    printf(" Vertices\n");
    for(i=0; i<getnumVertices(); i++)
    {
        printf(" %d    ",this->padre[i]);
    }
    printf("   Padre del vertice\n ");
    for(i=0; i<getnumVertices(); i++)
    {
        printf(" %.3f",this->pesosDijstra[i]);
    }
    printf("    Peso trayecto vertice y raiz\n");
    for(i=0; i<getnumVertices(); i++)
    {
        printf(" %d    ",this->DistaMenosDe[i]);
    }
    printf(" Vertice que dista menos del vertice del arbol\n");
}

/********************************ALGORITMO DE KRUSKAL*****************************************/

void Grafo::UneSubArboles(int p,int q)
{
    int i,t;
    if ( (foresta[p]==p) && (foresta[q]==q) ){//crea subárbol
        foresta[p]=cntf; foresta[q]=cntf; cntf++;
    } else
      if (foresta[p]<getnumVertices()) foresta[p]=foresta[q]; //pega p a subárbol q
       else
         if(foresta[q]<getnumVertices()) foresta[q]=foresta[p]; //pega q a subárbol p
            else
              for(t=foresta[p], i=0; i<getnumVertices(); i++)
                if(foresta[i] == t) foresta[i] = foresta[q]; //une subarbol p a subarbol q
}

int Grafo::NoPertenece(int p, int q){
    return (foresta[p] != foresta[q]);
}

void Grafo::MostrarKruskal(Arista *arist){
	int i, k, E;
    E=numElementos(arist);
    qsortnw(arist, 0, E-1); //ordena elementos por pesos.
    for(i=0; i<getnumVertices(); i++) foresta[i]=i; //crea conjunto de vértices.
    cntf=getnumVertices();
    for (i= 0, k = 0; i < E && k < (getnumVertices()-1); i++)
    if (NoPertenece( arist[i].getvInicial(), arist[i].getvFinal() )){
       UneSubArboles(arist[i].getvInicial(), arist[i].getvFinal());
       mst[k++] = arist[i]; //agrega rama al arbol
    }
}

void Grafo::qsortnw(Arista *arist, int l, int r)
{
    int i=l, j=r;
    Arista temp;
    float piv=arist[(l+r)/2].getpeso();
    do {
       while ( arist[i].getpeso() < piv)
          i++;
       while( piv < arist[j].getpeso())
          j--;
       if( i<=j){
	      if (i!=j) {
		    temp=arist[i];
		    arist[i]= arist[j];
            arist[j]=temp;
		  }
          i++;
		  j--;
       }
   } while(i<=j);

   if( l < j)
        qsortnw( arist, l, j);

   if( i < r )
        qsortnw( arist, i, r);
}

void Grafo::GRAPHmstKruskal(Arista *arist)
{
    int i, k, E;
    E=numElementos(arist); //Se crea representación de elementos a partir del grafo.
    qsortnw(arist, 0, E-1); //se ordena a los elementos, según el peso.
    UFinit(getnumVertices()); //crea conjunto de vértices.

    for (i= 0, k = 0; i < E && k < getnumVertices()-1; i++)//se agregan máximo V-1 ramas
        if (!UFfind(arist[i].getvInicial(), arist[i].getvFinal())){ //si v no está conectado a w
            UFunion(arist[i].getvInicial(), arist[i].getvFinal()); //se agregan vértices al conjunto
            mst[k++] = arist[i]; //se agrega rama e al árbol mst
        }
    UFdestroy();
}

void Grafo::MostrarKruskalP(Arista *arist)
{
    int i;
    GRAPHmstKruskal(arist);
    printf("Aristas    Pesos\n");
    for (i = 0; i < (getnumVertices()-1); i++)
    printf("%2d-%2d ->   %0.2f\n", mst[i].getvInicial(), mst[i].getvFinal(), mst[i].getpeso());
}

void Grafo::UFinit(int n)
{
    int i;
    this->id = new int[n];
    this->sz = new int[n];

    for(i=0;i<n;i++){
        id[i] = i;
        sz[i] = 1;
    }
}

int Grafo::Find(int x)
{
    int i=x;
    while(i!=this->id[i]){
        i = this->id[i];
    }
    return i;
}

int Grafo::UFfind(int p,int q)
{
    return (Find(p)==Find(q));
}

void Grafo::UFunion(int p,int q)
{
    int i = Find(p), j = Find(q);
    if (i == j) return;
    if (this->sz[i] < this->sz[j]){ //si nodos conectados a i es menor nodos conectados a j
        this->id[i] = j;
        this->sz[j] += this->sz[i];  //el i se pega al j y nodos de i se acumulan en j
    }else {
        this->id[j] = i;
        this->sz[i] += this->sz[j]; //el j se pega al i y nodos de j se acumulan en i
    }
}

void Grafo::UFdestroy(void)
{
    free(id);
    free(sz);
}

int Grafo::UFfind1(int p,int q)
{
    return (this->id[p]==this->id[q]);
}

void Grafo::UFunion1(int p,int q, int n)
{
    int t,i;
    for(t = this->id[p],i=0;i<n;i++){
        if(this->id[i]==t){
            this->id[i]=this->id[q];
        }
    }
}


#endif // GRAFOA_H_INCLUDED
