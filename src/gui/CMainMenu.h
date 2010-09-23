#ifndef CMAINMENU_H
#define CMAINMENU_H

#include "CGuiPanel.h"
#include "CActionListener.h"
#include "CButton.h"
#include "CDraggable.h"

#include "macros.h"


class CMainMenu: public CGuiPanel, CActionListenerPanel{
  public:
    CMainMenu();
    virtual void draw();
    virtual void actionPerformed(int id);
  protected:
    CGuiPanel* newGame;
    CGuiPanel* settings;
    double    panelWidth;
};



#endif // CMAINMENU_H
