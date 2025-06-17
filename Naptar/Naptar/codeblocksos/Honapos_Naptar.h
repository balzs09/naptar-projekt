#pragma once
#include <iostream>
#include "Abs_Naptar.h"
#include <string>
//A T a dinamikusan foglalt ter�letet jelenti. Ez lehet esem�ny vagy d�tum is.
template <typename T,class E = std::range_error>
class Honapos_Naptar :public Abs_Naptar< T,E>
{
private:
	static  std::string honapok[12];
	int honap_sorszam;
	std::string megnevezes;
public:
	//Az Abs_Naptar �ltal �r�k�lt tagv�ltoz�k param�terekkel,
	// a Honapos_Naptar saj�t tagv�ltoz�i default megval�sitott konstruktor.
	Honapos_Naptar(T* taken_events=nullptr, size_t lefoglalt_db=0,size_t osszes_db=0,int sorszam=1) :Abs_Naptar<T,E>(taken_events, lefoglalt_db,osszes_db), megnevezes(honapok[sorszam]), honap_sorszam(sorszam) {}

	//Destruktor. A dinamikusan foglalt adatok felszabadit�s��rt felel�s.
	~Honapos_Naptar() {}

	//A h�napos napt�r kiirat�sa.
	//param os- kimenet
	void kiir(std::ostream& os) const {}
	
	
};

