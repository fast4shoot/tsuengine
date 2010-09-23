#include "CButton.h"

CButton::CButton(const vec2d& pos, const vec2d& size, const std::wstring& text):
CAbstractButton(pos,size)
{
  fgColor.set(1., 1., 1., 1.);
  bgColor.set(.5, .5, .5, .4);
  bgTopColor.set(0., 0., 0., .4);
  label=new CLabel(vec2d(4., getH()/15.), vec2d(getW()-12, getH()-getH()/3.),text);
  addChild(label);
}

void CButton::draw(){
  float mult = active?1.3f:1.f;
  mult*=pressed?0.75f:1.f;

  drawVerticalGradient(1., 1., getW()-2, getH()-2, bgTopColor*mult, bgColor*mult);
  if(!pressed){
    setDrawColor(glossColor);
    drawQuad(1., 1., getW()-2, (getH()-2)/2.);
  }
  setDrawColor(bgColor*5);
  drawFrame(0., 0., getW(), getH());
}

void CButton::onMouseClick(const vec2d& position, const MouseButton button){
  fireListeners();
}

