#include "../inc/scene_object.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"
#include "../inc/drone.hh"
#include <fstream> 

void SceneObject::CalcGlobalCoords(){

  std::ifstream local(TakeFileName_LocalCoords());
  std::ofstream global(TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");

  while(true){
    for(int i = 0; i < 4; ++i){
      local >> point;
      if( local.eof()) return;
      point = TransformToParentsCoords(point);

      global << point;
    }
    global << std::endl;
  }
}

/* SceneObject::~SceneObject(){
  if(ReturnType() != "Dron"){
    remove(TakeFileName_LocalCoords().c_str());
    remove(TakeFileName_GlobalCoords().c_str());
  }
  std::cout << "a" << std::endl;
} */

