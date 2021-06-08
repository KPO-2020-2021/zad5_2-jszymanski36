#pragma once

#include "scene_object.hh"

class Flat: public SceneObject{


  public:

    Flat(Vector3D scale, double pos_x, double pos_y,  std::string localfile, std::string globalfile);

    void Initiate(double scale_x, double scale_y, double scale_z) override;

    std::string ReturnType() override {return "Plaskowyz";};


};