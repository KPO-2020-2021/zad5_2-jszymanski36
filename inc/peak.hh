#pragma once

#include "scene_object.hh"

class Peak: public SceneObject{


  public:

    Peak(Vector3D scale, double pos_x, double pos_y, std::string localfile, std::string globalfile);

    virtual void Initiate(double scale_x, double scale_y, double scale_z) override;

    virtual std::string ReturnType() {return "Gora z ostrym szczytem";};
};