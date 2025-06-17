#include "Honapos_Naptar.h"
#include "Datum.h"
#include <string>
#include <iostream>
#include <iomanip> //A napt�r megfelelo kiirat�s�hoz sz�ks�ges.

//A h�napok elnevez�seinek defini�l�sa.
 std::string Honapos_Naptar:: honapok[] =
{ "Janu�r","Febru�r","M�rcius","�prilis","M�jus","J�nius","J�lius","Augusztus","Szeptember","Okt�ber","November","December" };

 //Megadja azt a napot ahonnan kezdodik az adott h�nap
 //@param date1- A h�nap elso napj�nak d�tuma.
 int Honapos_Naptar::het_kezdo_nap(const Datum& date1) const
 {
	 for (int i = 0; i < 7; i++)
	 {
		 if (Datum::het_napjai[i] == date1.milyen_napra_esik()) return i;
	 }
	 return 0;
 }

 //A h�nap �s a h�t napjai kiirat�sa.
 void Honapos_Naptar::honap_het_kiir(std::ostream& os) const
 {
	 for (int i = 0; i < 7; i++)
		 os << std::setw(15) << Datum::het_napjai[i] << " ";
	 os << std::endl << std::endl;
 }
 // A napok kiirat�sa.
 // Azok a napok amik le vannak foglalva valamilyen esem�ny �ltal "*"nap"*" jel�l�st kapnak.
 void Honapos_Naptar::nap_kiir(std::ostream& os,Datum& date1) const
 {
	 if (foglalt_e(date1) == true)
		 os << std::setw(13) << "*" << std::setw(2) << std::setfill('0') << date1.getnap() << std::setfill(' ') << "*";
	 else os << std::setw(13) << " " << std::setw(2) << std::setfill('0') << date1.getnap()<< std::setfill(' ') << " ";
 }
 // A h�napos napt�r kiirat�sa.
 // A honap_het_kiir �s nap_kiir f�ggv�nyek haszn�lat�val rendezetteb lesz a fokiir� f�ggv�ny.
 // Manipul�torok haszn�lat�val �rheto el, hogy rendezett legyen a napt�r.
 // Azokon a napokon amik nem tartoznak a h�napba �res napok ker�lnek(a h�nap kezdete elotti napok).
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


