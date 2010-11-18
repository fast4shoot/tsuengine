#ifndef CSCROLLABLEPANEL_H
#define CSCROLLABLEPANEL_H

#include "datatypes.h"
#include "CGuiPanel.h"


class CScrollablePanel : public CGuiPanel{
  public:
    CScrollablePanel(const vec2d& pos, const vec2d& size);
    void setOffset(const vec2d& offset);
    void draw();
    void afterDraw();
  protected:
    vec2d _offset;
};

inline CScrollablePanel::CScrollablePanel(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _offset(0., 0.)
{}

inline void CScrollablePanel::setOffset(const vec2d& offset){
  _offset=offset;
}

inline void CScrollablePanel::draw(){
  glColorMask(0,0,0,0);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc (GL_ALWAYS, 0x1, 0x1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  drawQuad(0., 0., getW(), getH());
  glColorMask(1,1,1,1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  glStencilFunc(GL_LESS,0,0xff);

  glPushMatrix();
  glTranslatef(_offset.x, _offset.y, 0.);
}

inline void CScrollablePanel::afterDraw(){
  glPopMatrix();
  glDisable(GL_STENCIL_TEST);
  glColorMask(0,0,0,0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
  drawQuad(0., 0., getW(), getH());
  glColorMask(1,1,1,1);
}

#endif // CSCROLLABLEPANEL_H
