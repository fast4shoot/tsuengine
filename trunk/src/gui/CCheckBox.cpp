#include "CCheckBox.h"
#include "CLabel.h"


CCheckBox::CCheckBox(const vec2d& pos, const vec2d& size, const String& text, bool selected):
  CAbstractToggle(pos,size,selected)
{
  addChild(new CLabel(vec2d(getH()+5., 0), vec2d(getH(), getH()), text));
}

void CCheckBox::draw(){
  double u=getH()/8.;

  setDrawColor(bgColor);
  drawQuad(u,u,u*6,u*6);

  setDrawColor(fgColor);
  drawQuad(0., 0., getH(), u );
  drawQuad(0., u*7., getH(), u );
  drawQuad(0., u, u, u*6. );
  drawQuad(u*7., u, u, u*6. );

  if(_selected)
    drawQuad(u*2., u*2., u*4., u*4. );
}
