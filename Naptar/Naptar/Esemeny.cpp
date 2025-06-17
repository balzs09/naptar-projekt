#include<iostream>
#include <string>
#include "Esemeny.h"
#include "Datum.h"
//K�t esem�ny �sszehasonlit�sa.
// Igazzal t�r vissza, ha az esem�ny minden tagv�ltoz�ja megegyezik, hamissal ellenkezo esetben.
bool Esemeny::operator==(const Esemeny& hasonlitando_event) const
{
	if (megnevezes == hasonlitando_event.megnevezes && tipus == hasonlitando_event.tipus
		&& idopont == hasonlitando_event.idopont) return true;
	return false;
}

//K�t esem�ny �sszehasonlit�sa.
//Az operator== f�ggv�nyt haszn�lja fel a megval�sit�s.
bool Esemeny::operator!=(const Esemeny& hasonlitando_date) const
{
	if (!(*this == hasonlitando_date)) return true;
	return false;
}
// Az esem�ny tip�s�t sztringg� alakitja �t.A kiirat�shoz sz�ks�ges l�p�s ez
std::string Esemeny::tipus_to_string() const
{
	switch (tipus)
	{
	case munkahelyi:
		return "munkahelyi";
	case iskolai:
		return "iskolai";
	case maganeleti:
		return "mag�n�leti";
	case globalis:
		return "glob�lis";
	default:
		return "egy�b";
	}
}

// Az esem�ny tip�s neveit esem�ny tipuss�  alakitja �t.A beolvas�shoz sz�ks�ges l�p�s ez.
Esemeny_Tipusok Esemeny::string_to_tipus(const std::string& tipus_nev)
{

	if(tipus_nev== "munkahelyi") return munkahelyi;
	if(tipus_nev== "iskolai") return iskolai;
	if (tipus_nev == "mag�n�leti") return maganeleti;
	if (tipus_nev == "glob�lis") return globalis;
	return egyeb;

}

//Az esem�ny kiirat�sa.
//@param os- kimenet
void Esemeny::esemeny_kiir(std::ostream& os) const
{
	os << "Az esem�ny neve: " << megnevezes << std::endl;
	os <<"Az esem�ny tipusa: "<< tipus_to_string()<<std::endl;
	os << "Az esem�ny d�tuma: ";
	idopont.datum_kiir(os);

}

//A foglalt_esemenyek fileba csak az adatokat irjuk be a k�nnyebb olvas�s �rdek�ben.
void Esemeny::esemeny_kiir_beolvasashoz(std::ostream& os) const
{
    os<<megnevezes<<std::endl;
    os<<tipus_to_string()<<std::endl;
   idopont.datum_kiir_beolvasashoz(os);
}

//Az esem�ny beolvas�sa.
//@param is- bemenet
//@param os-A kimenet amire, kiirjuk a felhaszn�l�nak, hogy milyen form�tumban v�rjuk az �rkez? adatokat.
void Esemeny::esemeny_beolvas(std::istream& is , std::ostream& os )
{
	std::string esemeny_tipus;
	os << "Ird be az esemeny megnevez�s�t!" << std::endl;
	std::getline(is >>std::ws, megnevezes);
	os << " Ird be az esemeny tipus�t!" << std::endl;
	os<<"(munkahelyi, iskolai, mag�n�leti vagy glob�lis, ha egyikbe se tartozik, egyeb lesz az esem�ny tipusa" << std::endl;
	is >> esemeny_tipus;
	tipus = string_to_tipus(esemeny_tipus);
	os << "Ird be az esem�ny d�tum�t" << std::endl;
	idopont.datum_beolvas(is, os);

}
