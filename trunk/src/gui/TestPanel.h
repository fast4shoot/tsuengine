#ifndef TESTPANEL_H
#define TESTPANEL_H

#include "CGuiPanel.h"

class TestPanel: public CGuiPanel{
  public:
                  TestPanel(const vec2d& pos, const vec2d& size);
  virtual void    draw();
  virtual void    onMouseDown(const vec2d& position, MouseButton button);
  virtual void    onMouseUp(const vec2d& position, MouseButton button);
  virtual void    onMouseOver();
  virtual void    onMouseOut();
  private:
    rgba        fgColor;
    rgba        bgColor;
};

#endif
