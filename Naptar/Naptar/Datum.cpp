#include "Datum.h"
#include <iostream>
#include <iomanip>//A d�tum kiirat�shoz sz�ks�ges manipul�torokat is haszn�lni.
#include <string>


//A h�t napjai defini�l�sa
 std::string Datum:: het_napjai[] = { "h�tf�","kedd","szerda","cs�t�rt�k","p�ntek","szombat","vas�rnap" };

//K�t d�tum �sszehasonlit�sa. Akkor t�r vissza igaz �rt�kkel a f�ggv�ny ha az elso d�tum a nagyobb.
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

//K�t d�tum k�z�tti egyenlos�gnek vizsg�lata. Igaz �rt�kkel t�r vissza, ha a d�tumok egyenloek, hamissal m�s esetben.
bool Datum::operator==(const Datum& hasonlitando_date) const
{
	if (ev == hasonlitando_date.ev && honap == hasonlitando_date.honap && nap == hasonlitando_date.nap) return true;
	return false;
}

//Kisebb rel�ci� vizsg�lata d�tumok k�zott.
// Megval�sit�s�hoz a kor�bban megval�sitott az "operator<" �s "operator=" tagf�ggv�nyek is fel vannak haszn�lva.
bool Datum::operator<(const Datum& hasonlitando_date) const
{
	if (!(*this > hasonlitando_date) && !(*this == hasonlitando_date)) return true;
	return false;
}

//Kisebb vagy egyenlos�g vizsg�lata d�tumok k�z�tt.
//A  kisebb oper�tor �s egyenlos�g felhaszn�l�s�val, ha egyik igaz igaz �rt�kkel t�r vissza, m�s esetben hamis �rt�kkel.
bool Datum::operator<=(const Datum& hasonlitando_date) const
{
	if((*this<hasonlitando_date)||(*this==hasonlitando_date)) return true;
	return false;
}

//nagyobb vagy egyenlos�g vizsg�lata d�tumok k�z�tt.
//A  nagyobb oper�tor �s egyenlos�g felhaszn�l�s�val, ha egyik igaz igaz �rt�kkel t�r vissza, m�s esetben hamis �rt�kkel.
bool Datum::operator>=(const Datum& hasonlitando_date) const
{
	if ((*this > hasonlitando_date) || (*this == hasonlitando_date)) return true;
	return false;
}

//K�t d�tum k�z�tti elt�r�snek vizsg�lata. Az "==" oper�tor van felhaszn�lva hozz�
bool Datum::operator!=(const Datum& hasonlitando_date) const
{
    return !(*this==hasonlitando_date);
}
//Vizsg�lja, hogy az adott �v sz�ko�v-e vagy sem.
// true �rt�kkel t�r vissza, ha a d�tum �ve sz�ko�vre esik, false �rt�kkel m�s esetben.
//param jelenlegi_ev- A vizsg�land� �v
 bool Datum::szokoev_e(int jelenlegi_ev)
{
	if ((jelenlegi_ev % 4 == 0&&jelenlegi_ev%100!=0)||(jelenlegi_ev%400==0)) return true;
	else return false;
}

//Azt vizsg�lja egy �vben h�ny nap van.
// A szokoev_e f�ggv�nyt haszn�lja fel, 366-ot t�rit vissza sz�ko�v eset�n, 365-�t ha nincs sz�ko�v.
//@param jelenlegi_ev- A vizsg�land� �v
int Datum::ev_napdb(int jelenlegi_ev)
{
	if (szokoev_e(jelenlegi_ev)) return 366;
	else return 365;
}
//Megkeresi a d�tumban h�ny napb�l �ll az adott h�nap. A sz�ko�veket is sz�mit�sba veszi
//A h�napban l�vo napok sz�m�val t�r vissza, eg�sz �rt�kkel
//Elosz�r ellenorzi, hogy 31 napos-e a h�nap, majd ,hogy 30 napos se.
//Ha egyik se, a h�nap febru�r, azt kell ellenorizni, hogy sz�ko�v van vagy sem
//@param jelenlegi_honap- A vizsg�land� h�nap
//@param jelenlegi_ev- A h�naphoz tartoz� �v amelyrol ellen�rizni kell febru�ri h�nap eset�n,hogy sz�ko�vre esik.
int Datum::honap_napdb(int jelenlegi_honap,int jelenlegi_ev)
{
	if ((jelenlegi_honap < 8 && jelenlegi_honap % 2 == 1) || (jelenlegi_honap >= 8 && jelenlegi_honap % 2 == 0)) return 31;
	else if ((jelenlegi_honap > 2 && jelenlegi_honap % 2 == 0) || (jelenlegi_honap >= 9 && jelenlegi_honap % 2 == 1)) return 30;
	else if (szokoev_e(jelenlegi_ev)) return 29;
	else return 28;
}
//K�t d�tum k�z�tt eltelt nap kisz�mit�sa.
// Az eltelt napok sz�m�val t�r vissza.
//A f�ggv�ny eloszor azt az esetet ellenorzi, ahol csak a napok k�l�nb�znek, ilyenkor ki kell vonni a nagyobb napb�l a kisebbiket.
//Ha a h�napok is k�l�nb�znek, akkor a k�ztes h�napok napjai hozz�ad�dnak az �sszeghez.
//A kisebb h�napb�l a d�tum napja ut�ni napok ker�lnek be mig a nagyobb h�napb�l a d�tum elottiek.
//Ha az �vek k�l�nb�znek is hasonl� a megval�sit�s. Ilyenkor beker�lnek a kisebb �vben k�vetkezendo h�napok, a nagyobban az elteltek.
//A k�ztes �vek napjai is �sszead�dnak �s a k�t h�nap k�vetkezendo �s eltelt napja.
int Datum::eltelt_napok(const Datum& date2) const
{
	Datum date1_copy = *this;
	Datum date2_copy = date2;
	int eltelt_nap = 0;
	if (*this < date2)
	{
		Datum aux = date1_copy;
		date1_copy= date2_copy;
		date2_copy= aux;
	}
	if (date1_copy.ev == date2_copy.ev && date1_copy.honap == date2_copy.honap) eltelt_nap = date1_copy.nap - date2_copy.nap;
	else if (date1_copy.ev==date2_copy.ev && date1_copy.honap > date2_copy.honap)
	{
		eltelt_nap =honap_napdb(date2_copy.honap,date2_copy.ev)-date2_copy.nap;
		for (int koztes_honapok = date2_copy.honap + 1; koztes_honapok < date1_copy.honap; koztes_honapok++)
		   eltelt_nap += honap_napdb(koztes_honapok,date2_copy.ev);
		eltelt_nap += date1_copy.nap;
	}
	else
	{
		eltelt_nap = honap_napdb(date2_copy.honap,date2_copy.ev) - date2_copy.nap;
		for (int honap2_utan = date2_copy.honap + 1; honap2_utan < 13; honap2_utan++)
			eltelt_nap += honap_napdb(honap2_utan,date2_copy.ev);
		for (int koztes_evek = date2_copy.ev + 1; koztes_evek < date1_copy.ev; koztes_evek++)
			eltelt_nap += ev_napdb(koztes_evek);
		for (int honap1_elott = 1; honap1_elott < date1_copy.honap; honap1_elott++)
			eltelt_nap += honap_napdb(honap1_elott,date1_copy.ev);
		eltelt_nap += date1_copy.nap;
	}
	return eltelt_nap;
}

//Kiirja a  d�tumot param�terk�nt megadott kimenetre
//@param os- kimenet
void Datum::datum_kiir(std::ostream& os) const
{
	os << ev << "." << std::setw(2) << std::setfill('0') << honap << "."
		<< std::setw(2) << std::setfill('0') << nap <<std::setfill(' ')<< std::endl;
}

//A foglalt_esemenzek fileba csak az adatokat irjuk be a k�nnyebb olvas�s �rdek�ben.
void Datum::datum_kiir_beolvasashoz(std::ostream& os) const
{
    os<<ev<<std::endl;
    os<<honap<<std::endl;
    os<<nap<<std::endl;
}

//D�tum beolvas�sa
//@ param is- bemenet
//@param os-A kimenet amire, kiirjuk a felhaszn�l�nak, hogy milyen form�tumban v�rjuk az �rkezo adatokat.
void Datum::datum_beolvas(std::istream& is ,std::ostream& os)
{
	os << "Ird be a d�tumot(�v,h�nap,nap sorrendben)!"<<std::endl;
	is >> ev >> honap >> nap;
	Datum(ev, honap, nap);
	//Igy ellenorizve van az az eset is, ha a felhaszn�l� hib�s d�tumot irt be.
}
//A f�ggv�ny azt sz�molja ki, hogy egy napt�ri nap milyen napra esik.
// A het_napjai[7] tartalmazza a h�t napjainak neveit.
//A f�ggv�ny felhaszn�lja az eltelt napokat, 2025.04.21-hez k�pest .
//Az igy kapott sz�mnak 7-el val� oszt�si marad�ka egy i sz�mot ad meg.
//A het_napjai[i] t�riti vissza a megfelelo napot.
std::string Datum::milyen_napra_esik() const
{

	Datum mai_datum(2025, 4, 21);
	int napkkulonbseg = eltelt_napok(mai_datum) ;
	int het_napjai_sorszam = 0;
	if (*this >= mai_datum) het_napjai_sorszam = napkkulonbseg % 7;
	else het_napjai_sorszam = ((-napkkulonbseg % 7)+7)%7;//t�lcsordul�s elker�l�se miatt sz�ks�ges a m�sodik modulo 7.
	return het_napjai[het_napjai_sorszam];
}


