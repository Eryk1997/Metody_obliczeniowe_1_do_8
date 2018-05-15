#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
const double eps = 1e-12;

void uzupelnij_dane(double **A, double *B, int *I,int n);
void wypisz_macierz(double **A, int *I, int n);
void wypisz_wektor(double *V, int n);
void wypisz_LU(double **A, int *I, int n);



bool wybor_elementu_podstawowego(double **A, int *I, int i,int n) {
	int imax=1, m;
	for (m = i; m < n; ++m) {
		if (fabs(A[I[m]][i]) > eps)
			imax = m;
	}

	if(imax==i)
		return false;

	// Zamianiamy wiersz macierzy

	cout << "Zamieniono elementy z wiersza " << i << " z wierszem " << imax << "." << endl;

	I[i] = imax;
	I[imax] = i;

	return true;
}


void dekompozycjaLU(double **A, int *I, int n) {

	int i, j, k,z, ii; //ii=i-1
	double tmp;

	for (i = 1; i < n; ++i) 
	{
		ii = i - 1;
		if (fabs(A[I[ii]][ii]) == 0.0)
			if (!wybor_elementu_podstawowego(A,I,ii,n)) {
				cout<<"mie mozna wybrac elementu podstawowego";
				exit(-1);
			}

		for (j = i; j < n; ++j) 
		{

			A[I[j]][ii]=A[I[j]][ii]/A[I[ii]][ii]; 
			for (k = i; k < n; ++k) {
				A[I[j]][k] -= (A[I[ii]][k] * A[I[j]][ii]);
			} 
		}

	}

}

void rozwiazanie_ukladu(double **A, double *B, int *I, int n) {
	
	int i, j;
	double suma=0;
	//Ly=b
	//macierz trójkatna dolna:

	for (i = 0; i<n; i++){
		for (j = 0; j<i; j++)
			suma = suma + A[I[i]][j] * B[I[j]];
		B[I[i]] = B[I[i]] - suma;
		suma = 0;
	}

	
	//Ux=y
	//macierz trójkatna gorna:
	suma = 0;
	for (i = n-1; i >= 0; i--){
		for (j = i + 1; j<n; j++)
			suma = suma + A[I[i]][j] * B[I[j]];
		B[I[i]] = (B[I[i]] - suma) / A[I[i]][i];
		suma = 0;
	}
	

}



int main()
{
double **A, *B; 
int *I, n = 4; //I -wektor indeksów, n- rozmiar macierzy NxN
//cin >> n;


A = new double *[n];

for (int i = 0; i < n; i++) 
	A[i] = new double[n];


B = new double[n];
I = new int[n];

uzupelnij_dane(A, B, I, n);

wypisz_macierz(A,I,n);
cout << "Wektor b:\n\n";
wypisz_wektor(B, n);
dekompozycjaLU(A, I, n);
wypisz_LU(A, I, n);
rozwiazanie_ukladu(A, B, I, n);


cout << "ROZWIAZANIE - wektor x:\n\n"; 
wypisz_wektor(B, n);


system("pause");
}




void uzupelnij_dane(double **A, double *B, int *I,int n) {
	
	double Dane[] = { 1,20,-30,-4,4,20,-6,50,9,-18,12,-11,16,-15,14,130 };
	
	int b = 0;
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			A[i][j] = Dane[b++];
	}

	B[0] = 0.0;
	B[1] = 114.0;
	B[2] = -5.0;
	B[3] = 177.0;

	I[0] = 0;
	I[1] = 1;
	I[2] = 2;
	I[3] = 3;

}


void wypisz_macierz(double **A, int *I, int n)
{
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "Macierz A:\n\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << setw(7) << A[I[i]][j];

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

void wypisz_LU(double **A, int *I, int n) {

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Macierz U:\n\n";
	int i, j;
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			if (j<i)
				cout << setw(7) << 0.00;
			else
				cout << setw(7) << A[I[i]][j];
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
					cout << setw(7) << A[I[i]][j];
			}
		}
		cout << endl;
	}

	cout << endl;
}