#include "CAbstractButton.h"

CAbstractButton::CAbstractButton(const vec2d& pos, const vec2d& size):
CGuiPanel(pos,size)
{}

void CAbstractButton::onMouseDown(const vec2d& position,const  MouseButton button){
  if(button==LMB)
    pressed=true;
}

void CAbstractButton::onMouseUp(const vec2d& position,const  MouseButton button){
  if(button==LMB)
    pressed=false;
}

void CAbstractButton::onMouseOver(){
  active=true;
}

void CAbstractButton::onMouseOut(){
  active=false;
  pressed=false;
}
