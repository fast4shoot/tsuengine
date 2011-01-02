#ifndef CWINDOW_H
#define CWINDOW_H

#include "CGuiPanel.h"
#include "listeners/CListenerMemberFn.h"

class CWindow: public CGuiPanel
{
  public:
    CWindow(const vec2d& position, const vec2d& size, const String& label);
    virtual void draw();
    virtual void windowButtonPressed(int id);
    virtual void onMouseDown(const vec2d& position,const  MouseButton button);
};

#endif // CWINDOW_H
