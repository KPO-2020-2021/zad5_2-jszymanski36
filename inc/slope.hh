#pragma once

#include "scene_object.hh"

class Slope: public SceneObject{


  public:

    Slope(Vector3D scale, double pos_x, double pos_y,  std::string templatefiles[3]);

    virtual void Initiate(std::string TemplateFile, double scale_x, double scale_y, double scale_z) override;
};