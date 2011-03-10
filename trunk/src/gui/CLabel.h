#ifndef CLABEL_H
#define CLABEL_H

#include <string>
#include <map>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "Font.h"


class CLabel: public CGuiPanel{
  public:
    enum ALIGN{
      ALIGN_LEFT=0,
      ALIGN_CENTER,
      ALIGN_RIGHT
    };

                    CLabel(const vec2d& position, const vec2d& size, const String& text="", ALIGN align=ALIGN_LEFT);
    void            setText(const String& text);
    String          getText();

    virtual void    draw();

  protected:
    String          _text;
    float           _height;
    Font*           _font;
    ALIGN           _align;

};

inline void CLabel::setText(const String& text){
  _text=text;
}

inline String CLabel::getText(){
  return _text;
}



#endif
