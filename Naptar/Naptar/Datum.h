#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

class Datum
{

private:
	int ev;
	int honap;
	int nap;

public:

	//A h�t napjainak elnevez�snek deklar�l�sa. Sz�ks�g van m�s oszt�lyban is r�, ez�rt publikus.
	static std::string het_napjai[7];
	//Parameter n�lk�li konstruktor. Beallitja a d�tumot az idei �v elso napj�ra.
	Datum()
	{

		ev = 2025;
		honap = 1;
		nap = 1;
	}

	//Param�teres konstruktor .
	//Ha nem megfelelo a h�nap vagy nap param�tere std::out_of_range hiba�zenetet dob.
	Datum(int year, int month, int day)  {
		if (month < 1 || month>12)
		{
			throw std::out_of_range("Nincs ennyi h�nap. 1 �s 12 k�z�tt kell legyen.");
		}
		int max_nap_db = honap_napdb(month, year);
		if (day<1 || day>max_nap_db )
		{
			std::ostringstream oss;
			oss<<"Nincs ennyi nap ebben a h�napban. A napok sz�ma 1 �s "<< max_nap_db << " kell legyen.";
			throw std::out_of_range(oss.str());
		}
		ev = year;
		honap = month;
		nap = day;
	};

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
	//A napt�r kiirat�sn�l sz�ks�g van a napra.
	int getnap() const{
		return nap;
	}
	//K�t d�tum �sszehasonlit�sa. Akkor t�r vissza igaz �rt�kkel a f�ggv�ny ha az elso d�tum a nagyobb.
	bool operator>(const Datum& hasonlitando_date) const;

	//K�t d�tum k�z�tti egyenlos�gnek vizsg�lata. Igaz �rt�kkel t�r vissza, ha a d�tumok egyenloek, hamissal m�s esetben.
	bool operator==(const Datum& hasonlitando_date) const;

	//K�t d�tum k�z�tti elt�r�snek vizsg�lata.
	//Kisebb rel�ci� vizsg�lata d�tumok k�zott.
	// Megval�sit�s�hoz a kor�bban megval�sitott az "operator>" �s "operator=" tagf�ggv�nyek is fel vannak haszn�lva.
	bool operator<(const Datum& hasonlitando_date) const;

	//Kisebb vagy egyenlos�g vizsg�lata d�tumok k�z�tt.
	//A  kisebb oper�tor �s egyenlos�g felhaszn�l�s�val, ha egyik igaz igaz �rt�kkel t�r vissza, m�s esetben hamis �rt�kkel.
	bool operator<=(const Datum& hasonlitando_date) const;

	//nagyobb vagy egyenlos�g vizsg�lata d�tumok k�z�tt.
	//A  nagyobb oper�tor �s egyenlos�g felhaszn�l�s�val, ha egyik igaz igaz �rt�kkel t�r vissza, m�s esetben hamis �rt�kkel.
	bool operator>=(const Datum& hasonlitando_date) const;

	//K�t d�tum k�z�tti elt�r�snek vizsg�lata. Az "==" oper�tor van felhaszn�lva hozz�
    bool operator!=(const Datum& hasonlitando_date) const;

	//Vizsg�lja, hogy az adott �v sz�ko�v-e vagy sem.
    // true �rt�kkel t�r vissza, ha a d�tum �ve sz�ko�vre esik, false �rt�kkel m�s esetben.
	//@param jelenlegi_ev- A vizsg�land� �v
	//statikus, hogy m�s oszt�lyban is lehets�ges legyen d�tum objektum n�lk�l haszn�lni.
	static bool szokoev_e(int jelenlegi_ev) ;

	//Azt vizsg�lja egy �vben h�ny nap van.
	// A szokoev_e f�ggv�nyt haszn�lja fel, 366-ot t�rit vissza sz�ko�v eset�n, 365-�t ha nincs sz�ko�v.
	//@param jelenlegi_ev- A vizsg�land� �v
	//statikus, hogy m�s oszt�lyban is lehets�ges legyen d�tum objektum n�lk�l haszn�lni.
	static int ev_napdb(int jelenlegi_ev) ;

	//Megkeresi a d�tumban h�ny napb�l �ll az adott h�nap. A sz�ko�veket is sz�mit�sba veszi
    //A h�napban l�vo napok sz�m�val t�r vissza, eg�sz �rt�kkel
	//@param jelenlegi_honap- A vizsg�land� h�nap
	//@param jelenlegi_ev- A h�naphoz tartoz� �v amelyrol ellenorizni kell febru�ri h�nap eset�n,hogy sz�ko�vre esik.
	//statikus, hogy m�s oszt�lyban is lehets�ges legyen d�tum objektum n�lk�l haszn�lni.
	static int honap_napdb(int jelenlegi_honap, int jelenlegi_ev) ;

	//K�t d�tum k�z�tt eltelt nap kisz�mit�sa.
	// Az eltelt napok sz�m�val t�r vissza.
	int eltelt_napok(const Datum& date2) const;

	//Kiirja a param�terk�nt kapott d�tumot a m�sik param�terk�nt megadott kimenetre
    //@param os- kimenet
	void datum_kiir(std::ostream& os=std::cout) const;

	//A foglalt_esemenyek fileba csak az adatokat irjuk be a k�nnyebb olvas�s �rdek�ben.
    void datum_kiir_beolvasashoz(std::ostream& os=std::cout) const;

	//D�tum beolvas�sa
	//@param is- bemenet
	void datum_beolvas(std::istream& is = std::cin,std::ostream& os=std::cout);

	//A f�ggv�ny azt sz�molja ki, hogy egy napt�ri nap milyen napra esik.
	// A het_napjai[7] tartalmazza a h�t napjainak neveit.
	//A f�ggv�ny felhaszn�lja az eltelt napokat, 2025.04.21-hez k�pest .
	//Az igy kapott sz�mnak 7-el val� oszt�si marad�ka egy i sz�mot ad meg.
	//A het_napjai[i] t�riti vissza a megfelelo napot.
	std::string milyen_napra_esik() const;

};
//D�tum kiirat�sa operator<< segits�g�vel.
//@param os-kimenet, @param datum1- kiirand� d�tum.
inline std::ostream& operator<<(std::ostream& os, const Datum& datum1)
{
	datum1.datum_kiir(os);
	return os;
}
