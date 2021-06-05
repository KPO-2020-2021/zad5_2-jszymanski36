#pragma once

#include "scene_object.hh"

class Flat: public SceneObject{


  public:

    Flat(Vector3D scale, double pos_x, double pos_y,  std::string templatefiles[3]);

    virtual void Initiate(std::string TemplateFile, double scale_x, double scale_y, double scale_z) override;
};