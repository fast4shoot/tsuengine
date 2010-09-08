#ifndef CGUIMGR_H
#define CGUIMGR_H

#include "CGuiPanel.h"

class CGuiMgr{
  public:
         CGuiMgr();
    void init();
    void update();
    void drawElements();
    
    CGuiPanel* basePanel;
};


#endif
