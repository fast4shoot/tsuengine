#ifndef CLABEL_H
#define CLABEL

#include <string>
#include <map>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "CBaseEngine.h"
#include "Font.h"


class CLabel: public CGuiPanel{
  public:
                    CLabel(const vec2d& position, const vec2d& size);
                    CLabel(const vec2d& position, const vec2d& size, const std::wstring& text);
    void            setText(const std::wstring& text);
    std::wstring    getText();

    virtual void    draw();
    virtual void    updateFont();


  protected:
    std::wstring     _text;
    float             _height;
    Font*           _font;
    void            init();

};

inline void CLabel::setText(const std::wstring& text){
  _text=text;
}

inline std::wstring CLabel::getText(){
  return _text;
}



#endif
