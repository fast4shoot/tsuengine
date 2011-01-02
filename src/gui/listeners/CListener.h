#ifndef CLISTENER_H
#define CLISTENER_H


#include "macros.h"

class CGuiPanel;

class CListener{
  public:
    virtual void    actionPerformed(){};
    virtual void    positionChangePerformed(){};
    virtual void    sizeChangePerformed(){};
    virtual void    addChildPerformed(CGuiPanel* child){};
};

#endif
