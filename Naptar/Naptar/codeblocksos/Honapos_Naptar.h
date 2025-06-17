#pragma once
#include <iostream>
#include "Abs_Naptar.h"
#include <string>
//A T a dinamikusan foglalt területet jelenti. Ez lehet esemény vagy dátum is.
template <typename T,class E = std::range_error>
class Honapos_Naptar :public Abs_Naptar< T,E>
{
private:
	static  std::string honapok[12];
	int honap_sorszam;
	std::string megnevezes;
public:
	//Az Abs_Naptar által örökölt tagváltozók paraméterekkel,
	// a Honapos_Naptar saját tagváltozói default megvalósitott konstruktor.
	Honapos_Naptar(T* taken_events=nullptr, size_t lefoglalt_db=0,size_t osszes_db=0,int sorszam=1) :Abs_Naptar<T,E>(taken_events, lefoglalt_db,osszes_db), megnevezes(honapok[sorszam]), honap_sorszam(sorszam) {}

	//Destruktor. A dinamikusan foglalt adatok felszabaditásáért felelõs.
	~Honapos_Naptar() {}

	//A hónapos naptár kiiratása.
	//param os- kimenet
	void kiir(std::ostream& os) const {}
	
	
};

