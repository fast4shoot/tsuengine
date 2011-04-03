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
    void stopKeyboardReceiving(CGuiPanel* panel);

    void addElement(CGuiPanel* element);

    void showMainMenu(bool val);
    CGuiPanel* getMainMenu();
    void fadeTo(double alpha, double time);
    CGuiPanel* getHud();

    void enableCursor(bool cursor);
    void enableEscape(bool escape);

  protected:
    CGuiPanel* _basePanel;
    CGuiPanel* _keyboardReceiver;
    CGuiPanel* m_mainMenu;
    CGuiPanel* m_hud;
    CBgFade* m_fade;

    Material* cursorMat;

    bool m_cursor;
    bool m_escape;
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

inline CGuiPanel* CGuiMgr::getMainMenu(){
  return m_mainMenu;
}

inline void CGuiMgr::enableCursor(bool cursor){
  m_cursor = cursor;
}

inline void CGuiMgr::enableEscape(bool escape){
  m_escape = escape;
}

#endif
