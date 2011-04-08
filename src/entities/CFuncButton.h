#ifndef CFUNCBUTTON_H
#define CFUNCBUTTON_H

#include "CWorldEntity.h"


class CFuncButton : public CWorldEntity{
  public:
    void init();
    void spawn();
    void think();
    void use(CBaseEntity* originator);
    double m_resetTime;
    Model* m_modelOn;
    Model* m_modelOff;
    bool m_onceOnly;
    void setPressed(bool pressed);
  protected:
    double m_pressTime;
    bool m_pressed;
};

ENTITY_DESCRIPTOR(CFuncButton, CWorldEntity)
  void registerEntity(){
    spawnable(true);
    classname("func_button");
    value("resetTime", &CFuncButton::m_resetTime);
    value("modelOn", &CFuncButton::m_modelOn);
    value("modelOff", &CFuncButton::m_modelOff);
    value("onceOnly", &CFuncButton::m_onceOnly);
    output("onPress");
    input("use", &CFuncButton::use);
  }
};

#endif // CFUNCBUTTON_H
