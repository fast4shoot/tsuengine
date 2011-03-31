#ifndef CGUIMGR_H
#define CGUIMGR_H

#include "elements/Material.h"
#include "macros.h"


class CGuiPanel;

class CGuiMgr{
  public:
         CGuiMgr();
    void init();
    void update();
    void drawElements();
    void setKeyboardReceiver(CGuiPanel* panel);
    bool isKeyboardReceiver(CGuiPanel* panel);

    void addMainMenuElement(CGuiPanel* element);

    void showMainMenu(bool val);

  protected:
    CGuiPanel* _basePanel;
    CGuiPanel* _keyboardReceiver;
    CGuiPanel* m_mainMenu;
    Material* cursorMat;
};

inline void CGuiMgr::setKeyboardReceiver(CGuiPanel* panel){
  _keyboardReceiver=panel;
}

inline bool CGuiMgr::isKeyboardReceiver(CGuiPanel* panel){
  return panel==_keyboardReceiver;
}



#endif
