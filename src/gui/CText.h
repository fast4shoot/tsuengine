#ifndef CTEXT_H
#define CTEXT_H

#include "CGuiPanel.h"
#include "FontWrapped.h"
#include "macros.h"
#include "utils/stringUtils.h"

class CText : public CGuiPanel
{
  public:
    CText(const vec2d& pos, const vec2d& size, const double height);
    virtual ~CText();
    virtual void draw();
    void          setText(const std::wstring& text);
  private:
    Font*  _font;
    std::wstring  _text;
    double        _height;
    CGuiPanel*    _textContainer;
};

inline CText::CText(const vec2d& pos, const vec2d& size, const double height):
  CGuiPanel(pos,size),
  _textContainer(new CGuiPanel(pos,size)),
  _height(height),
  _font(engine->fonts->getFont(L"ARIALUNI.TTF", height))
{}

inline CText::~CText(){}

inline void CText::draw(){
  _font->render(_text,_height,fgColor);
}

inline void CText::setText(const std::wstring& text){
  /*for(std::wstring::iterator it = text.begin(); it != text.end(); ++it){

  }*/
  std::wstring line = text;
  std::wstring part = text;
  if(_font->width(part,_height)>getW()){

  }
  MSGBOX(swformat(L"delka je %lf",_font->width(text,_height)).c_str());
}

#endif // CTEXT_H
