#pragma once
#include <iostream>
#include <string>
#include "Abs_Naptar.h"
#include "Datum.h"
#include "Honapos_Naptar.h"
#include "memtrace.h"
//Kiv�teloszt�ly, amely az std::exceptionbol sz�rmazik
//Elkap�sn�l �gy azt is ki lehet �rni pontosan milyen kiv�tel j�tt.
class Gond_Van:public std::runtime_error
{
public:
	explicit Gond_Van(const std::string& hibauzenet) :runtime_error(hibauzenet){}
};
class Eves_Naptar:public Abs_Naptar
{
private:
	int evszam;
	int osszes_nap;
public:


	//Param�teres konstruktor. A napok sz�ma az �v alapj�n sz�mithat� ki.
	Eves_Naptar(int ev=2025) :Abs_Naptar(),evszam(ev), osszes_nap(Datum::ev_napdb(ev)) {}

	//Az �sszes nap sz�m�val t�r vissza. Az a szerepe, hogy ez publikusan is l�that� legyen.
	int capacity() const{
		return osszes_nap;
	}

	//Az �ves napt�r kiirat�sa.
    //param os- kimenet
    void kiir(std::ostream& os=std::cout ) const;


};

