#ifndef CLABEL_H
#define CLABEL_H

#include <string>
#include <map>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "CBaseEngine.h"
#include "Font.h"


class CLabel: public CGuiPanel{
  public:
    enum ALIGN{
      ALIGN_LEFT=0,
      ALIGN_CENTER,
      ALIGN_RIGHT
    };

                    CLabel(const vec2d& position, const vec2d& size, const std::wstring& text=L"", ALIGN align=ALIGN_LEFT);
    void            setText(const std::wstring& text);
    std::wstring    getText();

    virtual void    draw();
    virtual void    updateFont();

  protected:
    std::wstring    _text;
    float           _height;
    Font*           _font;
    ALIGN           _align;

};

inline void CLabel::setText(const std::wstring& text){
  _text=text;
}

inline std::wstring CLabel::getText(){
  return _text;
}



#endif
