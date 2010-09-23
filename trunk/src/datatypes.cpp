#include "datatypes.h"
#include <cmath>
#include <cstdlib>
#include <windows.h>

/*
 *  Class: rgba
 *
 */

rgba::rgba(){
  r=g=b=a=0.0f;
}

rgba::rgba(float r, float g, float b, float a){
  this->r=r;
  this->g=g;
  this->b=b;
  this->a=a;
}

void rgba::set(float r, float g, float b, float a){
  this->r=r;
  this->g=g;
  this->b=b;
  this->a=a;
}

rgba rgba::operator*(float rhs){
  rgba out(r*rhs,g*rhs,b*rhs,a*rhs);
  return out;
}
