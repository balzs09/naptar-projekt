#pragma once
#include <iostream>
#include "Abs_Naptar.h"
//A T a dinamikusan foglalt ter�letet jelenti. Ez lehet esem�ny vagy d�tum is.
template<typename T,class E = std::range_error>
class Eves_Naptar:public Abs_Naptar<T,E>
{
private:
	int evszam;
    
public:
	//Megvizsgalja, hogy egy �v sz�k��v-e vagy sem.
	//A napok sz�m�val az �vben t�r vissza.
	static size_t nap_db_evben(int ev);

	//Param�teres konstruktor. A napok sz�ma az �v alapj�n sz�mithat� ki.
	Eves_Naptar(int ev=2025, T* esemenyek=nullptr, size_t lefoglalt_db=0) :Abs_Naptar<T,E>(esemenyek, lefoglalt_db, nap_db_evben(ev)),evszam(ev) {}
	
	//Destruktor. A dinamikusan foglalt adatok felszabadit�s��rt felel�s.
	~Eves_Naptar() {}


	//Az �ves napt�r kiirat�sa.
	//param os- kimenet
	void kiir(std::ostream& os) const {}

};

