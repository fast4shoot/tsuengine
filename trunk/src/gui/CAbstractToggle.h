#ifndef CABSTRACTTOGGLE_H
#define CABSTRACTTOGGLE_H

#include "datatypes.h"
#include "CAbstractButton.h"

class CAbstractToggle: public CAbstractButton
{
  public:
    CAbstractToggle(const vec2d& pos, const vec2d& size, bool selected=false);
    CAbstractToggle(const vec2d& pos, const vec2d& size);
    bool getSelected();
    virtual void onStateChanged()=0;
    virtual void onMouseClick(const vec2d& position, const MouseButton button);
  protected:
    bool _selected;
};

inline bool CAbstractToggle::getSelected(){
  return _selected;
}

#endif // CABSTRACTTOGGLE_H
