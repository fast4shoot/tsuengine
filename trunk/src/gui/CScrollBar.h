#ifndef CSCROLLBAR_H
#define CSCROLLBAR_H

#include "utils/math.h"
#include "utils/stringUtils.h"
#include "CGuiPanel.h"
#include "listeners/CListenerMemberFn.h"


class CScrollBar : public CGuiPanel{
  public:
    CScrollBar(const vec2d& pos, const vec2d& size);
    double getScrollAmount();
  protected:
    void buttonScroll(int id);
    double _scrollAmt;

};

inline double CScrollBar::getScrollAmount(){
  return _scrollAmt;
}

inline void CScrollBar::buttonScroll(int id){
  switch(id){
    case 0: _scrollAmt-=0.05; fireListeners(); break;
    case 1: _scrollAmt+=0.05; fireListeners(); break;
  }
  _scrollAmt=clamp(_scrollAmt, 0., 1.);
  fireListeners();
}


#endif // CSCROLLBAR_H
