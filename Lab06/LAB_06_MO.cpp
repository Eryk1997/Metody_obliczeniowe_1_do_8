#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <exception>

using namespace std;

void wczytajDane(double *nadDiag, double *Diag, double *podDiag, double *B, int n);
bool macierzDominujaca(double *nadDiag, double *Diag, double *podDiag, double *B, int n);
void wypisz_wektor(double *V, int n, string t);
void wypisz_mac(double *nadDiag, double *Diag, double *podDiag, double *B, int n);
//void AlgorytmThomasa_rozwiazanie_w_1_funkcji(double *nadDiag, double *Diag, double *podDiag, double *B, int n, double *X);

void AlgorytmThomasa_macierz(double *nadDiag, double *Diag, double *podDiag, int n) {

	double l;
	int i;

	for (i = 1; i < n; i++)
	{
		//l = podDiag[i - 1] / Diag[i - 1];
		Diag[i] = Diag[i] - (podDiag[i - 1] / Diag[i - 1]) * nadDiag[i - 1];//wyliczamy eta[i]
		
	}
}

void AlgorytmThomasa_rozwiazanie(double *nadDiag, double *Diag, double *podDiag, double *B, int n, double *X) {
	
	double l;
	int i;

	for (i = 1; i < n; i++)
	{
		//l = podDiag[i - 1] / Diag[i - 1];
		B[i] = B[i] - (podDiag[i - 1] / Diag[i - 1])* B[i - 1];//wyliczamy r[i]
	}

	X[n-1] = B[n-1] / Diag[n-1];//trójkatna górna
	for (i = n - 2; i >= 0; i--)
		X[i] = (B[i] - nadDiag[i] * X[i + 1]) / Diag[i]; //wyliczamy X[i]

}

//*******************************************************************************
int main() {

	double *nadDiag, *Diag, *podDiag,*B,*X;

	int n = 6; //rozmier macierzy (wektora)

	nadDiag = new double[n-1];
	Diag = new double[n];
	podDiag = new double[n-1];
	B = new double[n];
	X = new double[n];

	wczytajDane(nadDiag, Diag, podDiag, B, n);

	wypisz_wektor(nadDiag, n - 1, "wektor naddiagonalny:");
	wypisz_wektor(Diag, n, "wektor diagonalny:");
	wypisz_wektor(podDiag, n - 1, "wektor poddiagonalny:");
	wypisz_wektor(B, n, "wektor wyrazow wolnych:");
	wypisz_mac(nadDiag, Diag, podDiag, B, n);

	if (!macierzDominujaca(nadDiag, Diag, podDiag, B, n))
		cout << "Macierz nie jest diagonalnie dominujaca!";

	AlgorytmThomasa_macierz(nadDiag, Diag, podDiag, n);
	AlgorytmThomasa_rozwiazanie(nadDiag, Diag, podDiag, B, n,X);

	cout << "Algorytm Thomasa\n\n";

	wypisz_wektor(Diag, n, "wektor eta:");
	wypisz_wektor(B, n, "wektor r:");
	wypisz_wektor(X, n, "Rozwiazanie - wektor X:");

	getchar();
}


//******************************************************************************

bool macierzDominujaca(double *nadDiag, double *Diag, double *podDiag, double *B, int n){
//Sprawdzenie czy macierz jest diagonalnie silnie dominujaca (wiersze)
	for (int i = 0; i < n; ++i) {
		if (i == 0){
			if (!(fabs(Diag[i]) > nadDiag[i]))
				return false;//"Macierz nie jest diag. dominujaca!"
		}

		else if(i==n-1){
			if (!(fabs(Diag[i]) > podDiag[i]))
				return false;
		}
		else {
			if (!(fabs(Diag[i]) >nadDiag[i]+ podDiag[i]))
				return false;
		}

	}

	
	return true;
}




void wypisz_wektor(double *V, int n,string t)
{
	cout << t << endl;
	cout.setf(ios::fixed);
	cout.precision(2);

	for (int i = 0; i<n; i++)
		cout << V[i] << " ";

	cout << endl << endl;
}


void wczytajDane(double *nadDiag, double *Diag, double *podDiag, double *B, int n) {
	nadDiag[0] = 2. / 3.;
	nadDiag[1] = 5. / 6.;
	nadDiag[2] = 9. / 10.;
	nadDiag[3] = 13. / 14.;
	nadDiag[4] = 17. / 18.;

	Diag[0] = 30.0;
	Diag[1] = 20.0;
	Diag[2] = 10.0;
	Diag[3] = 10.0;
	Diag[4] = 20.0;
	Diag[5] = 30.0;

	podDiag[0] = 3. / 4.;
	podDiag[1] = 7. / 8.;
	podDiag[2] = 11. / 12.;
	podDiag[3] = 15. / 16.;
	podDiag[4] = 19. / 20.;


	B[0] = 94. / 3.;
	B[1] = 173. / 4.;
	B[2] = 581. / 20.;
	B[3] = -815. / 28.;
	B[4] = -6301. / 144.;
	B[5] = -319. / 10.;
}



void wypisz_mac(double *nadDiag, double *Diag, double *podDiag, double *B, int n)
{
	double zero = 0.0;

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Podana Macierz:\n";

	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				cout <<setw(7)<< Diag[i];
			}
			else if(j-1==i)
			{
				cout << setw(7) << nadDiag[j-1];
			}

			else if (j+1 == i )
			{
				cout << setw(7) << podDiag[j];
			}

			else {
				cout << setw(7) << zero;
			}
		}
		cout << endl;	
	}
	cout << endl;
}



/*/
void AlgorytmThomasa_rozwiazanie_w_1_funkcji(double *nadDiag, double *Diag, double *podDiag, double *B, int n, double *X) {

	double l;
	int i;

	for (i = 1; i < n; i++)
	{
		l = podDiag[i - 1] / Diag[i - 1];
		Diag[i] = Diag[i] - l*nadDiag[i - 1];
		B[i] = B[i] - l* B[i - 1];
	}



	X[n - 1] = B[n - 1] / Diag[n - 1];
	for (i = n - 2; i >= 0; i--)
		X[i] = (B[i] - nadDiag[i] * X[i + 1]) / Diag[i];

}

/*/