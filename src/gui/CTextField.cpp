#include "CTextField.h"
#include "utf8/utf8.h"

CTextField::CTextField(const vec2d& position, const vec2d& size, const String& text):
  CGuiPanel(position,size),
  _string(text),
  _label(new CLabel(vec2d(2., 4.), vec2d(0., getH()-8.), text))
{
  addChild(_label);
}

/*
void CTextField::onKeyboard(const String& string){
  _string+=string;
  _label->setText(_string);
}
*/

void CTextField::onKeyboard(const String& string){

  for(String::const_iterator it=string.begin(); it!=string.end(); ++it){
    switch(*it){
      case 0x0A: //linefeed
      case 0x1B: //escape
      case 0x0D:  // carriage return
      break;
      case 0x08:  // backspace
        if(!_string.empty()){
          String::iterator it = _string.end();
          utf8::prior(it, _string.begin());
          _string.erase(it,_string.end());
        }
      break;
      case 0x09:  // tab
        _string.append("    ");
      break;
      default:
        _string.push_back(*it);
      break;
    }
  }
  _label->setText(_string);
  fireListeners();
}

void CTextField::draw(){
  setDrawColor(fgColor);
  drawFrame(0., 0., getW(), getH());
  drawVerticalGradient(1., 1., getW()-2., getH()-2., rgba(.2, .2, .2, .3), rgba(.4, .4, .4, .3));
}
