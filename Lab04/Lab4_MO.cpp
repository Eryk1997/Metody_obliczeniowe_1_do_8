// Lab4_MO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iomanip>
#include <cstdlib> 
#include <iostream>
#include <math.h>
using namespace std;
typedef double(*funkcja)(double);

const int N_MAX = 1000;
const double TOLX = 10e-16; //|Xn-X(n-1)|=<=TOLX (~~0)
const double TOLF = 10e-16; //|f(x)|<=TOLF  (~~0)


void Newton(double x, double y, double z);
double max(double *d, int n);
void wypisz(int i, double x, double y, double z, double fx, double estymator);
void wypisz_macierz(double **mac);
double macierz_dopelnien(double **jac);
double dopelnienie(double a11, double a22, double a12, double a21);


double f(double x, double y, double z)
{
	return x*x + y*y + z*z - 2.0;
}

double g(double x, double y)
{
	return x*x + y*y - 1.0;
}

double h(double x, double y)
{
	return x*x - y;
}


double F1x(double x, double y, double z) {
	return 2 * x;
}
double F1y(double x, double y, double z) {
	return 2 * y;
}
double F1z(double x, double y, double z) {
	return 2 * z;
}
double F2x(double x, double y, double z) {
	return 2 * x;
}
double F2y(double x, double y, double z) {
	return 2 * y;
}
double F2z(double x, double y, double z) {
	return 0;
}
double F3x(double x, double y, double z) {
	return 2 * x;
}
double F3y(double x, double y, double z) {
	return -1;
}
double F3z(double x, double y, double z) {
	return 0;
}

/**********************************************************************************************************
***********************************************************************************************************/


int main()
{
	
	Newton(1, 1, 1.5);
	system("pause");
    return 0;
}

/**********************************************************************************************************
***********************************************************************************************************/

void Newton(double x, double y, double z) {
	int i = 0;
	double fx = 1.0;
	double estymator = 1.0;
	double Funkcja[3] = { 0 };
	double **Jacobia = new double *[3];
	for (int i = 0; i<3; i++)
		Jacobia[i] = new double[3];

	cout << "Metoda Newtona \nn:      x1:              x2:              x3:              residuum:        estymator: " << endl;

	Funkcja[0] = f(x, y, z);
	Funkcja[1] = g(x, y);
	Funkcja[2] = h(x, y);

	//macierz jacobiego^-1
	/*
	Jacobia[0][0] = 0;
	Jacobia[0][1] = 1.0 / (4 * y*x + 2 * x);
	Jacobia[0][2] = y / (2 * y*x + x);
	Jacobia[1][0] = 0;
	Jacobia[1][1] = 1.0 / (2 * y + 1);
	Jacobia[1][2] = -1.0 / (2 * y + 1);
	Jacobia[2][0] = 1.0 / (2 * z);
	Jacobia[2][1] = -1.0 / (2 * z);
	Jacobia[2][2] = 0;
	wypisz_macierz(Jacobia);
	*/


	while (i < N_MAX && estymator > TOLX && fabs(fx) > TOLF) {
		double delta[3] = { 0 };
		++i;

		Jacobia[0][0] = F1x(x, y, z);
		Jacobia[0][1] = F1y(x, y, z);
		Jacobia[0][2] = F1z(x, y, z);
		Jacobia[1][0] = F2x(x, y, z);
		Jacobia[1][1] = F2y(x, y, z);
		Jacobia[1][2] = F2z(x, y, z);
		Jacobia[2][0] = F3x(x, y, z);
		Jacobia[2][1] = F3y(x, y, z);
		Jacobia[2][2] = F3z(x, y, z);

		macierz_dopelnien(Jacobia);


		//mno¿enie macierzy przez wekror 
		for (int n = 0; n < 3; n++)
			for (int m = 0; m < 3; m++)
				delta[n] += (Jacobia[n][m] * Funkcja[m]);


		estymator = max(delta, 3);


		x -= delta[0];//xn+1=xn-delta
		y -= delta[1];
		z -= delta[2];


		Funkcja[0] = f(x, y, z);
		Funkcja[1] = g(x, y);
		Funkcja[2] = h(x, y);

		fx = max(Funkcja, 3);

		wypisz(i, x, y, z, fx, estymator);

	}

	delete[] Jacobia[0];
	delete[] Jacobia[1];
	delete[] Jacobia[2];
	delete Jacobia;

}





//*************************************************************************************************
double max(double *d, int n) {//d[n]

	double max = d[0];
	for (int i = 0; i < n; ++i)
		if (d[i] > max)
			max = fabs(d[i]);
	
	return max;

}

void wypisz(int i, double x, double y, double z, double fx, double estymator) {

	cout.width(3);
	cout << left << right << i << "  ";
	cout.precision(6);
	cout.width(15);
	cout << internal << scientific << x << "  ";
	cout.width(15);
	cout << internal << y << "  ";
	cout.width(15);
	cout << internal << z << "  ";
	cout.width(15);
	cout << internal  << fabs(fx) << "  ";
	cout.width(15);
	cout << internal << estymator << "  " << endl;
}


void wypisz_macierz(double **mac) {
	cout << "\nWypisana macierz: \n";
	for (int i = 0; i<3; i++)
	{
		cout << "\n\n";
		for (int j = 0; j<3; j++)
			cout << "      " << mac[i][j];
	}
}



double dopelnienie(double a11, double a22, double a12, double a21)                           //funkcja liczaca dopelnienia 
{
	return (a11*a22 - a12*a21);
}

double macierz_dopelnien(double **jac) {
	double macierz[3][3];
	int i, j;
	//cout << "\nWpisz liczby: \n " << endl;
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			//cout << "a" << i + 1 << j + 1 << " = ";
			//cin >> macierz[i][j];
			macierz[i][j] = jac[i][j];
		}
	}
	/*
	cout << "\nWypisana macierz: \n";
	for (i = 0; i<3; i++)
	{
	cout << "\n\n";
	for (j = 0; j<3; j++)
	cout << "      " << macierz[i][j];
	}
	*/



	double dop11, dop12, dop13, dop21, dop22, dop23, dop31, dop32, dop33; //dopelnienie algebraiczne
	double dop[3][3];

	dop11 = dop[0][0] = dopelnienie(macierz[1][1], macierz[2][2], macierz[1][2], macierz[2][1]);
	dop12 = dop[0][1] = (-1)*  dopelnienie(macierz[1][0], macierz[2][2], macierz[1][2], macierz[2][0]);
	dop13 = dop[0][2] = dopelnienie(macierz[1][0], macierz[2][1], macierz[1][1], macierz[2][0]);

	dop[1][0] = (-1)*  dopelnienie(macierz[0][1], macierz[2][2], macierz[0][2], macierz[2][1]);
	dop[1][1] = dopelnienie(macierz[0][0], macierz[2][2], macierz[0][2], macierz[2][0]);
	dop[1][2] = (-1)*dopelnienie(macierz[0][0], macierz[2][1], macierz[0][1], macierz[2][0]);

	dop[2][0] = dopelnienie(macierz[0][1], macierz[1][2], macierz[0][2], macierz[1][1]);
	dop[2][1] = (-1)*  dopelnienie(macierz[0][0], macierz[1][2], macierz[0][2], macierz[1][0]);
	dop[2][2] = dopelnienie(macierz[0][0], macierz[1][1], macierz[0][1], macierz[1][0]);


	//cout << "\n\n";


	double trans[3][3];                                                                  //macierzy transponowana
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
			trans[j][i] = dop[i][j];
	}

	/*
	cout << "\nMacierz transponowana (odwrotna): \n";
	for (i = 0; i<3; i++) {
	cout << "\n\n";
	for (j = 0; j<3; j++)
	cout << "     " << trans[i][j];
	}
	*/

	double det;                                                                             //obliczenie wyznacznika
	det = (macierz[0][0] * dop11) + (macierz[0][1] * dop12) + (macierz[0][2] * dop13);

	//cout << "\n\nWyznacznik macierzy jest: ";
	//cout << det << endl;


	if (det == 0)
	{                                                                       //sprawdzenie czy det=0
		cout << "\nMacierz jest osobliwa!\n\n";
		system("pause");
		return 0;
	}
	else {


		//cout << "\n\n Macierz A^-1: \n\n";                                      //macierz odwrotna
		for (i = 0; i<3; i++)
			for (j = 0; j < 3; j++) 
				jac[i][j] = (1 / det)*trans[i][j];
			
		
	}

	//cout << "\n\n";
	//system("pause");
	return 0;
}
