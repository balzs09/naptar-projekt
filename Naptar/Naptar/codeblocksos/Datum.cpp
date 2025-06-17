#include "Datum.h"
#include <iostream>
#include <iomanip>//A dátum kiiratáshoz szükséges manipulátorokat is használni.
#include <string>
//A hét napjai definiálása
const std::string het_napjai[] = { "hétfõ","kedd","szerda","csütürtök","péntek","szombat","vasárnap" };

//Két dátum összehasonlitása. Akkor tér vissza igaz értékkel a függvény ha az elsõ dátum a nagyobb.
bool Datum::operator>(const Datum& hasonlitando_date) const
{
	if (ev > hasonlitando_date.ev) return true;
	else if (ev == hasonlitando_date.ev)
	{
		if (honap > hasonlitando_date.honap) return true;
		else if (honap == hasonlitando_date.honap)
		{
			if (nap > hasonlitando_date.nap) return true;
		}
	}
	return false;
}

//Két dátum közötti egyenlõségnek vizsgálata. Igaz értékkel tér vissza, ha a dátumok egyenlõek, hamissal más esetben.
bool Datum::operator==(const Datum& hasonlitando_date) const
{
	if (ev == hasonlitando_date.ev && honap == hasonlitando_date.honap && nap == hasonlitando_date.nap) return true;
	else return false;
}

//Kisebb reláció vizsgálata dátumok közott. 
// Megvalósitásához a korábban megvalósitott az "operator<" és "operator=" tagfüggvények is fel vannak használva.
bool Datum::operator<(const Datum& hasonlitando_date) const
{
	if (!(*this > hasonlitando_date) && !(*this == hasonlitando_date)) return true;
	return false;
}
//Kiirja a  dátumot paraméterként megadott kimenetre
//param os- kimenet
void Datum::datum_kiir(std::ostream& os) const
{
	os << ev << "." << std::setw(2) << std::setfill('0') << honap<<"."
	   <<std::setw(2) << std::setfill('0') << nap<<std::endl;
}

