#include "TestPanel.h"
#include <gl/gl.h>
#include "macros.h"
#include "globals.h"
#include "CLabel.h"

void TestPanel::draw(){
  glColor4f(bgColor.r,bgColor.g,bgColor.b,bgColor.a);
  drawQuad(0.,0.,size.x,size.y);
}

void TestPanel::onMouseDown(const vec2d& position, MouseButton button){
  bgColor.set(.8,.8,.8,1.);
}
void TestPanel::onMouseUp(const vec2d& position, MouseButton button){
  bgColor.set(.8,.8,.8,.9);
  addChild(new CLabel(position-vec2d(20.,20.),vec2d(40.,40.),"FAIL"));
}

void TestPanel::onMouseOver(){
  bgColor.set(.6,.6,.6,.8);
}

void TestPanel::onMouseOut(){
  bgColor.set(.5,.5,.5,.8);
}

TestPanel::TestPanel(double x, double y, double w, double h):
CGuiPanel(x,y,w,h)
{
  bgColor.set(.5,.5,.5,.8);
}

TestPanel::TestPanel(const vec2d& pos, const vec2d& size):
CGuiPanel(pos,size)
{
  bgColor.set(.5,.5,.5,.8);
}
