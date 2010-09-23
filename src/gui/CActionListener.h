#ifndef CACTIONLISTENER_H
#define CACTIONLISTENER_H

#include "CActionListenerPanel.h"
#include "macros.h"

class CGuiPanel;

class CActionListener{
  public:
                    CActionListener(CActionListenerPanel* panel, int id);
    int             getId();
    void            setOriginator(CGuiPanel* originator);
    CGuiPanel*      getOriginator();
    virtual void    actionPerformed();

  private:
    int             _id;
    CGuiPanel*      _originator;
    CActionListenerPanel* _panel;
};

inline int CActionListener::getId(){
  return  _id;
}

inline void CActionListener::setOriginator(CGuiPanel* originator){
  _originator=originator;
}

inline CGuiPanel* CActionListener::getOriginator(){
  return _originator;
}

inline CActionListener::CActionListener(CActionListenerPanel* panel, int id){
  _id=id;
  _panel=panel;
}

inline void CActionListener::actionPerformed(){
  _panel->actionPerformed(_id);
}

#endif
