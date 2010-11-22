#ifndef CTEXTFIELD_H
#define CTEXTFIELD_H

#include "CGuiPanel.h"
#include "CLabel.h"

class CTextField : public CGuiPanel
{
  public:
                    CTextField(const vec2d& position, const vec2d& size, const String& text="");
    virtual void    onKeyboard(const String& string);
    virtual void    draw();
  protected:
    String    _string;
    CLabel*         _label;
};

#endif // CTEXTFIELD_H
