#ifndef CMAINMENU_H
#define CMAINMENU_H

#include "CGuiPanel.h"
#include "listeners/CListenerMemberFn.h"
#include "CButton.h"
#include "CConsole.h"

class CDownloadMaps;

#include "macros.h"


class CMainMenu: public CGuiPanel{
  public:
    CMainMenu();
    virtual void draw();
    virtual void buttonClicked(int id);
    virtual void displayElement(CGuiPanel* element);
    CGuiPanel* newGame;
    CGuiPanel* settings;
    CConsole*  console;
    CDownloadMaps* download;
  protected:

    double    panelWidth;
};

inline void CMainMenu::displayElement(CGuiPanel* element){
  element->setVisible(true);
  element->requestFocus();
}


#endif // CMAINMENU_H
