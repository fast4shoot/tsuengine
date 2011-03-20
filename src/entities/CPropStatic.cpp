#include "CPropStatic.h"

#include "DescriptorList.h"
#include "CBaseEngine.h"

void CPropStatic::spawn(){
  m_model->linkToEntity(this);
  m_model->setPhysics(P_STATIC);
}

REGISTER_ENTITY(CPropStatic)
