#ifndef CACTIONLISTENER_H
#define CACTIONLISTENER_H

#include "CActionListenerPanel.h"
#include "macros.h"

class CGuiPanel;

class CActionListener{
  public:
                    CActionListener(CActionListenerPanel* panel, const int id);
    virtual void    actionPerformed();
    virtual void    positionChangePerformed();
    virtual void    sizeChangePerformed();
    virtual void    addChildPerformed(CGuiPanel* child);
  protected:
    int             _id;
    CGuiPanel*      _originator;
    CActionListenerPanel* _panel;
};


inline CActionListener::CActionListener(CActionListenerPanel* panel, const int id){
  _id=id;
  _panel=panel;
}

inline void CActionListener::actionPerformed(){
  _panel->actionPerformed(_id);
}

inline void CActionListener::positionChangePerformed(){
  _panel->positionChangePerformed(_id);
}

inline void CActionListener::sizeChangePerformed(){
  _panel->sizeChangePerformed(_id);
}

inline void CActionListener::addChildPerformed(CGuiPanel* child){
  _panel->addChildPerformed(_id, child);
}
#endif
