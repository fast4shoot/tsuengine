#ifndef CBGFADE_H
#define CBGFADE_H

#include "CGuiPanel.h"

class CBgFade: public CGuiPanel{
  public:
    CBgFade();
    void draw();

  protected:
    double m_alphaStart;
    double m_timeStart;
    double m_time;
    double m_alphaEnd;
    double m_currAlpha;
};

#endif // CBGFADE_H
