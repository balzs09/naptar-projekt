#pragma once
#include <iostream>
#include "memtrace.h"
#include "Datum.h"
#include "Esemeny.h"
#include <stdexcept>
//A T a dinamikusan foglalt területet jelenti. Ez lehet esemény vagy dátum is.
//Az E hibakezelési osztály. Alapértéke az std:range_error.
template<typename T,class E>
class Abs_Naptar
{
protected:

	size_t osszes_nap_szama;
	T* lefoglalt_esemenyek;
	size_t lefoglalt_napok_szama;

public:
	//Az osztály konstruktora.
	Abs_Naptar(T* esemenyek = nullptr, size_t lefoglalt_db = 0, size_t osszes_db = 0) : osszes_nap_szama(osszes_db) 
	{
		if (lefoglalt_db > 0 && esemenyek != nullptr)
		{
			lefoglalt_napok_szama = lefoglalt_db;
			lefoglalt_esemenyek = new T[lefoglalt_db];
			for (int i = 0; i < lefoglalt_napok_szama; i++)
				lefoglalt_esemenyek[i] = esemenyek[i];
		}
		else lefoglalt_esemenyek = nullptr;
	}

	//Az összes nap számával tér vissza. Az a szerepe, hogy ez publikusan is látható legyen.
	size_t capacity() const { return osszes_nap_szama; }

	//Destruktor. A dinamikusan foglalt adatok felszabaditásáért felelõs.
	 ~Abs_Naptar() 
	 {
		 delete[] lefoglalt_esemenyek;
	 }

	//A naptár kiiratása. Virtuális mivel más formában irandó ki az éves és a hónapos naptár.
	//param os- kimenet
	 virtual void kiir(std::ostream& os) const {}

	//Egy dátum ellenõrzése, hogy lefoglalt-e vagy sem. 
	//A függvény true logikai érékkel tér vissza, ha a dátum már más esemény által foglalt, false értékkel ellenkezõ esetben.
	//@param vizsgalando_date- A dátum amirõl szeretnénk megtudni, hogy foglalt-e.
	 bool foglalt_e(Datum vizsgalando_date) const {}

	//A lefoglalt események kiiratása.
	// Az események a dátumok idõrendi sorrendjében kerülnek kiiratásra
	// Az Esemény osztály kiiró függvénye felhasználásra kerül.
	//@param os- kimenet
	 void lefoglaltak_kiir(std::ostream& os) const {}

	//Új esemény hozzáadása a lefoglalt események listájához
	//@param uj_esemeny- A lefoglalt események listájához hozzáadandó esemény.
	 void foglalas(T& uj_esemeny) {}


	//Eseméy törlése a lefoglalt események listájából
	// A függvénye összehasonlitja a listában lévõ eseményeket és egyezés esetén törli
	 void torles(T& torlendo_esemeny) {}
	//Az iterátor osztály elõredeklarálása
	class iterator;
	//Iterátor lézrehozása és az elsõ elemre állitása
	iterator begin() {}

	//Iterátor létrehozása és a az utolsó elem utánra állitása
	iterator end() {}
	class iterator
	{
	private:
		//pointer az aktuális és utolsó utáni elemre
		Esemeny* p_aktualis, * p_utolso;
	public:
		iterator() :p_aktualis(0), p_utolso(0) {}
		iterator(Abs_Naptar& naptar, int idx = 0) :p_aktualis(naptar.lefoglalt_esemenyek + idx), p_utolso(naptar.lefoglalt_esemenyek + naptar.osszes_nap_szama) {}
		//Iterátor növelése
		iterator& operator++() {}
		//Iterátorok összehasonlitása
		bool operator!=(const iterator& i) {}
		//Indirekció, hibés indirekció esetén kivételt dob.
		T& operator*() {}

	};
	//A lista egy elemének visszatéritése sorszáma alapján
	T getesemeny(int i) const;
	
};

