#include "Eves_Naptar.h"
#include <iostream>

//Megvizsgalja, hogy egy �v sz�k��v-e vagy sem.
//A napok sz�m�val az �vben t�r vissza.
template<typename T,class E>
 size_t Eves_Naptar<T,E>::nap_db_evben(int ev) 
{
	if (ev % 4 == 0) return 366;
	else return 365;
}
