#include "CWindow.h"

#include "CDraggable.h"
#include "CLabel.h"
#include "CButton.h"

CWindow::CWindow(const vec2d& position, const vec2d& size, const std::wstring& label):
  CGuiPanel(position,size)
{
  bgColor.set(.4, .4, .4, .8);
  fgColor.set(.9, .9, .9, .9);

  CGuiPanel* drag=new CDraggable(vec2d(1, 1), vec2d(getW()-2, 30) );
  addChild(drag);

  CGuiPanel* temp;

  drag->addChild(new CLabel(vec2d(4,4), vec2d(24, 18), label ));
  drag->addChild(temp=new CLabel(vec2d(3,3), vec2d(24, 18), label ));
  temp->setFgColor(rgba(.0, .0, .0, 1. ));


  temp=new CButton(vec2d(getW()-26,3), vec2d(20,24), L"X");
  temp->addActionListener(new CActionListener(this,1));
  drag->addChild(temp);


}

void CWindow::draw(){
  setDrawColor(fgColor);
  drawFrame(0, 0, getW(), getH());
  drawVerticalGradient(1, 31, getW()-2, getH()-32,rgba(.25,.25,.25,.8),bgColor);

}

void CWindow::actionPerformed(int id){
  if(id==1) setVisible(false);
}

void CWindow::onMouseDown(const vec2d& position,const  MouseButton button){
  requestFocus();
}
