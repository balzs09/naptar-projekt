// Naptar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include "Datum.h"
#include "Esemeny.h"
#include "Abs_Naptar.h"
#include "Eves_Naptar.h"
#include "Honapos_Naptar.h"
#include <locale>
//kezdetleges tesztprogram

class Gond_Van
{
public:
	Gond_Van(const std::string&) {}
};
/*
//Test 1
//Esem�ny hozz�ad�sa a list�hoz.
//Default konstruktorok ker�lnek hiv�sra.
void test_1()
{
	Honapos_Naptar honap1;
	Esemeny e1;
	honap1.foglalas<Gond_Van>(e1);
	honap1.kiir(std::cout);
}
//D�tumok hasonlit�sa
void test_2()
{
	Datum date1;
	Datum date2(2013, 9, 4);
	Datum date3 = date1;
	Eves_Naptar ev1(2013, nullptr, 0);
	ev1.foglalas<Gond_Van>(date2);
	if (date1 >ev1.getesemeny(0)) date1.datum_kiir(std::cout);
	if (date1 == date3) date3.datum_kiir(std::cout);
	if (date3 < date2) date3.datum_kiir(std::cout);
	else date2.datum_kiir(std::cout);
}
//Esem�nyek t�rl�se, adatok beolvas�s�val
//Saj�t kiv�telt dob hib�s d�tum eset�n
void test_3()
{
	std::cout << "H�nyadik h�napot (1-12) szeretn�d l�tni?";
	int honap1;
	std::cin >> honap1;
	std::cout << "A h�nap esem�nyeinek beolvas�sa.";
	Esemeny* Esemenyek1;
	Esemenyek1 = new Esemeny[10];
	for (int i = 0; i < 10; i++)
	{
		Esemenyek1[i].esemeny_beolvas(std::cin);
	}
	Honapos_Naptar h_naptar1(Esemenyek1, 10, 31, honap1);
	delete[]Esemenyek1;
	std::cout << "Melyik esem�nyt szeretn�d t�r�lni?";
	Esemeny torlendo_event;
	torlendo_event.esemeny_beolvas(std::cin);
	h_naptar1.torles(torlendo_event);

}*/
//Az inputrol kapott sz�m alapj�n d�l el, hogy melyik teszteset hiv�dik.
int main()
{
     setlocale(LC_ALL, "");        // ez be�ll�tja az op.rendszer �ltal haszn�lt
                                 // nyelvi k�rnyezetet, amit felt�telez�nk, hogy magyar
	Honapos_Naptar honap1;
	/*try
	{
		std::cout << "Irj egy sz�mot 1-t�l 3-ig" << std::endl;
		int teszt_szam;
		std::cin >> teszt_szam;
		switch (teszt_szam) {
		case 1:
			test_1();   //List�hoz hozz�ad�s
			break;

		case 2:
			test_2();   //D�tumok hasonlit�sa
			break;

		case 3:
			test_3();   //T�rl�s
			break;
		}

	}catch (std::exception& e) {
	std::cerr << e.what() <<std:: endl;
    }
    catch (Gond_Van&) {
	std::cerr << "Sajat kivetel jott" <<std:: endl;
    }
    catch (...) {
	std::cerr << "*** Nagy baj van! ****" <<std::endl;
    }
return 0;*/

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

