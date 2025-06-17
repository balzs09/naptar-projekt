#pragma once

#include "Datum.h"
#include <string>
enum  Esemeny_Tipusok
{
	munkahelyi,iskolai, maganeleti, globalis,egyeb
};
class Esemeny
{
private:
	std::string megnevezes;
	Esemeny_Tipusok tipus;
	Datum idopont;
public:

	//Default konstruktor. Az új évet állitja be, 2025.01.01 dátummal, ez egy globális esemény.
	Esemeny() :megnevezes("újév"), tipus(globalis), idopont(2025, 1, 1) {}

	//Paraméteres konstruktor.
	Esemeny(const std::string& nev, Esemeny_Tipusok milyen, const Datum& mikor) :megnevezes(nev), tipus(milyen), idopont(mikor) {}

    //Másoló konstruktor
	Esemeny(const Esemeny& event)
	{
		megnevezes = event.megnevezes;
		tipus = event.tipus;
		idopont = event.idopont;
	}

	//Értékadó operátor
	//A Naptár osztályban szükség van a dinamikusan foglalt események eltárolása érdekében.
	Esemeny& operator=(const Esemeny& event)
	{
		if (this != &event)
		{
			megnevezes = event.megnevezes;
			tipus = event.tipus;
			idopont = event.idopont;
		}
		return *this;
	}

	//Két esemény összehasonlitása.
	// Igazzal tér vissza, ha az esemény minden tagváltozója megegyezik, hamissal ellenkezo esetben.
	bool operator==(const Esemeny& hasonlitando_date) const;

	//Két esemény összehasonlitása.
	//Az operator== függvényt használja fel a megvalósitás.
	bool operator!=(const Esemeny& hasonlitando_date) const;

	// Az esemény tipúsát sztringgé alakitja át.A kiiratáshoz szükséges lépés ez
    std::string tipus_to_string() const;

	// Az esemény tipús neveit esemény tipussá  alakitja át.A beolvasáshoz szükséges lépés ez.
	static Esemeny_Tipusok string_to_tipus(const std::string& tipus_nev) ;

	// A naptárban szükség van rá
	//A lefoglalt dátum lekérdezése. Erre szükség van ,hogy lehessen tudni mely napok vannak lefoglalva a naptárban.
	//Az esemény idopontjával tér vissza a függvény.
	const Datum& get_lefoglalt_datum() const
	{
		return idopont;
	}


	//Az esemény kiiratása.
	//@param os- kimenet
	void esemeny_kiir(std::ostream& os = std::cout) const;

     //A foglalt_esemenyek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
     void esemeny_kiir_beolvasashoz(std::ostream& os=std::cout) const;

	//Az esemény beolvasása.
	//@param is- kimenet
	void esemeny_beolvas(std::istream& is = std::cin, std::ostream& os = std::cout);
};
//Esemény kiiratása operator<< segitségével.
//@param os-kimenet, @param datum1- kiirandó dátum.
inline std::ostream& operator<<(std::ostream& os, const Esemeny& esemeny1)
{
	esemeny1.esemeny_kiir(os);
	return os;
}
