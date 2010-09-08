#include "Piskvorka.h"

bool hrac=false;

Piskvorka::Piskvorka(double x, double y, double w, double h): WhiteBox(x, y, w, h){
  isSet=false;
}

bool Piskvorka::onClick(const vec2d& position, MouseButton button){
  if(isSet) return false;
  if(hrac){
    color.set(1.,0.,0.,.5);
  }else{
    color.set(0.,1.,0.,.5); 
  }
  hrac=!hrac;
  isSet=true;
  return false;
}
