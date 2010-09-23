#ifndef CDRAGGABLE_H
#define CDRAGGABLE_H

#include "datatypes.h"
#include "CAbstractButton.h"
class CDraggable: public CGuiPanel
{
  public:
    CDraggable(const vec2d& position, const vec2d& size);
    virtual void mouseMove(const vec2d& newPosition,const bool mouseOver);
    virtual void onMouseDown(const vec2d& position,const  MouseButton button);
    virtual void onMouseUp(const vec2d& position,const  MouseButton button);
    virtual void draw();
  protected:
    vec2d lastPosition;
    bool pressed;
};

#endif // CDRAGGABLE_H
