#include "CAbstractToggle.h"

CAbstractToggle::CAbstractToggle(const vec2d& pos, const vec2d& size, bool selected):
  CAbstractButton(pos,size),
  _selected(selected)
{}

void CAbstractToggle::onMouseClick(const vec2d& position, const MouseButton button){
  if(button==LMB)
    _selected=!_selected;
}
