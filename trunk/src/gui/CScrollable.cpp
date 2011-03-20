#include "CScrollable.h"

CScrollable::CScrollable(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _panel(new CStencilPanel(vec2d(0,0), size-vec2d(20., 0.))),
  _bar(new CScrollBar(vec2d(getW()-20., 0), vec2d(20., getH())))
{
  _bar->addListener(makeCListenerMemberFn(SCROLLBAR, this, &CScrollable::apFn));
  addChild(_panel);
  addChild(_bar);
}

void CScrollable::setScrolledItem(CGuiPanel* scrolled){
  _scrolled=scrolled;
  _scrolled->setPosition(0., 0.);
  _panel->addChild(scrolled);
  _bar->setContentHeight(scrolled->getH());
}
