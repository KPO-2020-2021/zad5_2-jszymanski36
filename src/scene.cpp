#include <bits/stdc++.h>
#include <memory>
#include <iostream>
#include "../inc/scene.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"


#define PLIK_WLASCIWY_PRZESZKODA         "../datasets/PlikWlasciwy_Przeszkoda"

#define PLIK_ROBOCZY_PRZESZKODA          "../datasets/PlikRoboczy_Przeszkoda"

#define FORMAT_PLIKU                ".dat"


void Scene::AddObject(Vector3D scale, double pos_x, double pos_y, int type, PzG::LaczeDoGNUPlota &Lacze){

  std::string localfile = std::string(PLIK_ROBOCZY_PRZESZKODA) + std::to_string(ObjectList.size() - DroneArray.size()) + FORMAT_PLIKU;
  std::string globalfile = std::string(PLIK_WLASCIWY_PRZESZKODA) + std::to_string(ObjectList.size() - DroneArray.size()) + FORMAT_PLIKU; 
  std::shared_ptr<SceneObject> tmp;
  switch(type){

    case 1:{
      tmp = std::make_shared<Peak>(Peak(scale, pos_x, pos_y, localfile, globalfile));
    }
    break;

    case 2:{
      tmp = std::make_shared<Slope>(Slope(scale, pos_x, pos_y, localfile, globalfile));
    }
    break;

    case 3:{
      tmp = std::make_shared<Flat>(Flat(scale, pos_x, pos_y, localfile, globalfile));
    }
    break;

    default:
      throw std::runtime_error("Niepoprawny typ przeszkody!");
    break;
  }
  ObjectList.push_back(tmp);
  Lacze.DodajNazwePliku(globalfile.c_str());
}


void Scene::DeleteObject(int index, PzG::LaczeDoGNUPlota &Lacze){

  std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin();
  std::advance(it, index + DroneArray.size() - 1);


  std::string local = it->get()->TakeFileName_LocalCoords();
  std::string global = it->get()->TakeFileName_GlobalCoords();
  Lacze.UsunNazwePliku(local);
  Lacze.UsunNazwePliku(global);
  remove(local.c_str());
  remove(global.c_str());
  ObjectList.erase(it);
}

bool Scene::PrintObjects(){

  if(ObjectList.size() == DroneArray.size()) return 0;

  int j = 1;
  for(std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin(); it != ObjectList.end(); ++it){
    if(it->get()->ReturnType() != "Dron"){
      std::cout << j << "- (" << it->get()->ReturnPosition() << ") " << it->get()->ReturnType() << std::endl;
      ++j;
    }
  }
  return 1;
}

Scene::~Scene(){

  for(std::list<std::shared_ptr<SceneObject>>::iterator it = ObjectList.begin(); it != ObjectList.end(); ++it){
    if(it->get()->ReturnType() != "Dron"){
      remove(it->get()->TakeFileName_GlobalCoords().c_str());
      remove(it->get()->TakeFileName_LocalCoords().c_str());
    }
  }
}
