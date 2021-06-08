#pragma once

/*!
* \file
* \brief Deklaracja klasy Sceny
*
* Plik zawiera deklarację klasy określającą pojęcie sceny zawierającej drony i jej metody
*/

/*!
* \brief Modeluje pojecie sceny
*/
#include "drone.hh"
#include <memory>



class Scene: Drone {

  private:

    /*!
    * \brief Kontener zawierający wszystkie używane drony
    */
    std::vector<Drone> DroneArray;

    /*!
    * \brief Indeks aktywnego drona wewnątrz kontenera
    */
    unsigned int ActiveDrone;

    std::list<std::shared_ptr<SceneObject>> ObjectList;

  public: 


    /*!
    * \brief Dodaj nowego drona do sceny
    */
    void AddDrone(Drone new_drone) {DroneArray.push_back(new_drone); ObjectList.push_back(std::make_shared<Drone> (new_drone));};

    /*!
    * \brief Zwróć wskaźnik na drona, który jest obecnie aktywny
    */
    Drone *GetActiveDrone(){return (&DroneArray[ActiveDrone]);};

    /*!
    * \brief Zwróć drona o podanym indeksie
    */
    Drone GetDrone(int index){return (DroneArray[index]);};

    /*!
    * \brief Wybierz aktywnego drona, podając jego numer (zaczynając od 1)
    */
    void ChooseActiveDrone(unsigned int choice) {ActiveDrone = choice-1;};

    /*!
    * \brief Zwróć indeks aktywnego drona
    */
    int ReturnAtiveDroneNum() {return ActiveDrone;};

    void AddObject(Vector3D scale, double pos_x, double pos_y, int type, PzG::LaczeDoGNUPlota &Lacze);

    void DeleteObject(int index, PzG::LaczeDoGNUPlota &Lacze);

    bool PrintObjects();

    ~Scene();
};