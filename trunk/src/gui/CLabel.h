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

                    CLabel(const vec2d& position, const vec2d& size, const String& text="", bool shaded = false, ALIGN align=ALIGN_LEFT);
    void            setText(const String& text);
    String          getText();

    virtual void    draw();
    void            invalidate();
    void            recalculate();

  protected:
    String          _text;
    float           _height;
    Font*           _font;
    ALIGN           _align;
    double          m_offset;
    bool            m_invalid;
    bool            m_shaded;

};

inline String CLabel::getText(){
  return _text;
}

inline void CLabel::invalidate(){
  m_invalid = true;
}


#endif
