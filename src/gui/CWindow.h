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
    virtual CGuiPanel* getContent(){return _content;}
  private:
    CGuiPanel* _content;
};

#endif // CWINDOW_H
