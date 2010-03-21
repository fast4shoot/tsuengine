#include "vec3d.h"
#include <cmath>
#include "macros.h"
vec3d vec3d::operator=(vec3d& in){
  x=in.x;      
  y=in.y;
  z=in.z;
  return *this;
}

vec3d vec3d::operator+(vec3d& in){
  vec3d ret;
  ret.x=this->x+in.x;
  ret.y=this->y+in.y;
  ret.z=this->z+in.z;
 return vec3d();
}
  
vec3d vec3d::operator-(vec3d& in){
  vec3d ret;
  ret.x=this->x-in.x;
  ret.y=this->y-in.y;
  ret.z=this->z-in.z;
  return ret;
}

vec3d vec3d::operator*(double in){
  vec3d ret;
  ret.x=this->x*in;
  ret.y=this->y*in;
  ret.z=this->z*in;
  return ret;
}

vec3d vec3d::operator/(double in){
  vec3d ret;
  ret.x=this->x/in;
  ret.y=this->y/in;
  ret.z=this->z/in;
  return ret;
}

double vec3d::length(){
  return sqrt(x*x+y*y+z*z);       
}

double vec3d::lengthSqr(){
  return x*x+y*y+z*z;       
}

vec3d::vec3d(double x, double y, double z){
  this->x=x;
  this->y=y;
  this->z=z;                    
}

vec3d::vec3d(){
  x=0;
  y=0;
  z=0;                    
}

void vec3d::set(double x, double y, double z){
  this->x=x;
  this->y=y;
  this->z=z;                    
}

vec3d vec3d::normalized(){
  double len=length();
  vec3d ret;
  if(len==0.0){
    MSGBOX("Normalizing a zero-length vector!");
    ret.set(0,0,0);
  }else{
    ret.set(x/len,y/len,z/len);
  }
  return ret;
   
}
