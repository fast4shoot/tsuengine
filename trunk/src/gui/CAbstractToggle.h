#ifndef CABSTRACTTOGGLE_H
#define CABSTRACTTOGGLE_H

#include "datatypes.h"
#include "CAbstractButton.h"

class CAbstractToggle: public CAbstractButton
{
  public:
    CAbstractToggle(const vec2d& pos, const vec2d& size, bool selected=false);
    bool getSelected();
    void setSelected(bool selected);
    virtual void onStateChanged(){}
    virtual void onMouseClick(const vec2d& position, const MouseButton button);
  protected:
    bool m_selected;
};

inline bool CAbstractToggle::getSelected(){
  return m_selected;
}

inline void CAbstractToggle::setSelected(bool selected){
  m_selected = selected;
}

#endif // CABSTRACTTOGGLE_H
