#pragma once
#include <iostream>
#include "Datum.h"
#include <string>
enum Esemeny_Tipusok
{
	munkahelyi,iskolai, maganeleti, globalis
};
class Esemeny
{
private:
	std::string megnevezes;
	Esemeny_Tipusok tipus;
	Datum idopont;
public:
	//Az esemény tipúsát sztringgé alakitja át. A kiiratáshoz szükséges lépés ez
	std::string tipus_to_string() {}

	//Default konstruktor. Az új évet állitja be, 2025.01.01 dátummal, ez egy globális esemény.
	Esemeny() :megnevezes("újév"), tipus(globalis), idopont(2025, 1, 1) {}

	//Paraméteres konstruktor.
	Esemeny(std::string nev, Esemeny_Tipusok milyen, Datum mikor) :megnevezes(nev), tipus(milyen), idopont(mikor) {}

    //Másoló konstruktor
	Esemeny(const Esemeny& event) {}

	//Értékadó operátor
	//A Naptár osztályban szükség van a dinamikusan foglalt események eltárolása érdekében.
	Esemeny& operator=(const Esemeny& event);

	//Két esemény összehasonlitása. 
	// Igazzal tér vissza, ha az esemény minden tagválzozója megegyezik, hamissal ellenkezõ esetben.
	bool operator==(const Datum& hasonlitando_date) const {}
	// A naptárban szükség van rá
	//A lefoglalt dátum lekérdezése. Erre szükség van ,hogy lehessen tudni mely napok vannak lefoflalva a naptárban.
	//Az esemény idõpontjával tér vissza a függvény.
	Datum get_lefoglalt_datum() const;
	

	//Az esemény kiiratása.
	//@param os- kimenet
	void esemeny_kiir(std::ostream& os) const {}


	//Az esemény beolvasása.
	//@param is- kimenet
	void esemeny_beolvas(std::istream& os) {}
};

