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
//Kivételosztály, amely az std::exceptionbol származik
//Elkapásnál így azt is ki lehet írni pontosan milyen kivétel jött.
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
//üzleti modell

int main()
{
    //Dátum konstruktorainak tesztelése.
    //Kivételeket is ellenõrzi.
    //Az EXPECT_EQ által az "==" operátor is ellenõrizve van. Az EXPECT_NE által pedig a "!=" is.
	TEST(Datum,Konstruktorok)
	{
	    Datum d1;
	    Datum d2(2023,4,8);
	   //Hibás hónap
	    EXPECT_ANY_THROW(Datum(2002,67,7));
	    //Hibás nap
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
	//Dátum reláció jeles operátorok ellenõrzései
	//Elsõ elem az a paraméter kell legyen amire igaz az állitás.
	TEST(Datum,Egyenlotlensegek)
	{
	    Datum d1;
        Datum d2(2023,4,8);
        Datum d3(2025,5,17);
	    EXPECT_GT(d1,d2);//nagyobb
	    EXPECT_LT(d1,d3);//kisebb
	    Datum d4=d1;
	    EXPECT_GE(d4,d1);//nagyobb vagy egyenlõ
	    EXPECT_LE(d2,d4);//kisebb vagy egyenlõ
	}END
	//Szökõévvel, hónapok és évek napjainak számával kapcsolatos függvények ellenõrzése.
	TEST(Datum,Napokszama)
	{

        EXPECT_TRUE(Datum::szokoev_e(2024));
        EXPECT_FALSE(Datum::szokoev_e(2022));
        EXPECT_EQ(Datum::ev_napdb(2016),366);
        EXPECT_EQ(Datum::ev_napdb(2100),365);
        EXPECT_EQ(Datum::honap_napdb(2,2024),29);
        EXPECT_EQ(Datum::honap_napdb(9,30),30);

	}END
	//Elsõ négy teszt az eltelt napok számának ellenõrzését biztositja.
	//A következõk pedig azt ,hogy milyen napra esik egy dátum.
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
        EXPECT_TRUE("hétfõ"==d4.milyen_napra_esik());
	}END
    //Esemény konstruktorainak és "==","!=" operátorainak mûködésének ellenõrzése
    TEST(Esemeny,Konstruktorok)
    {
        Esemeny e1;
        Esemeny e2("HF leadás",iskolai,Datum(2025,05,18));
        Esemeny e3=e2;
        Esemeny e4;
        e4=e1;
        Esemeny e5("újév",globalis,Datum(2025,1,1));
        EXPECT_EQ(e3,e2);
        EXPECT_EQ(e4,e1);
        EXPECT_EQ(e5,e1);
        EXPECT_NE(e3,e5);
        EXPECT_EQ(e4,e5);
    }END
    //Az esemény osztály Dátum getter függvényének és a sztringet tipussá átalakitó függvény ellenõrzése.
    TEST(Esemeny,DatumTipus)
    {
        Esemeny e1;
        Datum d1(2025,05,18);
        Esemeny e2("HF leadás",iskolai,d1);
        EXPECT_EQ(d1,e2.get_lefoglalt_datum());
        EXPECT_TRUE("iskolai"==e2.tipus_to_string());
        EXPECT_FALSE("globalis"==e1.tipus_to_string());
        EXPECT_TRUE("globális"==e1.tipus_to_string());
    }END

    //Az Abs_Naptar származtatott osztályainak konstruktorainak ellenorzése .
    //Kivétel dobás ellenorzése.
    TEST(Abs_Naptar,Foglalas_Kivetelek)
    {

        Datum d1(2025,05,18);
        Esemeny holnapi_esemeny1("HF leadás",iskolai,d1);
        Esemeny holnapi_esemeny2("román elnökválasztás",globalis,Datum(2025,05,18));
        Honapos_Naptar a0;
        Eves_Naptar a1;
        EXPECT_NO_THROW(a0.foglalas<Gond_Van>(holnapi_esemeny1));
        EXPECT_ANY_THROW(a0.foglalas<Gond_Van>(holnapi_esemeny2));
        EXPECT_NO_THROW(a1.foglalas<Gond_Van>(holnapi_esemeny2));


    }END
    //A foglalás helyes mûködése.
    //Lefoglal egy eseményt majd ellenõrzi, hogy az jó helyre került a tömbben
    TEST(Abs_Naptar,Foglalas)
    {
         Datum d1(2025,05,18);
         Esemeny esemeny1("HF leadás",iskolai,d1);
         Esemeny esemeny2("szülinap",maganeleti,Datum(2025,4,9));
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
    //A törlés funkció helyes mûködésének tesztelése
    //A foglalt_e függvénnyel ellenorzi, hogy a dátum törölve lett-e.
	TEST(Abs_Naptar,Torles)
	{

	     Datum d1(2025,05,18);
         Esemeny esemeny1("HF leadás",iskolai,d1);
         Esemeny esemeny2("szülinap",maganeleti,Datum(2025,4,9));
         Esemeny esemeny3("konferencia",munkahelyi,Datum(2025,4,19));
         Esemeny esemeny4("Prog ZH2",iskolai,Datum(2025,5,20));
         Eves_Naptar e0;
         e0.foglalas<Gond_Van>(esemeny1);
         e0.foglalas<Gond_Van>(esemeny2);
         e0.foglalas<Gond_Van>(esemeny3);
         e0.torles<Gond_Van>(esemeny2);
         EXPECT_FALSE(e0.foglalt_e(Datum(2025,4,9)));
         EXPECT_TRUE(e0.foglalt_e(d1));
         EXPECT_EQ(esemeny3,e0.getesemeny<Gond_Van>(1));//Annak ellenõrzése, hogy helyesen megtörtént a csúsztatás törlés után.
         EXPECT_ANY_THROW((e0.torles<Gond_Van>(esemeny4)));

	}END
	//Annak ellenõrzése, hogy a DatumEsemenye függvény helyesen mûködik
	//Ha lefoglalunk egy eseményt, a dátum megadásával meg kell kapni az adott eseményt.
	TEST(Abs_Naptar,EsemenyDatumbol)
	{
	     Datum d1(2025,05,18);
         Esemeny esemeny1("HF leadás",iskolai,d1);
         Esemeny esemeny2("szülinap",maganeleti,Datum(2025,4,9));
         Eves_Naptar e0;
         e0.foglalas<Gond_Van>(esemeny1);
         e0.foglalas<Gond_Van>(esemeny2);
         EXPECT_EQ(esemeny1,e0.Datum_Esemenye<Gond_Van>(d1));
         EXPECT_NE(esemeny1,e0.Datum_Esemenye<Gond_Van>(Datum(2025,4,9)));
         EXPECT_EQ(esemeny2,e0.Datum_Esemenye<Gond_Van>(Datum(2025,4,9)));
         EXPECT_ANY_THROW((e0.Datum_Esemenye<Gond_Van>(Datum(2021,2,3))));
	}END
	//A helyes összes nap mûködése az éves naptár osztályban
	TEST(Eves_Naptar,OsszesNapEv)
	{
	    Eves_Naptar idei_ev;
	    Eves_Naptar mult_ev(2024);
	    Eves_Naptar jovo_ev(2026);
	    EXPECT_EQ(365,idei_ev.capacity());
	    EXPECT_EQ(366,mult_ev.capacity());
	    EXPECT_NE(366,jovo_ev.capacity());
	}END
	//A helyes összes nap mûködése a hónapos naptár osztállyban
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
	//Annak vizsgálata, hogy helyesen megállapitható, hogy egy hónap kezdete milyen napra esik.
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


//Ez a függvény felhasználható a fájlból beolvasás és fájlba kiírás megvalósítására.
//Tesztelési funkciója van, bemutatja a beolvasó és kiiró függvények mûködését.
std::ostream& teszt_beolvasas_kiiras(std::istream& isf,std::ostream& osf)
{
    Datum mai_datum;
    std::ostringstream alkiiro;//Ebben az esetben nem szükséges a kiirás ezért van használva egy néma output.
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

//Abban az esetben ha a felhasználó szeretné látni a naptár kiirása külön-külön a lefoglalt eseményeket dátum szerint, erre is lehetõsége van.
void foglalt_esemeny_kiiratas(std::fstream& fs)
{
    std::cout<<"Azok a dátumok foglaltak amik elõtt és után * van.Szeretnéd látni valamelyik dátum lefoglalt eseményét? Igen(I) vagy nem(N)"<<std::endl;
    char szeretne_e;
    std::cin>>szeretne_e;
    Honapos_Naptar seged_naptar;
    if(szeretne_e=='I')
       seged_naptar.foglalas_olvasas_file<Gond_Van>(fs);
    while(szeretne_e=='I')
    {
        std::cout<<"Milyen dátumon lévõ eseményt szeretnél látni( olyat írj ami le van foglalva) ?"<<std::endl;
        Datum lefoglalt_datum;
        lefoglalt_datum.datum_beolvas(std::cin);
        Esemeny ekkor_foglalt_esemeny=seged_naptar.Datum_Esemenye<Gond_Van>(lefoglalt_datum);
        ekkor_foglalt_esemeny.esemeny_kiir();
        std::cout<<"Szeretnél más eseményt is látni(I vagy N)?"<<std::endl;
        std::cin>>szeretne_e;
    }
}
//A felhasználó által kívánt naptár kiirható.
void naptar_kiiratas(std::fstream& fs)
{
    std::cout<<"Milyen naptárt szeretnél kiiratni? Évest(E) vagy hónapost(H)?"<<std::endl;
    char naptar_tipus;
    std::cin>>naptar_tipus;
    while(naptar_tipus!='E'&&naptar_tipus!='H')
    {
        std::cout<<"Rossz betût írtál be. E vagy H kell legyen"<<std::endl;
        std::cin>>naptar_tipus;
    }
    if(naptar_tipus=='E')
    {
        int evszam;
        std::cout<<"Milyen évet szeretnél látni? Írd be az évszámot!"<<std::endl;
        std::cin>>evszam;
        Eves_Naptar kiirando_ev(evszam);
        kiirando_ev.foglalas_olvasas_file<Gond_Van>(fs);
        kiirando_ev.kiir();
    }
    if(naptar_tipus=='H')
    {
        int evszam, honap_sorszam;
        std::cout<<"Milyen hónapot szeretnél látni? Írd be elõször évszámot, majd a hónap sorszámát!"<<std::endl;
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
      //Fájlból beolvasás és fájlba kiirás tesztelés
	   std::ifstream test_beolvasas("Beolvaso_Teszt.txt");
	     std::ofstream test_kiiras("Kiiro_Teszt.txt");
	     if (!test_beolvasas) {
         throw std::runtime_error("Nem sikerült megnyitni a beolvasó fájlt!");
        }
        if (!test_kiiras) {
        throw std::runtime_error("Nem sikerült megnyitni a kiíró fájlt!");
        }
	   teszt_beolvasas_kiiras(test_beolvasas,test_kiiras);
	   test_beolvasas.close();
	   test_kiiras.close();
     //Felhasználói alkalmazás
       std::fstream foglalt_esemenyekf("foglalt_esemenyek.txt",std::ios::in |std::ios::out);
       if(!foglalt_esemenyekf)
        {
            throw std::runtime_error("Nem sikerült megnyitni a kiíró fájlt!");
        }
	   std::cout<<"Mit szeretnél csinálni? ";
	   std::cout<<" Naptárat kiiratni(N), eseményt foglalni(F), eseményt törölni(T), az összes foglalt eseményt látni(O) vagy kilépni(K)?"<<std::endl;
       char funkcio_valasztas;
       std::cin>>funkcio_valasztas;
       while(funkcio_valasztas!='K')
       {
            //A fájl visszaállítása az elejére olvasáshoz.
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
              foglalt_esemenyekf.seekp(0, std::ios::end);//A poziciót a fájl végére állítja íráshoz.
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
               //A törölt eseményt a fájlból is töröljük.
               //Ezt úgy valósítsuk be, hogy a naptárban törlés után, az új eseménylistát írjuk be a fájlba.
              Esemeny foglalando_esemeny;
              foglalando_esemeny.esemeny_beolvas();
              seged_naptar.torles<Gond_Van>(foglalando_esemeny);
              foglalt_esemenyekf.close();
              foglalt_esemenyekf.open("foglalt_esemenyek.txt", std::ios::out | std::ios::trunc);//törlés érdekében kinyitás
              seged_naptar.lefoglaltak_kiir_olvasashoz(foglalt_esemenyekf);
              foglalt_esemenyekf.close();
              foglalt_esemenyekf.open("foglalt_esemenyek.txt", std::ios::in | std::ios::out|std::ios::app);
              break;
           }

           default:
           std::cout<<"Rosz betût írtál be.";
       }

           std::cout<<"Mit szeretnél következõnek csinálni?";
           std::cout<<" Naptárat kiiratni(N), eseményt foglalni(F), eseményt törölni(T), az összes foglalt eseményt látni(O) vagy kilépni(K)?"<<std::endl;
           std::cin>>funkcio_valasztas;
       }
       foglalt_esemenyekf.close();

	}
	catch (Gond_Van& e) {
	std::cerr << "Saját kivetel jott"<<e.what()<<std:: endl;
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


