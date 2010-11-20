#ifndef CSTENCILPANEL_H
#define CSTENCILPANEL_H

#include "datatypes.h"
#include "CGuiPanel.h"


class CStencilPanel: public CGuiPanel{
  public:
    CStencilPanel(const vec2d& pos, const vec2d& size);
    void draw();
    void afterDraw();
};

inline CStencilPanel::CStencilPanel(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size)
{}

inline void CStencilPanel::draw(){
  glColorMask(0,0,0,0);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc (GL_ALWAYS, 0x1, 0x1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  drawQuad(0., 0., getW(), getH());
  glColorMask(1,1,1,1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  glStencilFunc(GL_LESS,0,0xff);
}

inline void CStencilPanel::afterDraw(){
  glDisable(GL_STENCIL_TEST);
  glColorMask(0,0,0,0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
  drawQuad(0., 0., getW(), getH());
  glColorMask(1,1,1,1);
}

#endif // CSCROLLABLEPANEL_H
