#ifndef CAUTOSIZEPANEL_H
#define CAUTOSIZEPANEL_H

#include "CGuiPanel.h"

class CAutoSizePanel: public CGuiPanel{
  public:
    CAutoSizePanel();
  protected:
    void recalcSizeCallback(int id);
    void recalcSizeOnNewChildCallback(int id, CGuiPanel* panel);
    void recalc();
};

#endif // CAUTOSIZEPANEL_H
