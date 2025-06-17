#include<iostream>
#include <string>
#include "Esemeny.h"
#include "Datum.h"
//Két esemény összehasonlitása.
// Igazzal tér vissza, ha az esemény minden tagváltozója megegyezik, hamissal ellenkezo esetben.
bool Esemeny::operator==(const Esemeny& hasonlitando_event) const
{
	if (megnevezes == hasonlitando_event.megnevezes && tipus == hasonlitando_event.tipus
		&& idopont == hasonlitando_event.idopont) return true;
	return false;
}

//Két esemény összehasonlitása.
//Az operator== függvényt használja fel a megvalósitás.
bool Esemeny::operator!=(const Esemeny& hasonlitando_date) const
{
	if (!(*this == hasonlitando_date)) return true;
	return false;
}
// Az esemény tipúsát sztringgé alakitja át.A kiiratáshoz szükséges lépés ez
std::string Esemeny::tipus_to_string() const
{
	switch (tipus)
	{
	case munkahelyi:
		return "munkahelyi";
	case iskolai:
		return "iskolai";
	case maganeleti:
		return "magánéleti";
	case globalis:
		return "globális";
	default:
		return "egyéb";
	}
}

// Az esemény tipús neveit esemény tipussá  alakitja át.A beolvasáshoz szükséges lépés ez.
Esemeny_Tipusok Esemeny::string_to_tipus(const std::string& tipus_nev)
{

	if(tipus_nev== "munkahelyi") return munkahelyi;
	if(tipus_nev== "iskolai") return iskolai;
	if (tipus_nev == "magánéleti") return maganeleti;
	if (tipus_nev == "globális") return globalis;
	return egyeb;

}

//Az esemény kiiratása.
//@param os- kimenet
void Esemeny::esemeny_kiir(std::ostream& os) const
{
	os << "Az esemény neve: " << megnevezes << std::endl;
	os <<"Az esemény tipusa: "<< tipus_to_string()<<std::endl;
	os << "Az esemény dátuma: ";
	idopont.datum_kiir(os);

}

//A foglalt_esemenyek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
void Esemeny::esemeny_kiir_beolvasashoz(std::ostream& os) const
{
    os<<megnevezes<<std::endl;
    os<<tipus_to_string()<<std::endl;
   idopont.datum_kiir_beolvasashoz(os);
}

//Az esemény beolvasása.
//@param is- bemenet
//@param os-A kimenet amire, kiirjuk a felhasználónak, hogy milyen formátumban várjuk az érkez? adatokat.
void Esemeny::esemeny_beolvas(std::istream& is , std::ostream& os )
{
	std::string esemeny_tipus;
	os << "Ird be az esemeny megnevezését!" << std::endl;
	std::getline(is >>std::ws, megnevezes);
	os << " Ird be az esemeny tipusát!" << std::endl;
	os<<"(munkahelyi, iskolai, magánéleti vagy globális, ha egyikbe se tartozik, egyeb lesz az esemény tipusa" << std::endl;
	is >> esemeny_tipus;
	tipus = string_to_tipus(esemeny_tipus);
	os << "Ird be az esemény dátumát" << std::endl;
	idopont.datum_beolvas(is, os);

}
