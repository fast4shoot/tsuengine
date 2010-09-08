#ifndef WHITEBOX_H
#define WHITEBOX_H
#include "CGuiPanel.h"

class WhiteBox : public CGuiPanel{
  public:
    WhiteBox(double x, double y, double w, double h);
    void draw();
    bool onClick(const vec2d& position, MouseButton button);
    rgba color;
    bool isWhite;
};
#endif
