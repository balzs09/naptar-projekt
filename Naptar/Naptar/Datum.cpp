#include "Datum.h"
#include <iostream>
#include <iomanip>//A dátum kiiratáshoz szükséges manipulátorokat is használni.
#include <string>


//A hét napjai definiálása
 std::string Datum:: het_napjai[] = { "hétfõ","kedd","szerda","csütörtök","péntek","szombat","vasárnap" };

//Két dátum összehasonlitása. Akkor tér vissza igaz értékkel a függvény ha az elso dátum a nagyobb.
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

//Két dátum közötti egyenloségnek vizsgálata. Igaz értékkel tér vissza, ha a dátumok egyenloek, hamissal más esetben.
bool Datum::operator==(const Datum& hasonlitando_date) const
{
	if (ev == hasonlitando_date.ev && honap == hasonlitando_date.honap && nap == hasonlitando_date.nap) return true;
	return false;
}

//Kisebb reláció vizsgálata dátumok közott.
// Megvalósitásához a korábban megvalósitott az "operator<" és "operator=" tagfüggvények is fel vannak használva.
bool Datum::operator<(const Datum& hasonlitando_date) const
{
	if (!(*this > hasonlitando_date) && !(*this == hasonlitando_date)) return true;
	return false;
}

//Kisebb vagy egyenloség vizsgálata dátumok között.
//A  kisebb operátor és egyenloség felhasználásával, ha egyik igaz igaz értékkel tér vissza, más esetben hamis értékkel.
bool Datum::operator<=(const Datum& hasonlitando_date) const
{
	if((*this<hasonlitando_date)||(*this==hasonlitando_date)) return true;
	return false;
}

//nagyobb vagy egyenloség vizsgálata dátumok között.
//A  nagyobb operátor és egyenloség felhasználásával, ha egyik igaz igaz értékkel tér vissza, más esetben hamis értékkel.
bool Datum::operator>=(const Datum& hasonlitando_date) const
{
	if ((*this > hasonlitando_date) || (*this == hasonlitando_date)) return true;
	return false;
}

//Két dátum közötti eltérésnek vizsgálata. Az "==" operátor van felhasználva hozzá
bool Datum::operator!=(const Datum& hasonlitando_date) const
{
    return !(*this==hasonlitando_date);
}
//Vizsgálja, hogy az adott év szökoév-e vagy sem.
// true értékkel tér vissza, ha a dátum éve szökoévre esik, false értékkel más esetben.
//param jelenlegi_ev- A vizsgálandó év
 bool Datum::szokoev_e(int jelenlegi_ev)
{
	if ((jelenlegi_ev % 4 == 0&&jelenlegi_ev%100!=0)||(jelenlegi_ev%400==0)) return true;
	else return false;
}

//Azt vizsgálja egy évben hány nap van.
// A szokoev_e függvényt használja fel, 366-ot térit vissza szökoév esetén, 365-öt ha nincs szökoév.
//@param jelenlegi_ev- A vizsgálandó év
int Datum::ev_napdb(int jelenlegi_ev)
{
	if (szokoev_e(jelenlegi_ev)) return 366;
	else return 365;
}
//Megkeresi a dátumban hány napból áll az adott hónap. A szökoéveket is számitásba veszi
//A hónapban lévo napok számával tér vissza, egész értékkel
//Eloször ellenorzi, hogy 31 napos-e a hónap, majd ,hogy 30 napos se.
//Ha egyik se, a hónap február, azt kell ellenorizni, hogy szökoév van vagy sem
//@param jelenlegi_honap- A vizsgálandó hónap
//@param jelenlegi_ev- A hónaphoz tartozó év amelyrol ellenörizni kell februári hónap esetén,hogy szökoévre esik.
int Datum::honap_napdb(int jelenlegi_honap,int jelenlegi_ev)
{
	if ((jelenlegi_honap < 8 && jelenlegi_honap % 2 == 1) || (jelenlegi_honap >= 8 && jelenlegi_honap % 2 == 0)) return 31;
	else if ((jelenlegi_honap > 2 && jelenlegi_honap % 2 == 0) || (jelenlegi_honap >= 9 && jelenlegi_honap % 2 == 1)) return 30;
	else if (szokoev_e(jelenlegi_ev)) return 29;
	else return 28;
}
//Két dátum között eltelt nap kiszámitása.
// Az eltelt napok számával tér vissza.
//A függvény eloszor azt az esetet ellenorzi, ahol csak a napok különböznek, ilyenkor ki kell vonni a nagyobb napból a kisebbiket.
//Ha a hónapok is különböznek, akkor a köztes hónapok napjai hozzáadódnak az összeghez.
//A kisebb hónapból a dátum napja utáni napok kerülnek be mig a nagyobb hónapból a dátum elottiek.
//Ha az évek különböznek is hasonló a megvalósitás. Ilyenkor bekerülnek a kisebb évben következendo hónapok, a nagyobban az elteltek.
//A köztes évek napjai is összeadódnak és a két hónap következendo és eltelt napja.
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

//Kiirja a  dátumot paraméterként megadott kimenetre
//@param os- kimenet
void Datum::datum_kiir(std::ostream& os) const
{
	os << ev << "." << std::setw(2) << std::setfill('0') << honap << "."
		<< std::setw(2) << std::setfill('0') << nap <<std::setfill(' ')<< std::endl;
}

//A foglalt_esemenzek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
void Datum::datum_kiir_beolvasashoz(std::ostream& os) const
{
    os<<ev<<std::endl;
    os<<honap<<std::endl;
    os<<nap<<std::endl;
}

//Dátum beolvasása
//@ param is- bemenet
//@param os-A kimenet amire, kiirjuk a felhasználónak, hogy milyen formátumban várjuk az érkezo adatokat.
void Datum::datum_beolvas(std::istream& is ,std::ostream& os)
{
	os << "Ird be a dátumot(év,hónap,nap sorrendben)!"<<std::endl;
	is >> ev >> honap >> nap;
	Datum(ev, honap, nap);
	//Igy ellenorizve van az az eset is, ha a felhasználó hibás dátumot irt be.
}
//A függvény azt számolja ki, hogy egy naptári nap milyen napra esik.
// A het_napjai[7] tartalmazza a hét napjainak neveit.
//A függvény felhasználja az eltelt napokat, 2025.04.21-hez képest .
//Az igy kapott számnak 7-el való osztási maradéka egy i számot ad meg.
//A het_napjai[i] tériti vissza a megfelelo napot.
std::string Datum::milyen_napra_esik() const
{

	Datum mai_datum(2025, 4, 21);
	int napkkulonbseg = eltelt_napok(mai_datum) ;
	int het_napjai_sorszam = 0;
	if (*this >= mai_datum) het_napjai_sorszam = napkkulonbseg % 7;
	else het_napjai_sorszam = ((-napkkulonbseg % 7)+7)%7;//túlcsordulás elkerülése miatt szükséges a második modulo 7.
	return het_napjai[het_napjai_sorszam];
}


