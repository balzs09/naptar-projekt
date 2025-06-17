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
	//Az esem�ny tip�s�t sztringg� alakitja �t. A kiirat�shoz sz�ks�ges l�p�s ez
	std::string tipus_to_string() {}

	//Default konstruktor. Az �j �vet �llitja be, 2025.01.01 d�tummal, ez egy glob�lis esem�ny.
	Esemeny() :megnevezes("�j�v"), tipus(globalis), idopont(2025, 1, 1) {}

	//Param�teres konstruktor.
	Esemeny(std::string nev, Esemeny_Tipusok milyen, Datum mikor) :megnevezes(nev), tipus(milyen), idopont(mikor) {}

    //M�sol� konstruktor
	Esemeny(const Esemeny& event) {}

	//�rt�kad� oper�tor
	//A Napt�r oszt�lyban sz�ks�g van a dinamikusan foglalt esem�nyek elt�rol�sa �rdek�ben.
	Esemeny& operator=(const Esemeny& event);

	//K�t esem�ny �sszehasonlit�sa. 
	// Igazzal t�r vissza, ha az esem�ny minden tagv�lzoz�ja megegyezik, hamissal ellenkez� esetben.
	bool operator==(const Datum& hasonlitando_date) const {}
	// A napt�rban sz�ks�g van r�
	//A lefoglalt d�tum lek�rdez�se. Erre sz�ks�g van ,hogy lehessen tudni mely napok vannak lefoflalva a napt�rban.
	//Az esem�ny id�pontj�val t�r vissza a f�ggv�ny.
	Datum get_lefoglalt_datum() const;
	

	//Az esem�ny kiirat�sa.
	//@param os- kimenet
	void esemeny_kiir(std::ostream& os) const {}


	//Az esem�ny beolvas�sa.
	//@param is- kimenet
	void esemeny_beolvas(std::istream& os) {}
};

