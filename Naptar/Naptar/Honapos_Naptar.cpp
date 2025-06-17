#include "Honapos_Naptar.h"
#include "Datum.h"
#include <string>
#include <iostream>
#include <iomanip> //A naptár megfelelo kiiratásához szükséges.

//A hónapok elnevezéseinek definiálása.
 std::string Honapos_Naptar:: honapok[] =
{ "Január","Február","Március","Április","Május","Június","Július","Augusztus","Szeptember","Október","November","December" };

 //Megadja azt a napot ahonnan kezdodik az adott hónap
 //@param date1- A hónap elso napjának dátuma.
 int Honapos_Naptar::het_kezdo_nap(const Datum& date1) const
 {
	 for (int i = 0; i < 7; i++)
	 {
		 if (Datum::het_napjai[i] == date1.milyen_napra_esik()) return i;
	 }
	 return 0;
 }

 //A hónap és a hét napjai kiiratása.
 void Honapos_Naptar::honap_het_kiir(std::ostream& os) const
 {
	 for (int i = 0; i < 7; i++)
		 os << std::setw(15) << Datum::het_napjai[i] << " ";
	 os << std::endl << std::endl;
 }
 // A napok kiiratása.
 // Azok a napok amik le vannak foglalva valamilyen esemény által "*"nap"*" jelölést kapnak.
 void Honapos_Naptar::nap_kiir(std::ostream& os,Datum& date1) const
 {
	 if (foglalt_e(date1) == true)
		 os << std::setw(13) << "*" << std::setw(2) << std::setfill('0') << date1.getnap() << std::setfill(' ') << "*";
	 else os << std::setw(13) << " " << std::setw(2) << std::setfill('0') << date1.getnap()<< std::setfill(' ') << " ";
 }
 // A hónapos naptár kiiratása.
 // A honap_het_kiir és nap_kiir függvények használatával rendezetteb lesz a fokiiró függvény.
 // Manipulátorok használatával érheto el, hogy rendezett legyen a naptár.
 // Azokon a napokon amik nem tartoznak a hónapba üres napok kerülnek(a hónap kezdete elotti napok).
 // @param os- kimenet
 void Honapos_Naptar::kiir(std::ostream& os) const
 {
	 int elseje_het_sorszam = het_kezdo_nap(Datum(evszam, honap_sorszam, 1));
	 os << std::setw(55) << evszam <<"."<<megnevezes<< std::endl << std::endl<<std::endl;
	 honap_het_kiir(os);
	 for(int i=0;i<elseje_het_sorszam;i++) os << std::setw(16) << " ";
	 int nap_sorszam = 1;
	 while (nap_sorszam!=osszes_nap+1)
	 {
	     Datum napi_datum(evszam,honap_sorszam,nap_sorszam);
		 nap_kiir(os, napi_datum);
		 nap_sorszam++;
		 elseje_het_sorszam++;
		 if (elseje_het_sorszam == 7) {
			 elseje_het_sorszam = 0;
			 os << std::endl<<std::endl;
		 }
	 }
	 os << std::endl << std::endl << std::endl;
 }


