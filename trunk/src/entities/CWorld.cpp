#include "CWorld.h"

void CWorld::spawn(){
  m_model->linkToEntity(this);
  m_model->setPhysics(P_STATIC);
}

REGISTER_ENTITY(CWorld)
