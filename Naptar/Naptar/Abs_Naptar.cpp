#include <iostream>
#include "Abs_Naptar.h"
#include "Datum.h"
#include "Esemeny.h"

//Egy dátum ellenorzése, hogy lefoglalt-e vagy sem.
//A függvény true logikai érékkel tér vissza, ha a dátum már más esemény által foglalt, false értékkel ellenkezo esetben.
//@param vizsgalando_date- A dátum amirol szeretnénk megtudni, hogy foglalt-e.
//A dinmikusan tárolt lefoglalt eseményeket iterátorával bejárva ellenorizzük, hogy a dátum megegyezik-e a paramétebren megadott dátummal.
bool Abs_Naptar::foglalt_e(const Datum& vizsgalando_date) const
{

	for ( const_iterator i = begin(); i != end(); i++)
	{
		if ((*i).get_lefoglalt_datum() == vizsgalando_date) return true;
	}
	return false;
}

//A lefoglalt események kiiratása.
// Az események a dátumok idorendi sorrendjében kerülnek kiiratásra
// Az Esemény osztály kiiró függvénye felhasználásra kerül.
//@param os- kimenet
//Iterátorral bejárva kerülnek kiiratásta a lefoglalt események.
void Abs_Naptar::lefoglaltak_kiir(std::ostream& os) const
{
    os<<"A lefoglalt napok száma: "<<lefoglalt_napok_szama<<std::endl;
	for ( const_iterator i = begin(); i != end(); i++)
	{
		(*i).esemeny_kiir(os);
		os<<std::endl;
	}
}
//Törlés estén a foglalt_esemenzek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
//Csak azokat kell ebben az esetben kiírni, amelyek nem újévre esnek, mivel ez az esemény már a nptár objekzumok létrejöttekor létezik, így nem szabad a fájból újra beolvasni.
//@param os- kimenet
void Abs_Naptar::lefoglaltak_kiir_olvasashoz(std::ostream& os) const
{

	for ( const_iterator i = begin(); i != end(); i++)
	{
	    if((*i).get_lefoglalt_datum()!=Datum(2025,1,1))
		      (*i).esemeny_kiir_beolvasashoz(os);
	}
}

