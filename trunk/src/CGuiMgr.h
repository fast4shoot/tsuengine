#ifndef CGUIMGR_H
#define CGUIMGR_H

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

    CGuiPanel* _basePanel;
    CGuiPanel* _keyboardReceiver;
};

inline void CGuiMgr::setKeyboardReceiver(CGuiPanel* panel){
  _keyboardReceiver=panel;
}

inline bool CGuiMgr::isKeyboardReceiver(CGuiPanel* panel){
  return panel==_keyboardReceiver;
}

#endif
