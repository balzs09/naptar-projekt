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

	//Default konstruktor. Az �j �vet �llitja be, 2025.01.01 d�tummal, ez egy glob�lis esem�ny.
	Esemeny() :megnevezes("�j�v"), tipus(globalis), idopont(2025, 1, 1) {}

	//Param�teres konstruktor.
	Esemeny(const std::string& nev, Esemeny_Tipusok milyen, const Datum& mikor) :megnevezes(nev), tipus(milyen), idopont(mikor) {}

    //M�sol� konstruktor
	Esemeny(const Esemeny& event)
	{
		megnevezes = event.megnevezes;
		tipus = event.tipus;
		idopont = event.idopont;
	}

	//�rt�kad� oper�tor
	//A Napt�r oszt�lyban sz�ks�g van a dinamikusan foglalt esem�nyek elt�rol�sa �rdek�ben.
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

	//K�t esem�ny �sszehasonlit�sa.
	// Igazzal t�r vissza, ha az esem�ny minden tagv�ltoz�ja megegyezik, hamissal ellenkezo esetben.
	bool operator==(const Esemeny& hasonlitando_date) const;

	//K�t esem�ny �sszehasonlit�sa.
	//Az operator== f�ggv�nyt haszn�lja fel a megval�sit�s.
	bool operator!=(const Esemeny& hasonlitando_date) const;

	// Az esem�ny tip�s�t sztringg� alakitja �t.A kiirat�shoz sz�ks�ges l�p�s ez
    std::string tipus_to_string() const;

	// Az esem�ny tip�s neveit esem�ny tipuss�  alakitja �t.A beolvas�shoz sz�ks�ges l�p�s ez.
	static Esemeny_Tipusok string_to_tipus(const std::string& tipus_nev) ;

	// A napt�rban sz�ks�g van r�
	//A lefoglalt d�tum lek�rdez�se. Erre sz�ks�g van ,hogy lehessen tudni mely napok vannak lefoglalva a napt�rban.
	//Az esem�ny idopontj�val t�r vissza a f�ggv�ny.
	const Datum& get_lefoglalt_datum() const
	{
		return idopont;
	}


	//Az esem�ny kiirat�sa.
	//@param os- kimenet
	void esemeny_kiir(std::ostream& os = std::cout) const;

     //A foglalt_esemenyek fileba csak az adatokat irjuk be a k�nnyebb olvas�s �rdek�ben.
     void esemeny_kiir_beolvasashoz(std::ostream& os=std::cout) const;

	//Az esem�ny beolvas�sa.
	//@param is- kimenet
	void esemeny_beolvas(std::istream& is = std::cin, std::ostream& os = std::cout);
};
//Esem�ny kiirat�sa operator<< segits�g�vel.
//@param os-kimenet, @param datum1- kiirand� d�tum.
inline std::ostream& operator<<(std::ostream& os, const Esemeny& esemeny1)
{
	esemeny1.esemeny_kiir(os);
	return os;
}
