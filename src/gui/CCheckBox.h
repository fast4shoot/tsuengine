#ifndef CCHECKBOX_H
#define CCHECKBOX_H

#include "CAbstractToggle.h"

class CCheckBox: public CAbstractToggle
{
  public:
    CCheckBox(const vec2d& pos, const vec2d& size, const String& text, bool selected=false);
    virtual void draw();
  protected:
};

#endif // CCHECKBOX_H
