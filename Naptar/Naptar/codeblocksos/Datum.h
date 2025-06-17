#pragma once
#include <iostream>
#include <string>
class Datum
{

private:
	int ev;
	int honap;
	int nap;
	static const std::string het_napjai[7];
public:
	//parameter n�lk�li konstruktor. Beallitja a d�tumot az idei �v els� napj�ra.
	Datum() 
	{

		ev = 2025;
		honap = 1;
		nap = 1;
	}

	//Param�teres konstruktor .
	Datum(int year, int month, int day) :ev(year), honap(month), nap(day) {};

	//M�sol� konstruktor.
	Datum(const Datum& date) 
	{
		ev = date.ev;
		honap = date.honap;
		nap = date.nap;
	}

	//�rt�kad� oper�tor.
	Datum& operator=(const Datum& date) 
	{
		if (this != &date) {
			ev = date.ev;
			honap = date.honap;
			nap = date.nap;
		}
		return *this;
	}

	//K�t d�tum �sszehasonlit�sa. Akkor t�r vissza igaz �rt�kkel a f�ggv�ny ha az els� d�tum a nagyobb.
	bool operator>(const Datum& hasonlitando_date) const;

	//K�t d�tum k�z�tti egyenl�s�gnek vizsg�lata. Igaz �rt�kkel t�r vissza, ha a d�tumok egyenl�ek, hamissal m�s esetben.
	bool operator==(const Datum& hasonlitando_date) const;

	//Kisebb rel�ci� vizsg�lata d�tumok k�zott. 
	// Megval�sit�s�hoz a kor�bban megval�sitott az "operator>" �s "operator=" tagf�ggv�nyek is fel vannak haszn�lva.
	bool operator<(const Datum& hasonlitando_date) const;

	//K�t d�tum k�z�tt eltelt nap kisz�mit�sa.
	// Az eltelt napok sz�m�val t�r vissza.
	int eltelt_napok(const Datum& date2) const {}
	//Kiirja a param�terk�nt kapott d�tumot a m�sik param�terk�nt 
	// megadott kimenetre
    //@param os- kimenet
	void datum_kiir(std::ostream& os) const;

	//D�tum beolvas�sa
	//@ param is- kimenet
	void datum_beolvas(std::istream& is) {}
	//A f�ggv�ny azt sz�molja ki, hogy egy napt�ri nap milyen napra esik.
	//A f�ggv�ny felhaszn�lja az eltelt napokat, 2025.04.21-hez k�pest .
	//Az igy kapott sz�mnak 7-el val� oszt�si marad�ka egy i sz�mot ad meg.
	//A het_napjai[i] t�riti vissza a megfelel� napot.
	std::string milyen_napra_esik() const {}
};



