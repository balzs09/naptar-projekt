#include "Datum.h"
#include <iostream>
#include <iomanip>//A d�tum kiirat�shoz sz�ks�ges manipul�torokat is haszn�lni.
#include <string>
//A h�t napjai defini�l�sa
const std::string het_napjai[] = { "h�tf�","kedd","szerda","cs�t�rt�k","p�ntek","szombat","vas�rnap" };

//K�t d�tum �sszehasonlit�sa. Akkor t�r vissza igaz �rt�kkel a f�ggv�ny ha az els� d�tum a nagyobb.
bool Datum::operator>(const Datum& hasonlitando_date) const
{
	if (ev > hasonlitando_date.ev) return true;
	else if (ev == hasonlitando_date.ev)
	{
		if (honap > hasonlitando_date.honap) return true;
		else if (honap == hasonlitando_date.honap)
		{
			if (nap > hasonlitando_date.nap) return true;
		}
	}
	return false;
}

//K�t d�tum k�z�tti egyenl�s�gnek vizsg�lata. Igaz �rt�kkel t�r vissza, ha a d�tumok egyenl�ek, hamissal m�s esetben.
bool Datum::operator==(const Datum& hasonlitando_date) const
{
	if (ev == hasonlitando_date.ev && honap == hasonlitando_date.honap && nap == hasonlitando_date.nap) return true;
	else return false;
}

//Kisebb rel�ci� vizsg�lata d�tumok k�zott. 
// Megval�sit�s�hoz a kor�bban megval�sitott az "operator<" �s "operator=" tagf�ggv�nyek is fel vannak haszn�lva.
bool Datum::operator<(const Datum& hasonlitando_date) const
{
	if (!(*this > hasonlitando_date) && !(*this == hasonlitando_date)) return true;
	return false;
}
//Kiirja a  d�tumot param�terk�nt megadott kimenetre
//param os- kimenet
void Datum::datum_kiir(std::ostream& os) const
{
	os << ev << "." << std::setw(2) << std::setfill('0') << honap<<"."
	   <<std::setw(2) << std::setfill('0') << nap<<std::endl;
}

