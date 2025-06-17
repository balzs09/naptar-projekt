#pragma once
#include <iostream>
#include <string>
class Datum
{

private:
	int ev;
	int honap;
	int nap;
	static const std::string het_napjai[7];
public:
	//parameter nélküli konstruktor. Beallitja a dátumot az idei év elsõ napjára.
	Datum() 
	{

		ev = 2025;
		honap = 1;
		nap = 1;
	}

	//Paraméteres konstruktor .
	Datum(int year, int month, int day) :ev(year), honap(month), nap(day) {};

	//Másoló konstruktor.
	Datum(const Datum& date) 
	{
		ev = date.ev;
		honap = date.honap;
		nap = date.nap;
	}

	//Értékadó operátor.
	Datum& operator=(const Datum& date) 
	{
		if (this != &date) {
			ev = date.ev;
			honap = date.honap;
			nap = date.nap;
		}
		return *this;
	}

	//Két dátum összehasonlitása. Akkor tér vissza igaz értékkel a függvény ha az elsõ dátum a nagyobb.
	bool operator>(const Datum& hasonlitando_date) const;

	//Két dátum közötti egyenlõségnek vizsgálata. Igaz értékkel tér vissza, ha a dátumok egyenlõek, hamissal más esetben.
	bool operator==(const Datum& hasonlitando_date) const;

	//Kisebb reláció vizsgálata dátumok közott. 
	// Megvalósitásához a korábban megvalósitott az "operator>" és "operator=" tagfüggvények is fel vannak használva.
	bool operator<(const Datum& hasonlitando_date) const;

	//Két dátum között eltelt nap kiszámitása.
	// Az eltelt napok számával tér vissza.
	int eltelt_napok(const Datum& date2) const {}
	//Kiirja a paraméterként kapott dátumot a másik paraméterként 
	// megadott kimenetre
    //@param os- kimenet
	void datum_kiir(std::ostream& os) const;

	//Dátum beolvasása
	//@ param is- kimenet
	void datum_beolvas(std::istream& is) {}
	//A függvény azt számolja ki, hogy egy naptári nap milyen napra esik.
	//A függvény felhasználja az eltelt napokat, 2025.04.21-hez képest .
	//Az igy kapott számnak 7-el való osztási maradéka egy i számot ad meg.
	//A het_napjai[i] tériti vissza a megfelelõ napot.
	std::string milyen_napra_esik() const {}
};



