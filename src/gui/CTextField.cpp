#include "CTextField.h"

CTextField::CTextField(const vec2d& position, const vec2d& size, const std::wstring& text):
  CGuiPanel(position,size),
  _string(text),
  _label(new CLabel(vec2d(2., 2.), vec2d(0., getH()-4.), text))
{
  addChild(_label);
}

void CTextField::onKeyboard(const std::wstring& string){
  _string+=string;
  _label->setText(_string);
}

void CTextField::draw(){
  drawVerticalGradient(0, 0, getW(), getH(), rgba(.2, .2, .2, .3), rgba(.4, .4, .4, .3));
}
