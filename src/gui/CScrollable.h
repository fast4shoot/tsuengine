#ifndef CSCROLLABLE_H
#define CSCROLLABLE_H

#include <gl/gl.h>
#include "listeners/CListenerMemberFn.h"
#include "CGuiPanel.h"
#include "CStencilPanel.h"
#include "CScrollBar.h"


class CScrollable : public CGuiPanel{
  public:
    CScrollable(const vec2d& pos, const vec2d& size);
    void setScrolledItem(CGuiPanel* scrolled);
    void apFn(int id);
  protected:
    CStencilPanel* _panel;
    CScrollBar* _bar;
    CGuiPanel* _scrolled;

    static const int SCROLLBAR=0;
};

inline CScrollable::CScrollable(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _panel(new CStencilPanel(vec2d(0,0), size-vec2d(20., 0.))),
  _bar(new CScrollBar(vec2d(getW()-20., 0), vec2d(20., getH())))
{
  _bar->addListener(makeCListenerMemberFn(SCROLLBAR, this, &CScrollable::apFn));
  addChild(_panel);
  addChild(_bar);
}

inline void CScrollable::setScrolledItem(CGuiPanel* scrolled){
  _scrolled=scrolled;
  _scrolled->setPosition(0., 0.);
  _panel->addChild(scrolled);
}

inline void CScrollable::apFn(int id){
  if(id==SCROLLBAR) _scrolled->setY(-(_scrolled->getH()-getH())*(_bar->getScrollAmount()));
}


#endif // CSCROLLABLE_H
