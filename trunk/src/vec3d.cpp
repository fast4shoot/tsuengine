#include "vec3d.h"
#include "macros.h"


vec3d::vec3d(double x, double y, double z):
  x(x),
  y(y),
  z(z)
{}

vec3d::vec3d():
  x(0),
  y(0),
  z(0)
{}

void vec3d::set(double x, double y, double z){
  this->x=x;
  this->y=y;
  this->z=z;
}

vec3d vec3d::normalized() const{
  double len=length();
  vec3d ret;
  if(len==0.0){
    MSGBOX(L"Normalizing a zero-length vector!");
    ret.set(0,0,0);
  }else{
    ret/=len;
  }
  return ret;
}
