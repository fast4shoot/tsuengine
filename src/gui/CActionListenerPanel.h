#ifndef CACTIONLISTENERPANEL_H
#define CACTIONLISTENERPANEL_H


class CActionListenerPanel
{
  public:
    virtual void actionPerformed(int id){};
    virtual void positionChangePerformed(int id){};
    virtual void sizeChangePerformed(int id){};
    virtual void addChildPerformed(int id, CGuiPanel* child){};
};

#endif // CACTIONLISTENERPANEL_H
