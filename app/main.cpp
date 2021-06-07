// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "../inc/scene.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"
#include "../inc/matrix3x3.hh"
#include "../inc/lacze_do_gnuplota.hh"

#define PLIK_ROBOCZY__DRON_KORPUS  "../datasets/PlikRoboczy_Dron_Korpus.dat"
#define PLIK_ROBOCZY__DRON_ROTOR  "../datasets/PlikRoboczy_Dron_Rotor.dat"
#define PLIK_ROBOCZY_SZCZYT        "../datasets/PlikRoboczy_Szczyt.dat"
#define PLIK_ROBOCZY_GRAN          "../datasets/PlikRoboczy_Gran.dat"
#define PLIK_ROBOCZY_PLASKOWYZ     "../datasets/PlikRoboczy_Plaskowyz.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "../datasets/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "../datasets/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "../datasets/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "../datasets/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "../datasets/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS  "../datasets/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1  "../datasets/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2  "../datasets/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3  "../datasets/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4  "../datasets/PlikWlasciwy_Dron2_Rotor4.dat"

#define PLIK_WLASCIWY_SZCZYT        "../datasets/PlikWlasciwy_Szczyt.dat"
#define PLIK_WLASCIWY_GRAN          "../datasets/PlikWlasciwyGran.dat"
#define PLIK_WLASCIWY_PLASKOWYZ     "../datasets/PlikWlasciwy_Plaskowyz.dat"

#define PLIK_TRASY_PRZELOTU "../datasets/trasa_przelotu.dat"

#define PLIK_WZORCOWEGO_SZESCIANU       "../datasets/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "../datasets/graniastoslup6.dat"

/*!
* \brief Pozycja 1. drona
*/
#define DRONE1_POS 20,20,0

/*!
* \brief Pozycja 2. drona
*/
#define DRONE2_POS 140,50,0


/*!
* \brief Zapisz ścieżkę lotu do odpowiedniego pliku
* \param[in] PathPoints - kontener zawierający poszczególne punkty na planowanej ścieżce lotu drona
* \param[in] FileName - nazwa pliku do którego ścieżka powinna zostać zapisana
*/
void WritePathToFile(std::vector<Vector3D> PathPoints, std::string FileName){
       std::ofstream file(FileName);

       if(!file.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
       file << PathPoints[0];
       file << PathPoints[1];
       file << PathPoints[2];
       file << PathPoints[3];
}

/*!
* \brief Wyświetl opcje menu programu
*/
void PrintMenu(){

       std::cout << "a - wybierz aktywnego drona" << std::endl;
       std::cout << "p - zadaj parametry przelotu" << std::endl;
       std::cout << "m - wyswietl menu" << std::endl;
       std::cout << "r - wykonaj ruch po okręgu o zadanym promieniu" << std::endl << std::endl;
       std::cout << "k - koniec działania programu" << std::endl;
}

int main()
{
  PzG::LaczeDoGNUPlota  Lacze;
  std::vector<Vector3D> Path;
  Scene scene;
  Drone drone1, drone2;
  Drone *dronePtr;          // wskaźnik na aktywnego drona, to przez niego wykonywane są operacje na dronie

  char choice;              // wybór opcji przez użytkownika
  double angle, distance;   // kąt i odległość wybierane przez użytkownika

  Cuboid::TemplateFileName = PLIK_WZORCOWEGO_SZESCIANU;
  HexPrism::TemplateFileName = PLIK_WZORCOWEGO_GRANIASTOSLUPA6;

  const std::string FileNames1[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON1_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON1_ROTOR1, PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR3, PLIK_WLASCIWY__DRON1_ROTOR4};

  drone1.SetCoordFiles(FileNames1);
  drone1.Initiate(DRONE1_POS, 0);
  drone1.CalcDroneGlobalCoords();


  const std::string FileNames2[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON2_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON2_ROTOR1, PLIK_WLASCIWY__DRON2_ROTOR2, PLIK_WLASCIWY__DRON2_ROTOR3, PLIK_WLASCIWY__DRON2_ROTOR4};
  drone2.SetCoordFiles(FileNames2);
  drone2.Initiate(DRONE2_POS, 30);
  drone2.CalcDroneGlobalCoords();


  scene.AddDrone(drone1);
  scene.AddDrone(drone2);
  scene.ChooseActiveDrone(1);
  dronePtr = scene.GetActiveDrone();

  Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);
  
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR4);
  
  Lacze.DodajNazwePliku(PLIK_WLASCIWY_GRAN);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY_SZCZYT);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY_PLASKOWYZ);

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);

       double T1[SIZE] = {20, 80, 60};
       Vector3D Sc1(T1);
       std::string filenames1[3] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY_GRAN, PLIK_ROBOCZY_GRAN};
       Slope gran(Sc1, 100, 90, filenames1);
       scene.AddObject(gran);

       double T2[SIZE] = {10,10,60};
       Vector3D Sc2(T2);
       std::string filenames2[3] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY_SZCZYT, PLIK_ROBOCZY_SZCZYT};
       Peak szczyt(Sc2, 100, 20, filenames2);
       scene.AddObject(szczyt);

       double T3[SIZE] = {50, 60, 15};
       Vector3D Sc3(T3);
       std::string filenames3[3] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WLASCIWY_PLASKOWYZ, PLIK_ROBOCZY_PLASKOWYZ};
       Flat plaskowyz(Sc3, 150, 105, filenames3);
       scene.AddObject(plaskowyz);        


  Lacze.UstawRotacjeXZ(64,65); 
  Lacze.Rysuj();

       std::cout << "Położenie drona aktywnego: " << (*dronePtr).ReturnPosition();
       std::cout << std::endl;
       PrintMenu();

       while(choice!='k'){
              std::cout << std::endl << "Aktualna ilość obiektów Wektor3D: " << Vector3D::ReturnActiveNumVectors() << std::endl;
              std::cout << "Laczna ilość obiektów Wektor3D: " << Vector3D::ReturnAllNumVectors() << std::endl << std::endl;
              std::cout << "Twój wybór? (m - menu) > ";
              std::cin >> choice;
              

              switch(choice){
                     case 'a':{
                            int i;
                            std::cout << "Wybór aktywnego drona" << std::endl << std::endl;
                            std::cout << "1- Polozenie: " << scene.GetDrone(0).ReturnPosition();
                            if(scene.ReturnAtiveDroneNum() == 0) std::cout << " ^Dron aktywny";
                            std::cout << std::endl <<  "2- Polozenie: " << scene.GetDrone(1).ReturnPosition();
                            if(scene.ReturnAtiveDroneNum() == 1) std::cout << " ^Dron aktywny";

                            std::cout << std::endl << "Wprowadź numer aktywnego drona>";
                            std::cin >> i;
                            scene.ChooseActiveDrone(i);
                            dronePtr = scene.GetActiveDrone();
                            std::cout << std::endl << "Polozenie drona aktywnego: " << (*dronePtr).ReturnPosition();

                     break;
                     }

                     case 'p':
                            std::cout << "Podaj kierunek lotu (kat w stopniach) > ";
                            std::cin >> angle;
                            std::cout  << "Podaj długość lotu > ";
                            std::cin >> distance;
                            std::cout << std::endl << "Rysuje zaplanowana sciezke lotu ..." << std::endl;
                            (*dronePtr).PlanPath(angle, distance, Path);
                            WritePathToFile(Path, PLIK_TRASY_PRZELOTU);
                            Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);

                            std::cout << "Realizacja przelotu ..." << std::endl;
                            (*dronePtr).VerticalFlight(80, Lacze);
                            (*dronePtr).Rotate(angle, Lacze);
                            (*dronePtr).HorizontalFlight(distance, Lacze);
                            (*dronePtr).VerticalFlight(-80, Lacze);

                            std::cout << "Dron wyladował ..." << std::endl << std::endl;
                            std::cout << "Polozenie drona aktywnego: " << (*dronePtr).ReturnPosition();

                            Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
                            Lacze.Rysuj();
                     break;

                     case 'm':
                            PrintMenu();
                     break;

                     case 'k':
                            std::cout << "Koniec działania programu. " << std::endl;
                     break;

                     case 'r':
                            std::cout << "Podaj promień okręgu: > ";
                            std::cin >> distance;
                            std::cout << std::endl << "Realizacja przelotu ..." << std::endl;
                            (*dronePtr).GoAround(distance, Lacze);
                            
                            std::cout << "Dron wylądował ..." << std::endl << std::endl;
                            std::cout << "Polozenie drona aktywnego: " << (*dronePtr).ReturnPosition();
                     break;

                     default:
                            std::cout << "Nieprawidłowy wybór opcji" << std::endl;
                     break;
              }
       }
       return 0;
}