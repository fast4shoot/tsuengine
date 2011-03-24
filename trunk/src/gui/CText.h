#ifndef CTEXT_H
#define CTEXT_H

#include "typedefs.h"
#include "CGuiPanel.h"
#include "CLabel.h"
#include "macros.h"
#include "utils/stringUtils.h"


class CText : public CGuiPanel
{
  public:
                    CText(const vec2d& pos, const vec2d& size, const double height);
    virtual         ~CText();
    virtual void    draw();
    void            setText(const String& text);
    String          getText() const;
    void            invalidate(){_valid=false;}
    void            sizeChanged();
  private:
    void            update();
    Font*           _font;
    String          _text;
    double          _height;
    CGuiPanel*      _textContainer;
    bool            _valid;

};



inline CText::~CText(){}

inline void CText::draw(){
  if(!_valid){
    update();
  }
}

inline void CText::setText(const String& text){
  _text=text;
  invalidate();
}

inline String CText::getText() const {
  return _text;
}



inline void CText::sizeChanged(){
  invalidate();
}

#endif // CTEXT_H
