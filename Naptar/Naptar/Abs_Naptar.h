#pragma once
#include <iostream>
#include "memtrace.h"
#include "Datum.h"
#include "Esemeny.h"
#include <stdexcept>
#include <sstream>

class Abs_Naptar
{
private:
	//A másoló konstruktor és értékadó operátor letiltása
	Abs_Naptar(const Abs_Naptar&) {}

	Abs_Naptar& operator=(const Abs_Naptar&)
	{
		return *this;
	}
protected:
	Esemeny* lefoglalt_esemenyek=nullptr;
	size_t lefoglalt_napok_szama=0;

public:

	//Az osztály default konstruktora.
	Abs_Naptar()
	{
		lefoglalt_esemenyek=nullptr;
		lefoglalt_napok_szama=0;
	}

	//Destruktor. A dinamikusan foglalt adatok felszabaditásáért felelos.
	~Abs_Naptar()
	{
		delete[] lefoglalt_esemenyek;
	}
	//Az összes nap számával tér vissza. Az a szerepe, hogy ez publikusan is látható legyen.
	// Virtuális, mivel a napok száma függ a naptár tipusától.
	virtual int capacity() const = 0;

	//A naptár kiiratása. Virtuális mivel más formában irandó ki az éves és a hónapos naptár.
	//param os- kimenet
	virtual void kiir(std::ostream& os = std::cout) const = 0;

	//Egy dátum ellenorzése, hogy lefoglalt-e vagy sem.
	//A függvény true logikai érékkel tér vissza, ha a dátum már más esemény által foglalt, false értékkel ellenkezo esetben.
	//@param vizsgalando_date- A dátum amirol szeretnénk megtudni, hogy foglalt-e.
	 bool foglalt_e(const Datum& vizsgalando_date) const;

	 //Egy esemény visszaadása annak dátuma szerint
	 //A függvény megkeresi azt az eseményt amelynek dátuma megegyezik a paraméterként adottal.
	 //Abban az esetben ha a paraméterként adott dátumon nincs még lefoglalt esemény saját kivételt dob az E osztályba.
	 //@param vizsgalando_date- A dátum amire foglalt eseményt meg szeretnénk keresni.
	 template<class E>
	 const Esemeny& Datum_Esemenye(const Datum& vizsgalando_date) const
	 {
		 for (const_iterator i = begin(); i != end(); i++)
		 {
			 if ((*i).get_lefoglalt_datum() == vizsgalando_date) return (*i);
		 }
		 std::stringstream hiba;
		 hiba << "**Helytelen dátum**";
		 vizsgalando_date.datum_kiir(hiba);
		 hiba << "A dátum még nincs lefoglalva semmilyen esemény által sem.";
		 throw E(hiba.str());
	 }
	//A lefoglalt események kiiratása.
	// Az események a dátumok idorendi sorrendjében kerülnek kiiratásra
	// Az Esemény osztály kiiró függvénye felhasználásra kerül.
	//@param os- kimenet
	 void lefoglaltak_kiir(std::ostream& os=std::cout) const ;

     //Törlés estén a foglalt_esemenyek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
     void lefoglaltak_kiir_olvasashoz(std::ostream& os=std::cout) const ;

	// Új esemény hozzáadása a lefoglalt események listájához
	// Abban az esetben ha ez a dátum már le van foglalva saját kivételt dob.
	// Az új eseményt úgy szúrja be, hogy az események dátum szerint növekvő sorrendben legyenek.
	// Ha az új esemény minden esemény dátumánál nagyobb, akkor a lista végére kerül.
	// Más esetben az új esemény be van szúrva két dátum közé majd a további események az eggyel kisebb indexu eseményt kapják meg.
	//@param uj_esemeny- A lefoglalt események listájához hozzáadandó esemény.

	 template<class E>
	 void foglalas(const Esemeny& uj_esemeny)
	 {
		 size_t uj_pozicio=lefoglalt_napok_szama;
		 if (foglalt_e(uj_esemeny.get_lefoglalt_datum()) == true)
		 {
			 std::stringstream  hiba;
			 hiba << "**Foglaláshiba**- A(z)";
			 uj_esemeny.get_lefoglalt_datum().datum_kiir(hiba);
			 hiba << " dátum már foglalt  más esemény által";
			 throw E(hiba.str());
		 }
		Esemeny* uj_esemenyes = new Esemeny[lefoglalt_napok_szama + 1];
		for (size_t i = 0; i< lefoglalt_napok_szama; i++)
		{
			if (lefoglalt_esemenyek[i].get_lefoglalt_datum() <= uj_esemeny.get_lefoglalt_datum())
				uj_esemenyes[i] = lefoglalt_esemenyek[i];
			else
			{
				uj_pozicio = i;
				break;
			}
		}
		uj_esemenyes[uj_pozicio] = uj_esemeny;
		for (size_t j = uj_pozicio; j < lefoglalt_napok_szama; j++)
			uj_esemenyes[j + 1] = lefoglalt_esemenyek[j];
		lefoglalt_napok_szama++;
		delete[]lefoglalt_esemenyek;
		lefoglalt_esemenyek = uj_esemenyes;
	 }

	//Esemény törlése a lefoglalt események listájából
	// Ha nem található meg a lefoglalt események között a paraméterként megadott esemény saját kivételt dob.
	// Miután megtalálta a függvény a törlendo eseményt, addig a pozicióig az eseményeket lefoglalja.
	// A törölt pozicótól az  események elcsusztatása által megkapjuk az új listát.
	// A függvénye összehasonlitja a listában lévo eseményeket és egyezés esetén törli
	template<class E>
	void torles(Esemeny& torlendo_esemeny)
	{
		size_t torlendo_pozicio =lefoglalt_napok_szama ;//A törölt elem poziciójának megtalálásához szükséges.
		for (size_t i = 0; i < lefoglalt_napok_szama; i++)
		{
			if (lefoglalt_esemenyek[i] == torlendo_esemeny)
			{
				torlendo_pozicio = i;
				break;
			}
		}
		if (torlendo_pozicio==lefoglalt_napok_szama)//Azt jelenti nincs ilyen esemény még lefoglalva
		{
			std::stringstream  hiba;
			hiba << "**Törlésshiba**- A(z)";
			torlendo_esemeny.esemeny_kiir(hiba);
			hiba << " esemény  még nincs lefoglalva, igy törölni se lehet.";
			throw E(hiba.str());
		}

		Esemeny* torolt_esemenyes = new Esemeny[lefoglalt_napok_szama -1];
		for (size_t i = 0; i < torlendo_pozicio; i++)
			torolt_esemenyes[i] = lefoglalt_esemenyek[i];
		for (size_t j = torlendo_pozicio; j < lefoglalt_napok_szama - 1; j++)
			torolt_esemenyes[j] = lefoglalt_esemenyek[j + 1];
		lefoglalt_napok_szama--;
		delete[]lefoglalt_esemenyek;
		lefoglalt_esemenyek = torolt_esemenyes;
	}

	//A kosnstans iterátor osztály eloredeklarálása
	class const_iterator;
	//Iterátor lézrehozása és az elso elemre állitása
	const_iterator begin() const{ return  const_iterator(*this); }

	//Iterátor létrehozása és a az utolsó elem utánra állitása
	const_iterator end()  const{ return const_iterator(*this, lefoglalt_napok_szama); }
	class const_iterator
	{
	private:
		//pointer az aktuális és utolsó utáni elemre
		const Esemeny* p_aktualis, * p_utolso;
	public:
		//Default konstruktor
		const_iterator() :p_aktualis(nullptr), p_utolso(nullptr) {}
		//Paraméteres konstruktor
		const_iterator(const Abs_Naptar& naptar, size_t idx = 0)
			:p_aktualis(naptar.lefoglalt_esemenyek + idx), p_utolso(naptar.lefoglalt_esemenyek + naptar.lefoglalt_napok_szama) {}
		//Iterátor preinkremens növelése
		const_iterator& operator++()
		{
			if (p_aktualis != p_utolso)
			{
				++p_aktualis;
			}
			return *this;
		}
		//Iterátor posztinkremens növelése
		const_iterator operator++(int)
		{
			const_iterator tmp = *this;
			operator++();
			return tmp;
		}
		//Iterátorok összehasonlitása
		bool operator!=(const const_iterator& masik) const {
			return p_aktualis != masik.p_aktualis;
		}
	   //Iterátor indirekciója
	   //Ha az iterátor a tár végén van std::out of range hibaüzenetet küld.
		const Esemeny& operator*() const
		{
			if (p_aktualis == p_utolso)
			{
				throw std::out_of_range("Iterátor a végén van.");
			}
			return *p_aktualis;
		}
	};
	//A lista egy elemének visszatéritése sorszáma alapján
	//Ha nem megfelelo az index, kivételt dob az E osztályba.
	template<class E>
	const Esemeny& getesemeny(size_t i)
	{
		if (i < 1)
		{
			std::stringstream  hiba;
			hiba << "**Indexhiba**- Nincs elem az első elem el?tt";
			throw E(hiba.str());
		}
		if(i>lefoglalt_napok_szama)
		{
			std::stringstream  hiba;
			hiba << "**Indexhiba**- Nincs " << i << " esemény lefoglalva csak " << lefoglalt_napok_szama;
			throw E(hiba.str());
		}
		return lefoglalt_esemenyek[i-1];
	}
	//Az fs-ben szereplo lefoglalt napokat beolvassa és lefoglalja.
    //Így valósítható meg , hogy a régebben lefoglalt napok megmaradjanak.
     template<class E>
     void foglalas_olvasas_file(std::istream& is )
     {
         if(is)
        {
                 while(is)
                 {
                     Esemeny lefoglalt_esemeny;
                     std::ostringstream alkiiro;//Ebben az esetben nem szükséges a kiirás ezért van használva egy néma output.
                     lefoglalt_esemeny.esemeny_beolvas(is,alkiiro);
                     foglalas<E>(lefoglalt_esemeny);
                  }
        }
        else{
            std::stringstream hiba;
            hiba<<"**Fájlhiba**-Nem sikerült a fájlt beolvasni";
            throw E(hiba.str());
        }


     }

};

