#include "CScrollBar.h"
#include "CButton.h"
CScrollBar::CScrollBar(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _scrollAmt(0.)
{
  CButton* temp;
  addChild(temp=new CButton(vec2d(0.,0.), vec2d(getW(), getW()), L"^"));
  temp->addActionListener(new CActionListener(this,0));
  addChild(temp=new CButton(vec2d(0.,getW()), vec2d(getW(), getW()), L"V"));
  temp->addActionListener(new CActionListener(this,1));
}
