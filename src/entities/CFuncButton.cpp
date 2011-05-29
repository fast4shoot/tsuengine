#include "CFuncButton.h"

#include "CBaseEngine.h"

CFuncButton::CFuncButton():
  CWorldEntity()
{
  m_onceOnly = false;
  m_resetTime = 1.;
  m_pressTime = engine->getTime();
  m_pressed = false;
}

void CFuncButton::spawn(){
  m_modelOn->linkToEntity(this);
  m_modelOn->setPhysics(P_STATIC);
  m_modelOn->setVisible(false);
  m_modelOff->linkToEntity(this);
  m_modelOff->setPhysics(P_STATIC);
  engine->log("CFuncButton spawned");
}

void CFuncButton::think(){
  if(!m_onceOnly && engine->getTime()-m_pressTime >= m_resetTime){
    setPressed(false);
  }
}

void CFuncButton::use(CBaseEntity* originator){
  if(!m_pressed){
    setPressed(true);
    m_pressTime = engine->getTime();
    fireOutput("onPress");
  }
}

void CFuncButton::setPressed(bool pressed){
  m_pressed = pressed;
  m_modelOn->setVisible(pressed);
  m_modelOff->setVisible(!pressed);
}

REGISTER_ENTITY(CFuncButton)
