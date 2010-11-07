#ifndef CTEXT_H
#define CTEXT_H

#include "CGuiPanel.h"


class CText : public CGuiPanel
{
  public:
    CText(const vec2d& pos, const vec2d& size);
    virtual ~CText(){};
};

#endif // CTEXT_H
