#include "CDoorBase.h"

#include "DescriptorList.h"
#include "CBaseEngine.h"

void CDoorBase::init(){
  CWorldEntity::init();
  m_direction = 0.;
  m_fraction = 0.;
  m_open = false;
}

void CDoorBase::think(){
  if(m_direction != 0.){
    m_fraction+=m_direction*engine->getTimeDelta()*m_moveSpeed;
    if(m_fraction>=1.){
      m_direction = 0.;
      m_fraction = 1.;
      m_open = true;
      fireOutput("onOpen");
    }
    if(m_fraction<=0.){
      m_direction = 0.;
      m_fraction = 0.;
      m_open = false;
      fireOutput("onClose");
    }
  }
  //engine->debug(sformat("CDoorBase: %f, %d", m_fraction, m_direction) );
}

void CDoorBase::open(CBaseEntity* originator){
  m_direction=1;
}

void CDoorBase::close(CBaseEntity* originator){
  m_direction=-1;
}

void CDoorBase::toggle(CBaseEntity* originator){
  //engine->log("TOGGLE!!");
  if(m_direction == 0){
    m_direction = m_open?-1:1;
  }else{
    m_direction*=-1;
  }
}

REGISTER_ENTITY(CDoorBase)
