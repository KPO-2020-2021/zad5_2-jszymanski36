#pragma once

#include "cuboid.hh"


struct SceneObject: public Cuboid {

    public:
      
      void CalcGlobalCoords();

};