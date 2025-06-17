#pragma once
#include <iostream>
#include <string>
#include "Abs_Naptar.h"
#include "Datum.h"
#include "Honapos_Naptar.h"
#include "memtrace.h"
//Kivételosztály, amely az std::exceptionbol származik
//Elkapásnál így azt is ki lehet írni pontosan milyen kivétel jött.
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


	//Paraméteres konstruktor. A napok száma az év alapján számitható ki.
	Eves_Naptar(int ev=2025) :Abs_Naptar(),evszam(ev), osszes_nap(Datum::ev_napdb(ev)) {}

	//Az összes nap számával tér vissza. Az a szerepe, hogy ez publikusan is látható legyen.
	int capacity() const{
		return osszes_nap;
	}

	//Az éves naptár kiiratása.
    //param os- kimenet
    void kiir(std::ostream& os=std::cout ) const;


};

