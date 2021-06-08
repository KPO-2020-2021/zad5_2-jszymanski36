#pragma once

#include "scene_object.hh"

class Slope: public SceneObject{

  private:

    virtual void Initiate(double scale_x, double scale_y, double scale_z) override;

  public:

    Slope(Vector3D scale, double pos_x, double pos_y,  std::string localfile, std::string globalfile);

    virtual std::string ReturnType() {return "Gora z grania";};
};