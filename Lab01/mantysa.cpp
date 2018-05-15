// epsylon_maszynowy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void epsylon() {
	cout << "Dla zmiennych typu \"float\"\n" << endl;
	float pf = 1.0f, pom_f = 2.0f;
	 int mantysa_f=0;
	while (pom_f>1.0f)
	{
		pf = pf / 2.0f;
		pom_f = pf + 1.0f; //aby unikn¹æ rozszerzonej precyzji (microsoft w visual studio zablokowa³ mo¿liwoœc rozszerzonej precyzji)
	if(pom_f>1.0f)
		mantysa_f++;
		
	}
	cout << "epsylon maszynowy = " << 2.0f * pf;
	cout <<" liczba bitow mantysy = " << mantysa_f << endl;

	cout << "\nDla zmiennych typu \"double\"\n" << endl;
	double pd = 1.0, pom_d=2.0;
	int mantysa_d = 0;
	while (pom_d>1.0)
	{
		pd = pd / 2.0;
		pom_d = pd + 1.0; //aby unikn¹æ rozszerzonej precyzji (microsoft w visual studio zablokowa³ mo¿liwoœc rozszerzonej precyzji)
		if (pom_d >1.0)
		mantysa_d++;

	}
	cout << "epsylon maszynowy = " << 2.0 * pd;
	cout << " liczba bitow mantysy = " << mantysa_d << endl;


};

int main()
{
	epsylon();
	system("pause");
    return 0;
}

