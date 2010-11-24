#ifndef CBUTTON_H
#define CBUTTON_H

#include "CAbstractButton.h"
#include "CLabel.h"
#include "typedefs.h"

class CButton: public CAbstractButton
{
  public:
                    CButton(const vec2d& pos, const vec2d& size, const String& text);
    virtual void    draw();
    virtual void    onMouseClick(const vec2d& position, const MouseButton button);

  protected:
    CLabel  *label;
    CLabel  *label2;
    rgba bgTopColor;
};

#endif // CBUTTON_H
