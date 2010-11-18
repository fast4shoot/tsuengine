#ifndef CSCROLLABLE_H
#define CSCROLLABLE_H

#include <gl/gl.h>
#include "CGuiPanel.h"
#include "CScrollablePanel.h"
#include "CScrollBar.h"


class CScrollable : public CGuiPanel, CActionListenerPanel{
  public:
    CScrollable(const vec2d& pos, const vec2d& size);
    void setScrolledItem(CGuiPanel* scrolled);
    void actionPerformed(int id);
  protected:
    CScrollablePanel* _panel;
    CScrollBar* _bar;
    CGuiPanel* _scrolled;

    static const int SCROLLBAR=0;
};

inline CScrollable::CScrollable(const vec2d& pos, const vec2d& size):
  CGuiPanel(pos, size),
  _panel(new CScrollablePanel(vec2d(0,0), size-vec2d(20., 0.))),
  _bar(new CScrollBar(vec2d(getW()-20., 0), vec2d(20., getH())))
{
  _bar->addActionListener(new CActionListener(this, SCROLLBAR));
  addChild(_panel);
  addChild(_bar);
}

inline void CScrollable::setScrolledItem(CGuiPanel* scrolled){
  _scrolled=scrolled;
  _panel->addChild(scrolled);
}

inline void CScrollable::actionPerformed(int id){
  if(id==SCROLLBAR) _panel->setOffset(vec2d(0., -(_scrolled->getH()-getH())*(_bar->getScrollAmount())));
}


#endif // CSCROLLABLE_H
