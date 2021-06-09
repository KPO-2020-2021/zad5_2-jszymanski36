/*!
* \file 
* \brief Definicje metod klasy SceneObject
*/

#include "../inc/scene_object.hh"
#include "../inc/slope.hh"
#include "../inc/peak.hh"
#include "../inc/flat.hh"
#include "../inc/drone.hh"
#include <fstream> 

/*! 
* Obliczanie i wpisanie do odpowiedniego pliku globalnych współrzędnych obiektu sceny, na podstawie jego lokalnych współrzędnych i innych parametrów
*/
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



