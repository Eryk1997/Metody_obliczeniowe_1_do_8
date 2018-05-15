// LAB_08_MO.cpp : Defines the entry point for the console application.
//

// Zadanie8.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#define _USE_MATH_DEFINES 

#include <iostream>
#include <math.h>
#include <typeinfo>
#include <fstream>

double Krok = 0.1;

const int il_krok = 20;
const int ilosc_metod = 7;

using namespace std;



template <class typ>
typ fun(typ x) {


	return cos(x / 2.0);
}

template <class typ>
typ pochfun(typ x) {
	return (-1.0/2.0)*sin(x / 2.0);
}

template <class typ>
typ roz_progres_2p(typ x, typ h)
{
	return (fun(x + h) - fun(x)) / h;
	//return (cos(x/2 + h) - cos(x/2)) / h;
}

template <class typ>
typ roz_wstecz_2p(typ x, typ h)
{
	return (fun(x) - fun(x - h)) / h;
	//return (cos(x/2) - cos(x/2 - h)) / h;
}

template <class typ>
typ roz_centr_2p(typ x, typ h)
{
	return (fun(x + h) - fun(x - h)) / (2.0*h);
}

template <class typ>
typ roz_wstecz_3p(typ x, typ h)
{
	
	return (fun(x - 2.0*h) - 4.0*fun(x - h) + 3.0*fun(x)) / (2.0*h);
	
}

template <class typ>
typ roz_progres_3p(typ x, typ h)
{	
	return (4.0*fun(x + h) - (3.0*fun(x) + fun(x + 2.0*h))) / (2.0*h);
}

template <class typ>
void licz_roznice(typ *tabKrokow, typ **tabWynikow) {
	typ xp = 0.0;
	typ xs = M_PI_2 ;
	typ xk = M_PI ;
	typ krok = Krok;

	for (int i = 0; i < il_krok; i++) {
		tabKrokow[i] = krok;

		tabWynikow[0][i] = fabs(pochfun(xp) - roz_progres_2p(xp, krok));
		tabWynikow[1][i] = fabs(pochfun(xp) - roz_progres_3p(xp, krok));
		tabWynikow[2][i] = fabs(pochfun(xs) - roz_progres_2p(xs, krok));
		tabWynikow[3][i] = fabs(pochfun(xs) - roz_centr_2p(xs, krok));
		tabWynikow[4][i] = fabs(pochfun(xs) - roz_wstecz_2p(xs, krok));
		tabWynikow[5][i] = fabs(pochfun(xk) - roz_wstecz_2p(xk, krok));
		tabWynikow[6][i] = fabs(pochfun(xk) - roz_wstecz_3p(xk, krok));




		krok *= Krok;
	}
}

template <class typ>
void zapis(typ * tabKrokow, typ ** tabWynikow) {
	fstream plik;
	string nazwa = "dane_";

	nazwa += typeid(typ).name();
	nazwa += ".txt";

	plik.open(nazwa.c_str(), fstream::out);

	for (int j = 0; j<il_krok; j++) {
		plik << log10(tabKrokow[j]) << " ";

		for (int i = 0; i<7; i++) {
			plik << log10(tabWynikow[i][j]) << " ";
		}

		plik << endl;
	}

	plik.close();
}


int main()
{
	float *krokiFloat;
	double *krokiDouble;

	krokiFloat = new float[il_krok];
	krokiDouble = new double[il_krok];

	float **wynikiFloat;
	double **wynikiDouble;

	wynikiFloat = new float *[7];
	wynikiDouble = new double *[7];

	for (int i = 0; i<7; i++) {
		wynikiFloat[i] = new float[il_krok];
		wynikiDouble[i] = new double[il_krok];
	}

	licz_roznice(krokiFloat, wynikiFloat);
	licz_roznice(krokiDouble, wynikiDouble);

	zapis(krokiFloat, wynikiFloat);
	zapis(krokiDouble, wynikiDouble);
	return 0;
}






