#ifndef CABSTRACTBUTTON_H
#define CABSTRACTBUTTON_H

#include "CGuiPanel.h"

class CAbstractButton: public CGuiPanel{
  public:
                    CAbstractButton(const vec2d& pos, const vec2d& size);
    virtual void    onMouseDown(const vec2d& position,const  MouseButton button);
    virtual void    onMouseUp(const vec2d& position, const MouseButton button);
    virtual void    onMouseOver();
    virtual void    onMouseOut();

  protected:
    bool active;
    bool pressed;
};

#endif
