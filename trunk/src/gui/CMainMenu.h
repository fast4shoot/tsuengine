#ifndef CMAINMENU_H
#define CMAINMENU_H

#include "CGuiPanel.h"
#include "listeners/CListenerMemberFn.h"
#include "CButton.h"
#include "CConsole.h"

#include "macros.h"


class CMainMenu: public CGuiPanel{
  public:
    CMainMenu();
    virtual void draw();
    virtual void buttonClicked(int id);
    virtual void displayElement(CGuiPanel* element);
  protected:
    CGuiPanel* _newGame;
    CGuiPanel* _settings;
    CConsole*  _console;
    double    panelWidth;
};

inline void CMainMenu::displayElement(CGuiPanel* element){
  element->setVisible(true);
  element->requestFocus();
}


#endif // CMAINMENU_H
