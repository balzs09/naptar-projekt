#pragma once
#include <iostream>
#include "Abs_Naptar.h"
//A T a dinamikusan foglalt területet jelenti. Ez lehet esemény vagy dátum is.
template<typename T,class E = std::range_error>
class Eves_Naptar:public Abs_Naptar<T,E>
{
private:
	int evszam;
    
public:
	//Megvizsgalja, hogy egy év szökõév-e vagy sem.
	//A napok számával az évben tér vissza.
	static size_t nap_db_evben(int ev);

	//Paraméteres konstruktor. A napok száma az év alapján számitható ki.
	Eves_Naptar(int ev=2025, T* esemenyek=nullptr, size_t lefoglalt_db=0) :Abs_Naptar<T,E>(esemenyek, lefoglalt_db, nap_db_evben(ev)),evszam(ev) {}
	
	//Destruktor. A dinamikusan foglalt adatok felszabaditásáért felelõs.
	~Eves_Naptar() {}


	//Az éves naptár kiiratása.
	//param os- kimenet
	void kiir(std::ostream& os) const {}

};

