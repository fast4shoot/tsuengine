#ifndef CCENTEREDWINDOW_H
#define CCENTEREDWINDOW_H

#include "datatypes.h"
#include "CWindow.h"

class CCenteredWindow: public CWindow
{
  public:
    CCenteredWindow(const vec2d& size, const std::wstring& label);
};

#endif // CCENTEREDWINDOW_H
