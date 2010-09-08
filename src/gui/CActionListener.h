#ifndef CACTIONLISTENER_H
#define CACTIONLISTENER_H

class CGuiPanel;

class CActionListener{
  public:
                    CActionListener(int id);
    int             getId();
    void            setOriginator(CGuiPanel* originator);
    CGuiPanel*      getOriginator();
    virtual void    actionPerformed()=0;

  private:
    int             _id;
    CGuiPanel*      _originator;
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

inline CActionListener::CActionListener(int id){
  _id=id;
}

#endif
