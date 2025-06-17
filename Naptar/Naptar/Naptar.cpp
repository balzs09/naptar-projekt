// Naptar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <locale>
#include <iomanip>
#include <fstream>
#include "memtrace.h"
#include "Datum.h"
#include "Esemeny.h"
#include "Abs_Naptar.h"
#include "Eves_Naptar.h"
#include "Honapos_Naptar.h"
#include "gtest_lite.h"

#ifdef _WIN32
    #include <windows.h>
#endif
/*#define MEMTRACE*/
/*#define CPORTA*/
/*
//Kiv�teloszt�ly, amely az std::exceptionbol sz�rmazik
//Elkap�sn�l �gy azt is ki lehet �rni pontosan milyen kiv�tel j�tt.
class Gond_Van:public std::exception
{
private:
    std::string hiba_uzenet;
public:
	Gond_Van(const std::string& hiba):hiba_uzenet(hiba) {}
	const char* what() const noexcept override
	{
	    return hiba_uzenet.c_str();
	}
};*/
#ifdef CPORTA
//�zleti modell

int main()
{
    //D�tum konstruktorainak tesztel�se.
    //Kiv�teleket is ellen�rzi.
    //Az EXPECT_EQ �ltal az "==" oper�tor is ellen�rizve van. Az EXPECT_NE �ltal pedig a "!=" is.
	TEST(Datum,Konstruktorok)
	{
	    Datum d1;
	    Datum d2(2023,4,8);
	   //Hib�s h�nap
	    EXPECT_ANY_THROW(Datum(2002,67,7));
	    //Hib�s nap
	    EXPECT_ANY_THROW(Datum(2005,2,30));
	    EXPECT_NO_THROW(Datum(2023,4,9));
	    EXPECT_EQ(d2.getnap(),8);
	    Datum d3=d1;
	    EXPECT_EQ(d1,d3);
	    Datum d4;
	    d4=d2;
	    EXPECT_EQ(d4,d2);
	    EXPECT_NE(d4,d1);
	}END
	//D�tum rel�ci� jeles oper�torok ellen�rz�sei
	//Els� elem az a param�ter kell legyen amire igaz az �llit�s.
	TEST(Datum,Egyenlotlensegek)
	{
	    Datum d1;
        Datum d2(2023,4,8);
        Datum d3(2025,5,17);
	    EXPECT_GT(d1,d2);//nagyobb
	    EXPECT_LT(d1,d3);//kisebb
	    Datum d4=d1;
	    EXPECT_GE(d4,d1);//nagyobb vagy egyenl�
	    EXPECT_LE(d2,d4);//kisebb vagy egyenl�
	}END
	//Sz�k��vvel, h�napok �s �vek napjainak sz�m�val kapcsolatos f�ggv�nyek ellen�rz�se.
	TEST(Datum,Napokszama)
	{

        EXPECT_TRUE(Datum::szokoev_e(2024));
        EXPECT_FALSE(Datum::szokoev_e(2022));
        EXPECT_EQ(Datum::ev_napdb(2016),366);
        EXPECT_EQ(Datum::ev_napdb(2100),365);
        EXPECT_EQ(Datum::honap_napdb(2,2024),29);
        EXPECT_EQ(Datum::honap_napdb(9,30),30);

	}END
	//Els� n�gy teszt az eltelt napok sz�m�nak ellen�rz�s�t biztositja.
	//A k�vetkez�k pedig azt ,hogy milyen napra esik egy d�tum.
	TEST(Datum,Elteltnap)
	{
        Datum d1;
        Datum d2(2023,4,8);
        Datum d3(2024,2,29);
        Datum d4(2025,2,10);
        EXPECT_EQ(40,d1.eltelt_napok(d4));
        EXPECT_EQ(307,d1.eltelt_napok(d3));
        EXPECT_EQ(307,d3.eltelt_napok(d1));
        EXPECT_EQ(674,d2.eltelt_napok(d4));
        EXPECT_TRUE("szerda"==d1.milyen_napra_esik());
        EXPECT_FALSE("Szerda"==d1.milyen_napra_esik());
        EXPECT_TRUE("h�tf�"==d4.milyen_napra_esik());
	}END
    //Esem�ny konstruktorainak �s "==","!=" oper�torainak m�k�d�s�nek ellen�rz�se
    TEST(Esemeny,Konstruktorok)
    {
        Esemeny e1;
        Esemeny e2("HF lead�s",iskolai,Datum(2025,05,18));
        Esemeny e3=e2;
        Esemeny e4;
        e4=e1;
        Esemeny e5("�j�v",globalis,Datum(2025,1,1));
        EXPECT_EQ(e3,e2);
        EXPECT_EQ(e4,e1);
        EXPECT_EQ(e5,e1);
        EXPECT_NE(e3,e5);
        EXPECT_EQ(e4,e5);
    }END
    //Az esem�ny oszt�ly D�tum getter f�ggv�ny�nek �s a sztringet tipuss� �talakit� f�ggv�ny ellen�rz�se.
    TEST(Esemeny,DatumTipus)
    {
        Esemeny e1;
        Datum d1(2025,05,18);
        Esemeny e2("HF lead�s",iskolai,d1);
        EXPECT_EQ(d1,e2.get_lefoglalt_datum());
        EXPECT_TRUE("iskolai"==e2.tipus_to_string());
        EXPECT_FALSE("globalis"==e1.tipus_to_string());
        EXPECT_TRUE("glob�lis"==e1.tipus_to_string());
    }END

    //Az Abs_Naptar sz�rmaztatott oszt�lyainak konstruktorainak ellenorz�se .
    //Kiv�tel dob�s ellenorz�se.
    TEST(Abs_Naptar,Foglalas_Kivetelek)
    {

        Datum d1(2025,05,18);
        Esemeny holnapi_esemeny1("HF lead�s",iskolai,d1);
        Esemeny holnapi_esemeny2("rom�n eln�kv�laszt�s",globalis,Datum(2025,05,18));
        Honapos_Naptar a0;
        Eves_Naptar a1;
        EXPECT_NO_THROW(a0.foglalas<Gond_Van>(holnapi_esemeny1));
        EXPECT_ANY_THROW(a0.foglalas<Gond_Van>(holnapi_esemeny2));
        EXPECT_NO_THROW(a1.foglalas<Gond_Van>(holnapi_esemeny2));


    }END
    //A foglal�s helyes m�k�d�se.
    //Lefoglal egy esem�nyt majd ellen�rzi, hogy az j� helyre ker�lt a t�mbben
    TEST(Abs_Naptar,Foglalas)
    {
         Datum d1(2025,05,18);
         Esemeny esemeny1("HF lead�s",iskolai,d1);
         Esemeny esemeny2("sz�linap",maganeleti,Datum(2025,4,9));
         Esemeny esemeny3("konferencia",munkahelyi,Datum(2025,4,19));
         Esemeny esemeny4("Prog ZH2",iskolai,Datum(2025,5,20));
         Honapos_Naptar h0;
         h0.foglalas<Gond_Van>(esemeny1);
         h0.foglalas<Gond_Van>(esemeny2);
         h0.foglalas<Gond_Van>(esemeny3);
         h0.foglalas<Gond_Van>(esemeny4);
         EXPECT_EQ(esemeny4,h0.getesemeny<Gond_Van>(4));
         EXPECT_NE(esemeny1,h0.getesemeny<Gond_Van>(1));
         EXPECT_EQ(esemeny1,h0.getesemeny<Gond_Van>(3));
         EXPECT_EQ(esemeny2,h0.getesemeny<Gond_Van>(1));
         EXPECT_EQ(esemeny3,h0.getesemeny<Gond_Van>(2));
    }END
    //A t�rl�s funkci� helyes m�k�d�s�nek tesztel�se
    //A foglalt_e f�ggv�nnyel ellenorzi, hogy a d�tum t�r�lve lett-e.
	TEST(Abs_Naptar,Torles)
	{

	     Datum d1(2025,05,18);
         Esemeny esemeny1("HF lead�s",iskolai,d1);
         Esemeny esemeny2("sz�linap",maganeleti,Datum(2025,4,9));
         Esemeny esemeny3("konferencia",munkahelyi,Datum(2025,4,19));
         Esemeny esemeny4("Prog ZH2",iskolai,Datum(2025,5,20));
         Eves_Naptar e0;
         e0.foglalas<Gond_Van>(esemeny1);
         e0.foglalas<Gond_Van>(esemeny2);
         e0.foglalas<Gond_Van>(esemeny3);
         e0.torles<Gond_Van>(esemeny2);
         EXPECT_FALSE(e0.foglalt_e(Datum(2025,4,9)));
         EXPECT_TRUE(e0.foglalt_e(d1));
         EXPECT_EQ(esemeny3,e0.getesemeny<Gond_Van>(1));//Annak ellen�rz�se, hogy helyesen megt�rt�nt a cs�sztat�s t�rl�s ut�n.
         EXPECT_ANY_THROW((e0.torles<Gond_Van>(esemeny4)));

	}END
	//Annak ellen�rz�se, hogy a DatumEsemenye f�ggv�ny helyesen m�k�dik
	//Ha lefoglalunk egy esem�nyt, a d�tum megad�s�val meg kell kapni az adott esem�nyt.
	TEST(Abs_Naptar,EsemenyDatumbol)
	{
	     Datum d1(2025,05,18);
         Esemeny esemeny1("HF lead�s",iskolai,d1);
         Esemeny esemeny2("sz�linap",maganeleti,Datum(2025,4,9));
         Eves_Naptar e0;
         e0.foglalas<Gond_Van>(esemeny1);
         e0.foglalas<Gond_Van>(esemeny2);
         EXPECT_EQ(esemeny1,e0.Datum_Esemenye<Gond_Van>(d1));
         EXPECT_NE(esemeny1,e0.Datum_Esemenye<Gond_Van>(Datum(2025,4,9)));
         EXPECT_EQ(esemeny2,e0.Datum_Esemenye<Gond_Van>(Datum(2025,4,9)));
         EXPECT_ANY_THROW((e0.Datum_Esemenye<Gond_Van>(Datum(2021,2,3))));
	}END
	//A helyes �sszes nap m�k�d�se az �ves napt�r oszt�lyban
	TEST(Eves_Naptar,OsszesNapEv)
	{
	    Eves_Naptar idei_ev;
	    Eves_Naptar mult_ev(2024);
	    Eves_Naptar jovo_ev(2026);
	    EXPECT_EQ(365,idei_ev.capacity());
	    EXPECT_EQ(366,mult_ev.capacity());
	    EXPECT_NE(366,jovo_ev.capacity());
	}END
	//A helyes �sszes nap m�k�d�se a h�napos napt�r oszt�llyban
	TEST(Honapos_Naptar,OsszesNapHonap)
	{
	    Honapos_Naptar idei_januar;
	    Honapos_Naptar idei_aprilis(4,2025);
	    Honapos_Naptar tavaly_februar(2,2024);
	    Honapos_Naptar idei_oktober(10,2025);
	    EXPECT_EQ(31,idei_januar.capacity());
	    EXPECT_EQ(29,tavaly_februar.capacity());
	    EXPECT_EQ(30,idei_aprilis.capacity());
	    EXPECT_NE(30,idei_oktober.capacity());
	}END
	//Annak vizsg�lata, hogy helyesen meg�llapithat�, hogy egy h�nap kezdete milyen napra esik.
	TEST(Honapos_Naptar,KezdoNap)
	{
	    Honapos_Naptar idei_januar;
	    Honapos_Naptar idei_aprilis(4,2025);
	    Honapos_Naptar tavaly_februar(2,2024);
	    EXPECT_EQ(2,idei_januar.het_kezdo_nap(Datum(2025,1,1)));
        EXPECT_EQ(1,idei_aprilis.het_kezdo_nap(Datum(2025,4,1)));
        EXPECT_NE(4,tavaly_februar.het_kezdo_nap(Datum(2024,2,1)));
	}END
}
#else
//IO modell


//Ez a f�ggv�ny felhaszn�lhat� a f�jlb�l beolvas�s �s f�jlba ki�r�s megval�s�t�s�ra.
//Tesztel�si funkci�ja van, bemutatja a beolvas� �s kiir� f�ggv�nyek m�k�d�s�t.
std::ostream& teszt_beolvasas_kiiras(std::istream& isf,std::ostream& osf)
{
    Datum mai_datum;
    std::ostringstream alkiiro;//Ebben az esetben nem sz�ks�ges a kiir�s ez�rt van haszn�lva egy n�ma output.
    mai_datum.datum_beolvas(isf,alkiiro);
    mai_datum.datum_kiir(osf);
    osf<<std::endl;
    int honapszam, evszam,esemeny_db;
    isf>>honapszam;
    isf>>evszam;
    isf>>esemeny_db;
    Honapos_Naptar h1(honapszam,evszam);
    Eves_Naptar e1(evszam);
    for(int i=0;i<esemeny_db;i++)
    {
        Esemeny esi;
        esi.esemeny_beolvas(isf,alkiiro);
        h1.foglalas<Gond_Van>(esi);
        e1.foglalas<Gond_Van>(esi);
    }
    h1.lefoglaltak_kiir(osf);
    h1.kiir(osf);
    e1.kiir(osf);
    return osf;
}

//Abban az esetben ha a felhaszn�l� szeretn� l�tni a napt�r kiir�sa k�l�n-k�l�n a lefoglalt esem�nyeket d�tum szerint, erre is lehet�s�ge van.
void foglalt_esemeny_kiiratas(std::fstream& fs)
{
    std::cout<<"Azok a d�tumok foglaltak amik el�tt �s ut�n * van.Szeretn�d l�tni valamelyik d�tum lefoglalt esem�ny�t? Igen(I) vagy nem(N)"<<std::endl;
    char szeretne_e;
    std::cin>>szeretne_e;
    Honapos_Naptar seged_naptar;
    if(szeretne_e=='I')
       seged_naptar.foglalas_olvasas_file<Gond_Van>(fs);
    while(szeretne_e=='I')
    {
        std::cout<<"Milyen d�tumon l�v� esem�nyt szeretn�l l�tni( olyat �rj ami le van foglalva) ?"<<std::endl;
        Datum lefoglalt_datum;
        lefoglalt_datum.datum_beolvas(std::cin);
        Esemeny ekkor_foglalt_esemeny=seged_naptar.Datum_Esemenye<Gond_Van>(lefoglalt_datum);
        ekkor_foglalt_esemeny.esemeny_kiir();
        std::cout<<"Szeretn�l m�s esem�nyt is l�tni(I vagy N)?"<<std::endl;
        std::cin>>szeretne_e;
    }
}
//A felhaszn�l� �ltal k�v�nt napt�r kiirhat�.
void naptar_kiiratas(std::fstream& fs)
{
    std::cout<<"Milyen napt�rt szeretn�l kiiratni? �vest(E) vagy h�napost(H)?"<<std::endl;
    char naptar_tipus;
    std::cin>>naptar_tipus;
    while(naptar_tipus!='E'&&naptar_tipus!='H')
    {
        std::cout<<"Rossz bet�t �rt�l be. E vagy H kell legyen"<<std::endl;
        std::cin>>naptar_tipus;
    }
    if(naptar_tipus=='E')
    {
        int evszam;
        std::cout<<"Milyen �vet szeretn�l l�tni? �rd be az �vsz�mot!"<<std::endl;
        std::cin>>evszam;
        Eves_Naptar kiirando_ev(evszam);
        kiirando_ev.foglalas_olvasas_file<Gond_Van>(fs);
        kiirando_ev.kiir();
    }
    if(naptar_tipus=='H')
    {
        int evszam, honap_sorszam;
        std::cout<<"Milyen h�napot szeretn�l l�tni? �rd be el�sz�r �vsz�mot, majd a h�nap sorsz�m�t!"<<std::endl;
        std::cin>>evszam;
        std::cin>>honap_sorszam;
        Honapos_Naptar kiirando_honap(honap_sorszam,evszam);
        kiirando_honap.foglalas_olvasas_file<Gond_Van>(fs);
        kiirando_honap.kiir();
    }
    fs.clear();
    fs.seekg(0);
    foglalt_esemeny_kiiratas(fs);
}


int main()
{
    setlocale(LC_ALL, "");
    #ifdef _WIN32
     SetConsoleCP(1250);
   SetConsoleOutputCP(1250);
    #endif
	try{
      //F�jlb�l beolvas�s �s f�jlba kiir�s tesztel�s
	   std::ifstream test_beolvasas("Beolvaso_Teszt.txt");
	     std::ofstream test_kiiras("Kiiro_Teszt.txt");
	     if (!test_beolvasas) {
         throw std::runtime_error("Nem siker�lt megnyitni a beolvas� f�jlt!");
        }
        if (!test_kiiras) {
        throw std::runtime_error("Nem siker�lt megnyitni a ki�r� f�jlt!");
        }
	   teszt_beolvasas_kiiras(test_beolvasas,test_kiiras);
	   test_beolvasas.close();
	   test_kiiras.close();
     //Felhaszn�l�i alkalmaz�s
       std::fstream foglalt_esemenyekf("foglalt_esemenyek.txt",std::ios::in |std::ios::out);
       if(!foglalt_esemenyekf)
        {
            throw std::runtime_error("Nem siker�lt megnyitni a ki�r� f�jlt!");
        }
	   std::cout<<"Mit szeretn�l csin�lni? ";
	   std::cout<<" Napt�rat kiiratni(N), esem�nyt foglalni(F), esem�nyt t�r�lni(T), az �sszes foglalt esem�nyt l�tni(O) vagy kil�pni(K)?"<<std::endl;
       char funkcio_valasztas;
       std::cin>>funkcio_valasztas;
       while(funkcio_valasztas!='K')
       {
            //A f�jl vissza�ll�t�sa az elej�re olvas�shoz.
            foglalt_esemenyekf.clear();
            foglalt_esemenyekf.seekg(0);
            Honapos_Naptar seged_naptar;
            seged_naptar.foglalas_olvasas_file<Gond_Van>(foglalt_esemenyekf);
           switch(funkcio_valasztas)
           {
           case 'O':
              seged_naptar.lefoglaltak_kiir();
              break;
           case 'F':{
              foglalt_esemenyekf.clear();
              foglalt_esemenyekf.seekp(0, std::ios::end);//A pozici�t a f�jl v�g�re �ll�tja �r�shoz.
              Esemeny foglalando_esemeny;
              foglalando_esemeny.esemeny_beolvas();
              seged_naptar.foglalas<Gond_Van>(foglalando_esemeny);
              foglalando_esemeny.esemeny_kiir_beolvasashoz(foglalt_esemenyekf);
              break;
           }
           case 'N':
            foglalt_esemenyekf.clear();
            foglalt_esemenyekf.seekg(0);
            naptar_kiiratas(foglalt_esemenyekf);
            break;
           case 'T':{
               //A t�r�lt esem�nyt a f�jlb�l is t�r�lj�k.
               //Ezt �gy val�s�tsuk be, hogy a napt�rban t�rl�s ut�n, az �j esem�nylist�t �rjuk be a f�jlba.
              Esemeny foglalando_esemeny;
              foglalando_esemeny.esemeny_beolvas();
              seged_naptar.torles<Gond_Van>(foglalando_esemeny);
              foglalt_esemenyekf.close();
              foglalt_esemenyekf.open("foglalt_esemenyek.txt", std::ios::out | std::ios::trunc);//t�rl�s �rdek�ben kinyit�s
              seged_naptar.lefoglaltak_kiir_olvasashoz(foglalt_esemenyekf);
              foglalt_esemenyekf.close();
              foglalt_esemenyekf.open("foglalt_esemenyek.txt", std::ios::in | std::ios::out|std::ios::app);
              break;
           }

           default:
           std::cout<<"Rosz bet�t �rt�l be.";
       }

           std::cout<<"Mit szeretn�l k�vetkez�nek csin�lni?";
           std::cout<<" Napt�rat kiiratni(N), esem�nyt foglalni(F), esem�nyt t�r�lni(T), az �sszes foglalt esem�nyt l�tni(O) vagy kil�pni(K)?"<<std::endl;
           std::cin>>funkcio_valasztas;
       }
       foglalt_esemenyekf.close();

	}
	catch (Gond_Van& e) {
	std::cerr << "Saj�t kivetel jott"<<e.what()<<std:: endl;
    }
    catch (std::exception& e) {
	std::cerr << e.what() <<std:: endl;
    }

    catch (...) {
	std::cerr << "*** Nagy baj van! ****" <<std::endl;
    }
return 0;
}
   #endif // CPORTA


