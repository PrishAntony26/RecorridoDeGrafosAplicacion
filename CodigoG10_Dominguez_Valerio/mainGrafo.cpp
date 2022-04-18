/*
 * nomProgram: mainGrafo.cpp
 * descripcion:
 *     Llamada a las operaciones básicas de grafos en cuanto se
 *     considere la inclusión de la clase Arista como componente
 *     del mismo, tal que, de este modo, por medio de un menú
 *     de opciones, se podrán ejecutar y visualizar las operaciones
 *     para grafos dirigidos y no dirigidos y, por último, se podrá
 *     recuperar grafos dirigidos y no dirigidos desde archivos
 *     binarios .dat, consiguiendo, de esta manera, la implementación
 *     de todas las operaciones destinadas en la especificación del proyecto.
 *
 * INTEGRANTES:
 *	DOMINGUEZ ACOSTA, Prish Antony
 *	GUTIERREZ CARUAJULCA, Javier Antonio
 *	MALCA RAMIREZ, Jhonattan David
 *	VALERIO GAMBOA, Pedro Luis
 *
 * fecha: 26/08/2021
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <queue>
#include "Grafo.h"
#include "Arista.h"
#define MCAR 50

typedef char Cadena[MCAR];
using namespace std;

//Plantillas de funciones
void elegirGrafo();
void accionNoDirigido();
void accionDirigido();
void marco();
void accionRecNoDirigido();
void accionRecDirigido();

void aplicacionProfundidadAnchura();
void aplicacionDijkstra();
void aplicacionPrimKruskal();

Arista* datosArista(bool dirigido);

//Función principal
int main(){
    elegirGrafo();
	return 0;
}

//Implementación de funciones
void marco()
{
    cout <<"\n\t\t==========================================================================="<<endl;
}

void elegirGrafo()
{
    int respuesta;
    do{
        system("cls");
        marco();
        printf("\t\t||                                                                       ||\n");
        printf("\t\t||             ESTRUCTURA DE DATOS SEMANA 13                             ||\n");
        printf("\t\t||                                                                       ||\n");
        printf("\t\t||              APLICACIONES EN LA VIDA REAL - GRAFOS                    ||\n");
        printf("\t\t||                                                                       ||\n");
        printf("\t\t||            0. SALIR.                                                  ||\n");
        printf("\t\t||            1. RECORRIDOS DE PROFUNDIDAD Y ANCHURA                     ||\n");
        printf("\t\t||            2. GRAFO DIJKSTRA                                          ||\n");
        printf("\t\t||            3. GRAFO PRIM Y KRUSKAL                                    ||\n");
        printf("\t\t||                                                                       ||\n");
        marco();
        cout<<"\tIngrese opcion [0-3] -> :  ";
        cin>>respuesta;
        switch(respuesta){
            case 0: printf("\t\t Gracias por usar el sistema\n\n");
                    break;
            case 1: printf("\t\t APLICACIONES DE RECORRIDOS DE PROFUNDIDAD Y ANCHURA \n\n");
                    aplicacionProfundidadAnchura();
                    system("pause");
                    break;
            case 2: printf("\t\t APLICACIONES DE ALGORITMO DIJKSTRA \n\n");
                    aplicacionDijkstra();
                    system("pause");
                    break;
            case 3: printf("\t\t APLICACIONES DE ALGORITMO PRIM Y KRUSKAL n\n");
                    aplicacionPrimKruskal();
                    system("pause");
                    break;
        }
    }while(respuesta!=0);
}

void aplicacionProfundidadAnchura()
{
   bool dirigido = true;
   bool nodirigido = false;

   printf("\n\n################## PROFUNDIDAD ANCHURA APP 1 ##################");
   char archivo[25] = "EjemploProfAnch1.txt";
   Grafo g1;
   g1 = g1.GrafoRecuperar(archivo,dirigido);
   printf("\n\t Matriz de adyacencias ");
   g1.mostrarMatrizIncidencias();
   printf("\n\t Busqueda por profundidad ");
   g1.EjecucionBusquedaEnProfundidad();
   printf("\n\t Busqueda por extension ");
   g1.MostrarBusquedaEnExtension();
   printf("\n\n################## PROFUNDIDAD ANCHURA APP 2 ##################");
   char archivo2[35] = "RecorridoMapaBusqueda.txt";
   Grafo g2;
   g2 = g2.GrafoRecuperar(archivo2,dirigido);
   printf("\n\t Matriz de adyacencias ");
   g2.mostrarMatrizIncidencias();
   printf("\n\t Busqueda por profundidad ");
   g2.EjecucionBusquedaEnProfundidad();
   printf("\n\t Busqueda por extension ");
   g2.MostrarBusquedaEnExtension();
   printf("\n");
}

void aplicacionDijkstra()
{
    bool dirigido = false;
    printf("\n\n################## ALGORITMO DIJKSTRA APP 1 ##################");
    char archivo[25] = "EjemploDijkstra1.txt";
    Grafo g1;
    g1 = g1.GrafoRecuperar(archivo,dirigido);
    printf("\n\t Matriz de adyacencias ");
    g1.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Dijkstra ");
    g1.MostrarDijkstra(0);
    printf("\n\n################## ALGORITMO DIJKSTRA APP  ##################");
    char archivo2[25] = "EjemploDijkstra2.txt";
    Grafo g2;
    g2 = g2.GrafoRecuperar(archivo2,dirigido);
    printf("\n\t Matriz de adyacencias ");
    g2.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Dijkstra ");
    g2.MostrarDijkstra(0);
}

void aplicacionPrimKruskal()
{
    bool dirigido = true;
    bool Nodirigido = false;
    printf("\n\n################## ALGORITMO PRIM APP 1 ##################");
    int aux;
    char archivo[20] = "EjemploPrim1.txt";
    Grafo g1;
    g1 = g1.GrafoRecuperar(archivo,dirigido);
    printf("\n\t Matriz de adyacencias ");
    g1.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Prim ");
    g1.MostrarPrim(0);

    printf("\n\n################## ALGORITMO PRIM APP 2 ##################");
    char archivo2[20] = "EjemploPrim2.txt";
    Grafo g2;
    g2 = g2.GrafoRecuperar(archivo2,Nodirigido);
    printf("\n\t Matriz de adyacencias ");
    g2.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Prim ");
    g2.MostrarPrim(0);
    system("pause");

    printf("\n\n################## ALGORITMO KRUSKAL APP 1 ##################");
    char archivo3[25] = "EjemploKruskal1.txt";
    Grafo g3;
    g3 = g3.GrafoRecuperar(archivo3,Nodirigido);
    Arista arist[g3.getelementos()];
    g3.numElementos(arist);
    printf("\n\t Matriz de adyacencias ");
    g3.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Prim ");
    g3.MostrarKruskalP(arist);
    system("pause");
    printf("\n\n################## ALGORITMO KRUSKAL APP 2 ##################");
    char archivo4[20] = "EjemploKruskal2.txt";
    Grafo g4;
    g4 = g4.GrafoRecuperar(archivo4,Nodirigido);
    Arista arist2[g4.getelementos()];
    g4.numElementos(arist2);
    printf("\n\t Matriz de adyacencias ");
    g4.mostrarMatrizIncidencias();
    printf("\n\t Algoritmo de Prim ");
    g4.MostrarKruskalP(arist2);
}


