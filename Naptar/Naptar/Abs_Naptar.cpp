#include <iostream>
#include "Abs_Naptar.h"
#include "Datum.h"
#include "Esemeny.h"

//Egy d�tum ellenorz�se, hogy lefoglalt-e vagy sem.
//A f�ggv�ny true logikai �r�kkel t�r vissza, ha a d�tum m�r m�s esem�ny �ltal foglalt, false �rt�kkel ellenkezo esetben.
//@param vizsgalando_date- A d�tum amirol szeretn�nk megtudni, hogy foglalt-e.
//A dinmikusan t�rolt lefoglalt esem�nyeket iter�tor�val bej�rva ellenorizz�k, hogy a d�tum megegyezik-e a param�tebren megadott d�tummal.
bool Abs_Naptar::foglalt_e(const Datum& vizsgalando_date) const
{

	for ( const_iterator i = begin(); i != end(); i++)
	{
		if ((*i).get_lefoglalt_datum() == vizsgalando_date) return true;
	}
	return false;
}

//A lefoglalt esem�nyek kiirat�sa.
// Az esem�nyek a d�tumok idorendi sorrendj�ben ker�lnek kiirat�sra
// Az Esem�ny oszt�ly kiir� f�ggv�nye felhaszn�l�sra ker�l.
//@param os- kimenet
//Iter�torral bej�rva ker�lnek kiirat�sta a lefoglalt esem�nyek.
void Abs_Naptar::lefoglaltak_kiir(std::ostream& os) const
{
    os<<"A lefoglalt napok sz�ma: "<<lefoglalt_napok_szama<<std::endl;
	for ( const_iterator i = begin(); i != end(); i++)
	{
		(*i).esemeny_kiir(os);
		os<<std::endl;
	}
}
//T�rl�s est�n a foglalt_esemenzek fileba csak az adatokat irjuk be a k�nnyebb olvas�s �rdek�ben.
//Csak azokat kell ebben az esetben ki�rni, amelyek nem �j�vre esnek, mivel ez az esem�ny m�r a npt�r objekzumok l�trej�ttekor l�tezik, �gy nem szabad a f�jb�l �jra beolvasni.
//@param os- kimenet
void Abs_Naptar::lefoglaltak_kiir_olvasashoz(std::ostream& os) const
{

	for ( const_iterator i = begin(); i != end(); i++)
	{
	    if((*i).get_lefoglalt_datum()!=Datum(2025,1,1))
		      (*i).esemeny_kiir_beolvasashoz(os);
	}
}

