#ifndef CWINDOW_H
#define CWINDOW_H

#include "CGuiPanel.h"
#include "CActionListener.h"

class CWindow: public CGuiPanel, CActionListenerPanel
{
  public:
    CWindow(const vec2d& position, const vec2d& size, const std::wstring& label);
    virtual void draw();
    virtual void actionPerformed(int id);
    virtual void onMouseDown(const vec2d& position,const  MouseButton button);
};

#endif // CWINDOW_H
