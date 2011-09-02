#include "CPropToggle.h"
#include "elements/Model.h"


#include "DescriptorList.h"

void CPropToggle::toggle(CBaseEntity* originator){
  m_model->setVisible(!m_model->getVisible());
}

void CPropToggle::show(CBaseEntity* originator){
  m_model->setVisible(true);
}

void CPropToggle::hide(CBaseEntity* originator){
  m_model->setVisible(false);
}

REGISTER_ENTITY(CPropToggle)
