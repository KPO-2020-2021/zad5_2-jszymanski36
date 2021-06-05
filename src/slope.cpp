#include "../inc/slope.hh"
#include <fstream> 


Slope::Slope(Vector3D scale, double pos_x, double pos_y, std::string templatefiles[3]){
  
  double TPos[SIZE] = {pos_x, pos_y, 0};
  Vector3D Pos(TPos);

  SetPosition(Pos, 0);
  SetFileNames(templatefiles[2], templatefiles[1]);
  Initiate(templatefiles[0], scale[0], scale[1], scale [2]);
  CalcGlobalCoords();
}

void Slope::Initiate(std::string TemplateFile, double scale_x, double scale_y, double scale_z){
  
  std::ifstream Template (TemplateFile);
  std::ofstream Local (TakeFileName_LocalCoords());
  Vector3D point;
  double Tz[SIZE] = {0, 0, 0.5 * scale_z};
  double Tx[SIZE] = {scale_x, 0, 0};
  Vector3D Translation_Z(Tz), Modify_Point(Tx);

  if(!Template.is_open() || !Local.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
  SetScale(scale_x, scale_y, scale_z);

  for(int j = 0; j < 5; ++j){
    for(int i = 0; i < 4; ++i){
      Template >> point;
      if(Template.eof()) return;
      point = Scale(point);
      if((j==0 || j==4) && (i==1 || i==2)) point = point + Modify_Point;
      Local << point + Translation_Z;
      }
    Local << std::endl;
    }
}