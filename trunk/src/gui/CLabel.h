#ifndef CLABEL_H
#define CLABEL

#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "GLFT_Font.hpp"
#include "FTGL/ftgl.h"

class CLabel: public CGuiPanel{
  public:
                    CLabel(const vec2d& position, const vec2d& size);
                    CLabel(const vec2d& position, const vec2d& size, const std::string& text);
    void            setText(const std::string& text);
    std::string     getText();
    void            setHeight(int height);
    int             getHeight();
    virtual void    draw();
    virtual void    updateFont();


  protected:
    std::string     _text;
    int             _height;
    FTGLPixmapFont* _font;
    void            init();

};

inline void CLabel::setText(const std::string& text){
  _text=text;
}

inline std::string CLabel::getText(){
  return _text;
}

inline void CLabel::setHeight(const int height){
  _height=height;
  updateFont();
}

inline int CLabel::getHeight(){
  return _height;
}

#endif
