#include "CScrollBar.h"
#include "CButton.h"
CScrollBar::CScrollBar(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _scrollAmt(0.)
{
  CButton* temp;
  addChild(temp=new CButton(vec2d(0.,0.), vec2d(getW(), getW()), "^"));
  temp->addListener(makeCListenerMemberFn(0, this, &CScrollBar::buttonScroll));
  addChild(temp=new CButton(vec2d(0.,getW()), vec2d(getW(), getW()), "V"));
  temp->addListener(makeCListenerMemberFn(1, this, &CScrollBar::buttonScroll));
}
