#include "CAbstractToggle.h"

CAbstractToggle::CAbstractToggle(const vec2d& pos, const vec2d& size, bool selected):
  CAbstractButton(pos,size),
  m_selected(selected)
{}

void CAbstractToggle::onMouseClick(const vec2d& position, const MouseButton button){
  if(button==LMB){
    m_selected=!m_selected;
    onStateChanged();
    fireListeners();
  }
}
