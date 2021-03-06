#include "CDraggable.h"

CDraggable::CDraggable(const vec2d& position, const vec2d& size):
  CGuiPanel(position,size)
{
  bgColor.set(0.7,0.7,0.7,0.9);
  pressed=false;
}

void CDraggable::onMouseDown(const vec2d& position,const  MouseButton button){
  if(button==LMB){
    pressed=true;
    lastPosition=position;
  }
}

void CDraggable::onMouseUp(const vec2d& position,const  MouseButton button){
  if(button==LMB){
    pressed=false;
    lastPosition=position;
  }
}

void CDraggable::mouseMove(const vec2d& newPosition,const bool mouseOver){
  if(pressed){
    vec2d res=getParent()->getPosition()+newPosition-lastPosition;
    getParent()->setPosition(res);
  }
}

void CDraggable::draw(){
  drawVerticalGradient(0,0,getW(),getH(),rgba(0.5,0.5,0.5,0.9),bgColor);
  setDrawColor(glossColor);
  drawQuad(0,0,getW(),getH()/2.);
}
