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

	//A hét napjainak elnevezésnek deklarálása. Szükség van más osztályban is rá, ezért publikus.
	static std::string het_napjai[7];
	//Parameter nélküli konstruktor. Beallitja a dátumot az idei év elso napjára.
	Datum()
	{

		ev = 2025;
		honap = 1;
		nap = 1;
	}

	//Paraméteres konstruktor .
	//Ha nem megfelelo a hónap vagy nap paramétere std::out_of_range hibaüzenetet dob.
	Datum(int year, int month, int day)  {
		if (month < 1 || month>12)
		{
			throw std::out_of_range("Nincs ennyi hónap. 1 és 12 között kell legyen.");
		}
		int max_nap_db = honap_napdb(month, year);
		if (day<1 || day>max_nap_db )
		{
			std::ostringstream oss;
			oss<<"Nincs ennyi nap ebben a hónapban. A napok száma 1 és "<< max_nap_db << " kell legyen.";
			throw std::out_of_range(oss.str());
		}
		ev = year;
		honap = month;
		nap = day;
	};

	//Másoló konstruktor.
	Datum(const Datum& date)
	{
		ev = date.ev;
		honap = date.honap;
		nap = date.nap;
	}

	//Értékadó operátor.
	Datum& operator=(const Datum& date)
	{
		if (this != &date) {
			ev = date.ev;
			honap = date.honap;
			nap = date.nap;
		}
		return *this;
	}
	//A naptár kiiratásnál szükség van a napra.
	int getnap() const{
		return nap;
	}
	//Két dátum összehasonlitása. Akkor tér vissza igaz értékkel a függvény ha az elso dátum a nagyobb.
	bool operator>(const Datum& hasonlitando_date) const;

	//Két dátum közötti egyenloségnek vizsgálata. Igaz értékkel tér vissza, ha a dátumok egyenloek, hamissal más esetben.
	bool operator==(const Datum& hasonlitando_date) const;

	//Két dátum közötti eltérésnek vizsgálata.
	//Kisebb reláció vizsgálata dátumok közott.
	// Megvalósitásához a korábban megvalósitott az "operator>" és "operator=" tagfüggvények is fel vannak használva.
	bool operator<(const Datum& hasonlitando_date) const;

	//Kisebb vagy egyenloség vizsgálata dátumok között.
	//A  kisebb operátor és egyenloség felhasználásával, ha egyik igaz igaz értékkel tér vissza, más esetben hamis értékkel.
	bool operator<=(const Datum& hasonlitando_date) const;

	//nagyobb vagy egyenloség vizsgálata dátumok között.
	//A  nagyobb operátor és egyenloség felhasználásával, ha egyik igaz igaz értékkel tér vissza, más esetben hamis értékkel.
	bool operator>=(const Datum& hasonlitando_date) const;

	//Két dátum közötti eltérésnek vizsgálata. Az "==" operátor van felhasználva hozzá
    bool operator!=(const Datum& hasonlitando_date) const;

	//Vizsgálja, hogy az adott év szökoév-e vagy sem.
    // true értékkel tér vissza, ha a dátum éve szökoévre esik, false értékkel más esetben.
	//@param jelenlegi_ev- A vizsgálandó év
	//statikus, hogy más osztályban is lehetséges legyen dátum objektum nélkül használni.
	static bool szokoev_e(int jelenlegi_ev) ;

	//Azt vizsgálja egy évben hány nap van.
	// A szokoev_e függvényt használja fel, 366-ot térit vissza szökoév esetén, 365-öt ha nincs szökoév.
	//@param jelenlegi_ev- A vizsgálandó év
	//statikus, hogy más osztályban is lehetséges legyen dátum objektum nélkül használni.
	static int ev_napdb(int jelenlegi_ev) ;

	//Megkeresi a dátumban hány napból áll az adott hónap. A szökoéveket is számitásba veszi
    //A hónapban lévo napok számával tér vissza, egész értékkel
	//@param jelenlegi_honap- A vizsgálandó hónap
	//@param jelenlegi_ev- A hónaphoz tartozó év amelyrol ellenorizni kell februári hónap esetén,hogy szökoévre esik.
	//statikus, hogy más osztályban is lehetséges legyen dátum objektum nélkül használni.
	static int honap_napdb(int jelenlegi_honap, int jelenlegi_ev) ;

	//Két dátum között eltelt nap kiszámitása.
	// Az eltelt napok számával tér vissza.
	int eltelt_napok(const Datum& date2) const;

	//Kiirja a paraméterként kapott dátumot a másik paraméterként megadott kimenetre
    //@param os- kimenet
	void datum_kiir(std::ostream& os=std::cout) const;

	//A foglalt_esemenyek fileba csak az adatokat irjuk be a könnyebb olvasás érdekében.
    void datum_kiir_beolvasashoz(std::ostream& os=std::cout) const;

	//Dátum beolvasása
	//@param is- bemenet
	void datum_beolvas(std::istream& is = std::cin,std::ostream& os=std::cout);

	//A függvény azt számolja ki, hogy egy naptári nap milyen napra esik.
	// A het_napjai[7] tartalmazza a hét napjainak neveit.
	//A függvény felhasználja az eltelt napokat, 2025.04.21-hez képest .
	//Az igy kapott számnak 7-el való osztási maradéka egy i számot ad meg.
	//A het_napjai[i] tériti vissza a megfelelo napot.
	std::string milyen_napra_esik() const;

};
//Dátum kiiratása operator<< segitségével.
//@param os-kimenet, @param datum1- kiirandó dátum.
inline std::ostream& operator<<(std::ostream& os, const Datum& datum1)
{
	datum1.datum_kiir(os);
	return os;
}
