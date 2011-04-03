#ifndef CWINDOW_H
#define CWINDOW_H

#include "CGuiPanel.h"
#include "listeners/CListenerMemberFn.h"

class CWindow: public CGuiPanel
{
  public:
    CWindow(const vec2d& position, const vec2d& size, const String& label, double bottomHeight = 0., bool hasTitle=true);
    virtual void draw();
    virtual void windowButtonPressed(int id);
    virtual void onMouseDown(const vec2d& position,const  MouseButton button);
    virtual CGuiPanel* getContent(){return _content;}
  private:
    CGuiPanel* _content;
    double m_bottomHeight;
    bool m_title;
};

#endif // CWINDOW_H
