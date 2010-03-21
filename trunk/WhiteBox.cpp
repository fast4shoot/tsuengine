#include <gl/gl.h>
#include <cmath>
#include "WhiteBox.h"
#include "macros.h"
#include "globals.h"

WhiteBox::WhiteBox(double x, double y, double w, double h): CGuiPanel(x, y, w, h){
  color.r=1.;
  color.g=1.;
  color.b=1.;
  color.a=.5;
  isWhite=true;
}

void WhiteBox::draw(){
  CGuiPanel::draw();
  
  
  glBegin(GL_QUADS);
  
  glColor4f(color.r, color.g, color.b, 1.);
  glVertex2f(0,      0);
  glColor4f(color.r*.75, color.g*.75, color.b*.75, 1.);
  glVertex2f(size.x, 0);
  glColor4f(color.r, color.g, color.b, 1.);
  glVertex2f(size.x, size.y);
  glColor4f(color.r*.75, color.g*.75, color.b*.75, 1.);
  glVertex2f(0,      size.y);
  glEnd();
  
  CGuiPanel::drawChildren();
}

bool WhiteBox::onClick(const vec2d& position, MouseButton button){
  if(isWhite){
    color.set(0.,1.,0.,.5);
  }else{
    color.set(1.,1.,1.,.5); 
  }
  isWhite=!isWhite;
  getFocus();
  return false;
}
