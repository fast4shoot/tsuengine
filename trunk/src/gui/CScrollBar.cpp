#include "CScrollBar.h"
#include "CButton.h"
#include "CBaseEngine.h"

CScrollBar::CScrollBar(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _scrollAmt(0.)
{
  CButton* temp;
  addChild(temp=new CButton(vec2d(0.,0.), vec2d(getW(), getW()), "^"));
  temp->addListener(makeCListenerMemberFn(0, this, &CScrollBar::buttonScroll));
  addChild(temp=new CButton(vec2d(0.,getH()-getW()), vec2d(getW(), getW()), "V"));
  temp->addListener(makeCListenerMemberFn(1, this, &CScrollBar::buttonScroll));
}

void CScrollBar::buttonScroll(int id){

  switch(id){
    case 0: _scrollAmt-=20./m_contentHeight; break;
    case 1: _scrollAmt+=20./m_contentHeight; break;
  }
  engine->log(sformat("_scrollAmt: %f", _scrollAmt));
  _scrollAmt=clamp(_scrollAmt, 0., 1.);
  fireListeners();
}
