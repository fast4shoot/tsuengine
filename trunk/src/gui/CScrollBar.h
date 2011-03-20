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
    void setContentHeight(double height);
  protected:
    void buttonScroll(int id);
    double _scrollAmt;
    double m_contentHeight;

};

inline void CScrollBar::setContentHeight(double height){
  m_contentHeight = height;
}

inline double CScrollBar::getScrollAmount(){
  return _scrollAmt;
}

#endif // CSCROLLBAR_H
