#include "vec2d.h"
#include <cmath>
#include "macros.h"
#include <cstdio>

vec2d::vec2d(){
  x=0;
  y=0;
}

vec2d::vec2d(double x, double y){
  this->x=x;
  this->y=y;
}

vec2d::vec2d(const vec2d& in){
  x=in.x;
  y=in.y;
}

vec2d::vec2d(vec2d& in){
  x=in.x;
  y=in.y;
}


void vec2d::set(double x, double y){
  this->x=x;
  this->y=y;

}

void vec2d::set(const vec2d& in){
  x=in.x;
  y=in.y;
}


double vec2d::length(){
  return sqrt(x*x+y*y);
}

double vec2d::lengthSqr(){
  return x*x+y*y;
}

vec2d vec2d::normalized(){
  double len=length();
  vec2d ret;
  if(len==0.0){
    MSGBOX(L"Normalizing a zero-length vector!");
    ret.set(0.,0.);
  }else{
    ret.set(x/len,y/len);
  }
  return ret;

}
