#pragma once
#include <iostream>
#include "Abs_Naptar.h"
#include <string>

//A T a dinamikusan foglalt ter�letet jelenti. Ez lehet esem�ny vagy d�tum is.

class Honapos_Naptar :public Abs_Naptar
{
private:
	static  std::string honapok[12];

	int honap_sorszam;
	std::string megnevezes;
	int evszam;
	int osszes_nap;
public:
	//Az Abs_Naptar �ltal �r�k�lt tagv�ltoz�k param�terekkel,
	// a Honapos_Naptar saj�t tagv�ltoz�i default megval�sitott konstruktor.
	Honapos_Naptar(int sorszam=1, int ev=2025)
		:Abs_Naptar()
	{
		//Annak ellenorz�se �rdek�ben, hogy 1 �s 12 k�z�tti �rt�k a sorsz�m.
		Datum(ev, sorszam, 1);
		honap_sorszam = sorszam;
		megnevezes = honapok[sorszam - 1];
		evszam = ev;
		osszes_nap = Datum::honap_napdb(sorszam, ev);
	}

	//Az �sszes nap sz�m�val t�r vissza. Az a szerepe, hogy ez publikusan is l�that� legyen.
	int capacity() const{
		return osszes_nap;
	}

	//Megadja azt a napot ahonnan kezdodik az adott h�nap
	//@param date1- A h�nap elso napj�nak d�tuma.
	int het_kezdo_nap(const Datum& date1) const;


	//A h�nap �s a h�t napjai kiirat�sa.
	void honap_het_kiir(std::ostream& os) const;

	// A napok kiirat�sa.
	// Azok a napok amik le vannak foglalva valamilyen esem�ny �ltal "*"nap"*" jel�l�st kapnak.
	void nap_kiir(std::ostream& os, Datum& date1) const;

	//A h�napos napt�r kiirat�sa.
	//param os- kimenet
	void kiir(std::ostream& os = std::cout) const;

};

