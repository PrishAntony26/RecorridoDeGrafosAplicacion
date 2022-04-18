/*
 * nomProgram: Arista.h
 * descripcion:
 *     Se propone la estructura de árboles ponderados mediante
 *     aristas de acuerdo a la modificación de las funciones de
 *     grafos ponderados según la página 17 del documento Grafos
 *     de Silva, donde, por último, se añade el concepto de
 *     encapsulación de componentes con getters y setters.
 *
 * INTEGRANTES:
 *	DOMINGUEZ ACOSTA, Prish Antony
 *	GUTIERREZ CARUAJULCA, Javier Antonio
 *	MALCA RAMIREZ, Jhonattan David
 *	VALERIO GAMBOA, Pedro Luis
 *
 * fecha: 26/08/2021
 */

#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>

using namespace std;

class Arista
{
	public:
	    Arista();
	    Arista(int vIni,int vFin);
		Arista(int vIni,int vFin, float peso);
		int getvInicial();
		int getvFinal();
		float getpeso();
		void setpeso(float peso);
	private:
		int vInicial;
		int vFinal;
		float peso;
		//float peso;
};

Arista::Arista()
{

}

Arista::Arista(int vIni,int vFin)
{
    this->vInicial = vIni;
    this->vFinal = vFin;
}

Arista::Arista(int vIni,int vFin,float peso)
{
	this->vInicial = vIni;
    this->vFinal = vFin;
    this->peso = peso;
}

int Arista::getvFinal()
{
	return vFinal;
}

int Arista::getvInicial()
{
	return vInicial;
}

float Arista::getpeso()
{
    return peso;
}

void Arista::setpeso(float peso)
{
    this->peso = peso;
}

#endif // ARISTA_H_INCLUDED
