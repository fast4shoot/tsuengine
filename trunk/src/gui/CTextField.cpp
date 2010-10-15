#include "CTextField.h"

CTextField::CTextField(const vec2d& position, const vec2d& size, const std::wstring& text):
  CGuiPanel(position,size),
  _string(text),
  _label(new CLabel(vec2d(2., 4.), vec2d(0., getH()-8.), text))
{
  addChild(_label);
}

/*
void CTextField::onKeyboard(const std::wstring& string){
  _string+=string;
  _label->setText(_string);
}
*/

void CTextField::onKeyboard(const std::wstring& string){
  std::wstring temp(string);
  for(std::wstring::iterator it=temp.begin(); it!=temp.end(); ++it){
    switch(*it){
      case 0x0A: //linefeed
      case 0x1B: //escape
      case 0x0D:  // carriage return
      break;
      case 0x08:  // backspace
        if(!_string.empty()){
          _string.erase(_string.begin()+_string.size()-1);
        }
      break;
      case 0x09:  // tab
        _string.append(L"    ");
      break;
      default:
        _string.push_back(*it);
      break;
    }
  }
  _label->setText(_string);
}

void CTextField::draw(){
  drawVerticalGradient(0, 0, getW(), getH(), rgba(.2, .2, .2, .3), rgba(.4, .4, .4, .3));
}
