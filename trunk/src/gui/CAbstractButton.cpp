#include "CAbstractButton.h"

CAbstractButton::CAbstractButton(const vec2d& pos, const vec2d& size):
CGuiPanel(pos,size)
{}

void CAbstractButton::onMouseDown(const vec2d& position,const  MouseButton button){
  if(button==LMB)
    _pressed=true;
}

void CAbstractButton::onMouseUp(const vec2d& position,const  MouseButton button){
  if(button==LMB)
    _pressed=false;
}

void CAbstractButton::onMouseOver(){
  _active=true;
}

void CAbstractButton::onMouseOut(){
  _active=false;
  _pressed=false;
}
