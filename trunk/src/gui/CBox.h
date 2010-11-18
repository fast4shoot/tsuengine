#ifndef CBOX_H
#define CBOX_H

#include "CGuiPanel.h"


class CBox : public CGuiPanel{
  public:
    CBox(const vec2d& pos, const vec2d& size);
    virtual void draw();
};

inline CBox::CBox(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size)
{
  fgColor.set(.9, .9, .9, .9);
}

inline void CBox::draw(){
  setDrawColor(fgColor);
  drawFrame(0., 0., getW(), getH());
  setDrawColor(bgColor);
  drawQuad(1., 1., getW()-2., getH()-2.);
}

#endif // CBOX_H
