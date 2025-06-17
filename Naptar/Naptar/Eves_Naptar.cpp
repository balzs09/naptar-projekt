#include <iostream>
#include <iomanip>
#include "Eves_Naptar.h"
#include "Honapos_Naptar.h"
#include "Abs_Naptar.h"

//Az éves naptár kiiratása.
// Eloször az évszám kerül kiiratásra
// Ezután minden hónapot kiiratjuk a hónapos naptár osztályban megvalósitott függvény által.
//param os- kimenet
void Eves_Naptar::kiir(std::ostream& os ) const
    {
      os<<std::setw(60)<<evszam<<std::endl<<std::endl<<std::endl;
	  for (int i = 1; i < 13; i++)
	  {
		Honapos_Naptar honap_i( i, evszam);
		for(size_t j=0;j<lefoglalt_napok_szama;j++)
            honap_i.foglalas<Gond_Van>(lefoglalt_esemenyek[j]);
		honap_i.kiir(os);
	  }
	os<<std::endl<<std::endl<<std::endl;
   }
