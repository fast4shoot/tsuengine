#ifndef CGUIMGR_H
#define CGUIMGR_H

#include "elements/Material.h"
#include "macros.h"


class CGuiPanel;
class CBgFade;

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
    void fadeTo(double alpha, double time);
    CGuiPanel* getHud();

  protected:
    CGuiPanel* _basePanel;
    CGuiPanel* _keyboardReceiver;
    CGuiPanel* m_mainMenu;
    CGuiPanel* m_hud;
    CBgFade* m_fade;

    Material* cursorMat;
};

inline void CGuiMgr::setKeyboardReceiver(CGuiPanel* panel){
  _keyboardReceiver=panel;
}

inline bool CGuiMgr::isKeyboardReceiver(CGuiPanel* panel){
  return panel==_keyboardReceiver;
}

inline CGuiPanel* CGuiMgr::getHud(){
  return m_hud;
}


#endif
