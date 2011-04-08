#include "CFuncButton.h"

#include "CBaseEngine.h"

void CFuncButton::init(){
  m_onceOnly = false;
  m_resetTime = 1.;
}

void CFuncButton::spawn(){
  m_modelOn->linkToEntity(this);
  m_modelOn->setPhysics(P_STATIC);
  m_modelOn->setVisible(false);
  engine->log("wtf");
  m_modelOff->linkToEntity(this);
  m_modelOff->setPhysics(P_STATIC);
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
