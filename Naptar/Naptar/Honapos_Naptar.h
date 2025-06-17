#pragma once
#include <iostream>
#include "Abs_Naptar.h"
#include <string>

//A T a dinamikusan foglalt területet jelenti. Ez lehet esemény vagy dátum is.

class Honapos_Naptar :public Abs_Naptar
{
private:
	static  std::string honapok[12];

	int honap_sorszam;
	std::string megnevezes;
	int evszam;
	int osszes_nap;
public:
	//Az Abs_Naptar által örökölt tagváltozók paraméterekkel,
	// a Honapos_Naptar saját tagváltozói default megvalósitott konstruktor.
	Honapos_Naptar(int sorszam=1, int ev=2025)
		:Abs_Naptar()
	{
		//Annak ellenorzése érdekében, hogy 1 és 12 közötti érték a sorszám.
		Datum(ev, sorszam, 1);
		honap_sorszam = sorszam;
		megnevezes = honapok[sorszam - 1];
		evszam = ev;
		osszes_nap = Datum::honap_napdb(sorszam, ev);
	}

	//Az összes nap számával tér vissza. Az a szerepe, hogy ez publikusan is látható legyen.
	int capacity() const{
		return osszes_nap;
	}

	//Megadja azt a napot ahonnan kezdodik az adott hónap
	//@param date1- A hónap elso napjának dátuma.
	int het_kezdo_nap(const Datum& date1) const;


	//A hónap és a hét napjai kiiratása.
	void honap_het_kiir(std::ostream& os) const;

	// A napok kiiratása.
	// Azok a napok amik le vannak foglalva valamilyen esemény által "*"nap"*" jelölést kapnak.
	void nap_kiir(std::ostream& os, Datum& date1) const;

	//A hónapos naptár kiiratása.
	//param os- kimenet
	void kiir(std::ostream& os = std::cout) const;

};

