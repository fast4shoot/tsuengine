#ifndef CSCROLLABLE_H
#define CSCROLLABLE_H

#include "GL/glew.h"
#include "listeners/CListenerMemberFn.h"
#include "CGuiPanel.h"
#include "CStencilPanel.h"
#include "CScrollBar.h"


class CScrollable : public CGuiPanel{
  public:
    CScrollable(const vec2d& pos, const vec2d& size);
    void setScrolledItem(CGuiPanel* scrolled);
    void apFn(int id);
    void updateContentHeight(int dummy);
  protected:
    CStencilPanel* _panel;
    CScrollBar* _bar;
    CGuiPanel* _scrolled;

    static const int SCROLLBAR=0;
};



inline void CScrollable::apFn(int id){
  if(id==SCROLLBAR) _scrolled->setY(-(_scrolled->getH()-getH())*(_bar->getScrollAmount()));
}


#endif // CSCROLLABLE_H
