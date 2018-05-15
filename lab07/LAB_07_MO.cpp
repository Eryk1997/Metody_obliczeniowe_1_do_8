// LAB_07_MO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


double TOLX = 1e-12;
double TOLF = 1e-12;
int NMAX = 100;


void uzupelnij_dane(double **A, double *B, double *X0, int n);
void wypisz_macierz(double **A, int n);
void wypisz_wektor(double *V, int n);



void wypisz_rozwiazanie(int obieg,double *x,double estymator,double residuum, int n){

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << obieg << "\t";
	for (int i = 0; i < n; ++i)
		cout << fixed << x[i] << "\t";

	cout.setf(ios::scientific);
	cout.precision(10);
	cout << "\t" << scientific << estymator;
	cout << "\t" << scientific << residuum;
	cout << endl;
}

//********************************************************************
double max(double *x, int n, double **A,double *b) {

	
	double *Res = new double[n];//r=||Ax-b||


	for (int i = 0; i < n; ++i) {
		Res[i] = 0; 
		for (int j = 0; j < n; ++j)
			Res[i] += A[i][j] * x[j];
		Res[i] -= b[i];
		Res[i] = fabs(Res[i]);
	}

	

	double max = Res[0];
	for (int i = 0; i < n; ++i)
		if (fabs(Res[i]) > max)
			max = fabs(Res[i]);

	return max;
}
//********************************************************************
double Estymator(double *x0, double *x1, int n) {

	for (int i = 0; i < n; ++i)
		x0[i]= fabs(x0[i] - x1[i]);;

	double max = x0[0];
	for (int i = 0; i < n; ++i)
		if (x0[i] > max)
			max = fabs(x0[i]);

	return max;
}


//********************************************************************

void metodaJacobiego(double **A, double *B,double *X0, int n) {
	cout<<"Metoda Jacobiego\n";
	cout << "i \t x[0] \t x[1] \t x[2] \t x[3] \t\t estymator \t\t residuum\n" << endl;
	
	double *X1 = new double[n];
	double estymator=1, residuum=1;
	double suma = 0;
	int obieg = 0;

	while ((residuum>TOLF && estymator>TOLX) && NMAX>obieg) {
		obieg++;

		for (int i = 0; i < n; i++) {
			suma = 0;
			for (int j = 0; j < n; j++) 
				if (j != i)
					suma += A[i][j] * X0[j];

			X1[i] = (B[i]-suma) / A[i][i];
			
		}
		estymator = Estymator(X0,X1,n);
		residuum = max(X1, n,A,B);

		for (int i = 0; i < n; i++)
			X0[i] = X1[i];

		wypisz_rozwiazanie(obieg, X0,estymator,residuum,n);
	}
}
//********************************************************************

void Gaussa_Seidela(double **A, double *B, double *X0, int n) {
	cout << "\n\nMetoda Gaussa_Seidela\n\n";
	cout << "i \t x[0] \t x[1] \t x[2] \t x[3] \t\t estymator \t\t residuum\n" << endl;

	double *Xp = new double[n];
	double estymator = 1, residuum = 1;
	double suma = 0, suma1 = 0;
	int obieg = 0;

	while ((residuum > TOLF && estymator > TOLX) && NMAX > obieg) {
		obieg++;

		for (int i = 0; i < n; i++) {
			suma = 0;
			suma1 = 0;

			for (int j = 0; j < n; j++)
				if (j != i)
					suma += A[i][j] * X0[j];

			Xp[i] = X0[i];
					X0[i] = (B[i] - suma) / A[i][i];
				}
			
			estymator = Estymator(Xp, X0, n);
			residuum = max(X0, n,A,B);

			wypisz_rozwiazanie(obieg, X0, estymator, residuum, n);
		}
	}





//********************************************************************

void SOR(double **A, double *B, double *X0, int n) {
	cout << "\n\nMetoda SOR\n\n";
	cout << "i \t x[0] \t x[1] \t x[2] \t x[3] \t\t estymator \t\t residuum\n" << endl;

	double *Xp = new double[n];
	double estymator = 1, residuum = 1;
	double suma = 0;
	double Xtmp = 0;
	
double omega = 0.5;
	int obieg = 0;


	

	while ((residuum > TOLF && estymator > TOLX) && NMAX > obieg) {
		obieg++;

		for (int i = 0; i < n; i++) {
			suma = 0;

			for (int j = 0; j < n; j++)
				if (j != i)
					suma += A[i][j] * X0[j];

			Xtmp= (B[i] - suma) / A[i][i];

			Xp[i] = X0[i];
			X0[i] = (1-omega)*X0[i] +omega*Xtmp;
		}

		estymator = Estymator(Xp, X0, n);
		residuum = max(X0, n, A, B);



		wypisz_rozwiazanie(obieg, X0, estymator, residuum, n);
	}
}





//********************************************************************
int main()
{
	double **A, *B, *X0 ;
	int  n = 4; 
	//double omega = 0.5;


	A = new double *[n];

	for (int i = 0; i < n; i++)
		A[i] = new double[n];


	B = new double[n];
	X0 = new double[n];

	uzupelnij_dane(A, B, X0, n);

	wypisz_macierz(A, n);
	cout << "wektor b:" << endl;
	wypisz_wektor(B, n);
	cout << "przyblizenie poczatkowe x0:" << endl;
	wypisz_wektor(X0, n);


	metodaJacobiego(A, B, X0, n);
	uzupelnij_dane(A, B, X0, n);
	Gaussa_Seidela(A, B, X0, n);

	
		uzupelnij_dane(A, B, X0, n);
		SOR(A, B, X0, n);
	


	//getchar();
	system("pause");
    return 0;
}


//***********************************************************
void uzupelnij_dane(double **A, double *B, double *X0,  int n) {

	double Dane[] = { 100,1,-2,3,4,300,-5,6,7,-8,400,9,-10,11,-12,200 };

	int b = 0;
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			A[i][j] = Dane[b++];
	}

	B[0] = 395.0;
	B[1] = 603.0;
	B[2] = -415.0;
	B[3] = -606.0;

	X0[0] = 1.0;
	X0[1] = 1.0;
	X0[2] = 1.0;
	X0[3] = 1.0;


}


void wypisz_macierz(double **A, int n)
{
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "Macierz A:\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << setw(7) << A[i][j];

		cout << endl;
	}
	cout << endl;
}

void wypisz_wektor(double *V, int n)
{
	cout.setf(ios::fixed);
	cout.precision(2);

	for (int i = 0; i<n; i++)
		cout << V[i] << " ";

	cout << endl << endl;
}




/*  //niepotrzebne
void wypisz_LU(double **A, int n) {

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Macierz U:\n\n";
	int i, j;
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			if (j<i)
				cout << setw(7) << 0.00;
			else
				cout << setw(7) << A[i][j];
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "Macierz L:\n\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j > i)
				cout << setw(7) << 0.0;
			else {
				if (j == i)
					cout << setw(7) << 1.00;
				else
					cout << setw(7) << A[i][j];
			}
		}
		cout << endl;
	}

	cout << endl;
}


*/


// TO samo tylko d³u¿szy zapis:

/*

//********************************************************************

void Gaussa_Seidela2(double **A, double *B, double *X0, int n) {
	cout << "\n\nGaussa_Seidela2\n\n";
	cout << "i \t x[0] \t x[1] \t x[2] \t x[3] \t\t estymator \t\t residuum\n" << endl;

	double *Xp = new double[n];
	double estymator = 1, residuum = 1;
	double suma1 = 0, suma = 0;
	int obieg = 0;

	for (int i = 0; i<n; ++i) 
		Xp[i] = X0[i]+0.5;
		
	while ((residuum > TOLF && estymator > TOLX) && NMAX > obieg) {
		obieg++;

		for (int i = 0; i<n; ++i) {
			suma = 0;

			for (int j = 0; j<i; ++j) {
				suma += A[i][j] * X0[j];
			}
			for (int j = i + 1; j<n; ++j) {
				suma += A[i][j] * Xp[j];
			}

			X0[i] = (B[i] - suma) / A[i][i];
		}

		estymator = Estymator(Xp, X0, n);
		residuum = max(X0, n, A, B);

		for (int k = 0; k<n; ++k)
			Xp[k] = X0[k];

		wypisz_rozwiazanie(obieg, X0, estymator, residuum, n);
	}
}
*/




/*

void SOR2(double **A, double *B, double *X0, int n) {
cout << "\n\nMetoda SOR\n\n";
cout << "i \t x[0] \t x[1] \t x[2] \t x[3] \t\t estymator \t\t residuum\n" << endl;

double *Xp = new double[n];
double estymator = 1, residuum = 1;
double suma = 0;
double Xtmp = 0;
double omega = 0.5;
int obieg = 0;

for (int i = 0; i < n; ++i) {
Xp[i] = X0[i] ;


}


while ((residuum > TOLF && estymator > TOLX) && NMAX > obieg) {
obieg++;

for (int i = 0; i<n; ++i) {
suma = 0;

for (int j = 0; j<i; ++j) {
suma += A[i][j] * X0[j];
}
for (int j = i + 1; j<n; ++j) {
suma += A[i][j] * Xp[j];
}


X0[i] = (1 - omega)*Xp[i] + (omega / A[i][i])*(B[i] - suma);


}

estymator = Estymator(Xp, X0, n);
residuum = max(X0, n, A, B);

for (int k = 0; k<n; ++k)
Xp[k] = X0[k];

wypisz_rozwiazanie(obieg, X0, estymator, residuum, n);
}
}



*/