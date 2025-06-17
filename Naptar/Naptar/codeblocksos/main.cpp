#include <iostream>
#include <string>
#include <stdexcept>
#include "Datum.h"
#include "Esemeny.h"
#include "Abs_Naptar.h"
#include "Eves_Naptar.h"
#include "Honapos_Naptar.h"
//kezdetleges tesztprogram

class Gond_Van
{
public:
	Gond_Van(const std::string&) {}
};
//Test 1
//Esemény hozzáadása a listához.
//Default konstruktorok kerülnek hivásra.
void test_1()
{
	Honapos_Naptar<Esemeny> honap1;
	Esemeny e1;
	honap1.foglalas(e1);
	honap1.kiir(std::cout);
}
//Dátumok hasonlitása
void test_2()
{
	Datum date1;
	Datum date2(2013, 9, 4);
	Datum date3 = date1;
	Eves_Naptar<Datum> ev1(2013, nullptr, 0);
	ev1.foglalas(date2);
	if (date1 >ev1.getesemeny(0)) date1.datum_kiir(std::cout);
	if (date1 == date3) date3.datum_kiir(std::cout);
	if (date3 < date2) date3.datum_kiir(std::cout);
	else date2.datum_kiir(std::cout);
}
//Események törlése, adatok beolvasásával
//Saját kivételt dob hibás dátum esetén
void test_3()
{
	std::cout << "Hányadik hónapot (1-12) szeretnéd látni?";
	int honap1;
	std::cin >> honap1;
	std::cout << "A hónap eseményeinek beolvasása.";
	Esemeny* Esemenyek1;
	Esemenyek1 = new Esemeny[10];
	for (int i = 0; i < 10; i++)
	{
		Esemenyek1[i].esemeny_beolvas(std::cin);
	}
	Honapos_Naptar<Esemeny, Gond_Van> h_naptar1(Esemenyek1, 10, 31, honap1);
	delete[]Esemenyek1;
	std::cout << "Melyik eseményt szeretnéd törölni?";
	Esemeny torlendo_event;
	torlendo_event.esemeny_beolvas(std::cin);
	h_naptar1.torles(torlendo_event);

}
//Az inputrol kapott szám alapján dõl el, hogy melyik teszteset hivódik.
int main()
{

	try
	{
		std::cout << "Irj egy számot 1-tõl 3-ig" << std::endl;
		int teszt_szam;
		std::cin >> teszt_szam;
		switch (teszt_szam) {
		case 1:
			test_1();   //Listához hozzáadás
			break;

		case 2:
			test_2();   //Dátumok hasonlitása
			break;

		case 3:
			test_3();   //Törlés
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
return 0;

}
