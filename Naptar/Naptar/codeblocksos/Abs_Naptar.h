#pragma once
#include <iostream>
#include "memtrace.h"
#include "Datum.h"
#include "Esemeny.h"
#include <stdexcept>
//A T a dinamikusan foglalt ter�letet jelenti. Ez lehet esem�ny vagy d�tum is.
//Az E hibakezel�si oszt�ly. Alap�rt�ke az std:range_error.
template<typename T,class E>
class Abs_Naptar
{
protected:

	size_t osszes_nap_szama;
	T* lefoglalt_esemenyek;
	size_t lefoglalt_napok_szama;

public:
	//Az oszt�ly konstruktora.
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

	//Az �sszes nap sz�m�val t�r vissza. Az a szerepe, hogy ez publikusan is l�that� legyen.
	size_t capacity() const { return osszes_nap_szama; }

	//Destruktor. A dinamikusan foglalt adatok felszabadit�s��rt felel�s.
	 ~Abs_Naptar() 
	 {
		 delete[] lefoglalt_esemenyek;
	 }

	//A napt�r kiirat�sa. Virtu�lis mivel m�s form�ban irand� ki az �ves �s a h�napos napt�r.
	//param os- kimenet
	 virtual void kiir(std::ostream& os) const {}

	//Egy d�tum ellen�rz�se, hogy lefoglalt-e vagy sem. 
	//A f�ggv�ny true logikai �r�kkel t�r vissza, ha a d�tum m�r m�s esem�ny �ltal foglalt, false �rt�kkel ellenkez� esetben.
	//@param vizsgalando_date- A d�tum amir�l szeretn�nk megtudni, hogy foglalt-e.
	 bool foglalt_e(Datum vizsgalando_date) const {}

	//A lefoglalt esem�nyek kiirat�sa.
	// Az esem�nyek a d�tumok id�rendi sorrendj�ben ker�lnek kiirat�sra
	// Az Esem�ny oszt�ly kiir� f�ggv�nye felhaszn�l�sra ker�l.
	//@param os- kimenet
	 void lefoglaltak_kiir(std::ostream& os) const {}

	//�j esem�ny hozz�ad�sa a lefoglalt esem�nyek list�j�hoz
	//@param uj_esemeny- A lefoglalt esem�nyek list�j�hoz hozz�adand� esem�ny.
	 void foglalas(T& uj_esemeny) {}


	//Esem�y t�rl�se a lefoglalt esem�nyek list�j�b�l
	// A f�ggv�nye �sszehasonlitja a list�ban l�v� esem�nyeket �s egyez�s eset�n t�rli
	 void torles(T& torlendo_esemeny) {}
	//Az iter�tor oszt�ly el�redeklar�l�sa
	class iterator;
	//Iter�tor l�zrehoz�sa �s az els� elemre �llit�sa
	iterator begin() {}

	//Iter�tor l�trehoz�sa �s a az utols� elem ut�nra �llit�sa
	iterator end() {}
	class iterator
	{
	private:
		//pointer az aktu�lis �s utols� ut�ni elemre
		Esemeny* p_aktualis, * p_utolso;
	public:
		iterator() :p_aktualis(0), p_utolso(0) {}
		iterator(Abs_Naptar& naptar, int idx = 0) :p_aktualis(naptar.lefoglalt_esemenyek + idx), p_utolso(naptar.lefoglalt_esemenyek + naptar.osszes_nap_szama) {}
		//Iter�tor n�vel�se
		iterator& operator++() {}
		//Iter�torok �sszehasonlit�sa
		bool operator!=(const iterator& i) {}
		//Indirekci�, hib�s indirekci� eset�n kiv�telt dob.
		T& operator*() {}

	};
	//A lista egy elem�nek visszat�rit�se sorsz�ma alapj�n
	T getesemeny(int i) const;
	
};

