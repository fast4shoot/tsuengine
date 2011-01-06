#include "CWindow.h"

#include "CDraggable.h"
#include "CLabel.h"
#include "CButton.h"

CWindow::CWindow(const vec2d& position, const vec2d& size, const String& label):
  CGuiPanel(position,size)
{
  bgColor.set(.65, .65, .65, .8);
  fgColor.set(.9, .9, .9, .9);

  CGuiPanel* drag=new CDraggable(vec2d(1, 1), vec2d(getW()-2, 30) );
  addChild(drag);

  CGuiPanel* temp;

  drag->addChild(new CLabel(vec2d(4,4), vec2d(24, 18), label ));
  drag->addChild(temp=new CLabel(vec2d(3,3), vec2d(24, 18), label ));
  temp->setFgColor(rgba(.0, .0, .0, 1. ));


  temp=new CButton(vec2d(getW()-26,3), vec2d(20,24), "X");
  temp->addListener(makeCListenerMemberFn(0, this, &CWindow::windowButtonPressed));
  drag->addChild(temp);

  addChild(_content=new CGuiPanel(vec2d(8., 38.), vec2d(getW()-16., getH()-46.)));
}

void CWindow::draw(){
  setDrawColor(fgColor);
  drawFrame(0, 0, getW(), getH());
  drawVerticalGradient(1, 31, getW()-2, getH()-32,rgba(.96,.96,.96,.8),bgColor);
  setDrawColor(rgba(0., 0., 0., 0.1));
  drawQuad(-1,-1,getW()+2, getH()+2);
  drawQuad(-2,-2,getW()+4, getH()+4);
  drawQuad(-3,-3,getW()+6, getH()+6);
}

void CWindow::windowButtonPressed(int id){
  if(id==0) setVisible(false);
}

void CWindow::onMouseDown(const vec2d& position,const  MouseButton button){
  requestFocus();
}
