#include <vector>
#include "CBaseEntity.h"
#include "CBaseEngine.h"
#include "globals.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "CEntMgr.h"
#include "DescriptorList.h"


void CBaseEntity::think(){

}

vec3d CBaseEntity::getPos(){
  return pos;
}

void CBaseEntity::fireInput(const String& name, CBaseEntity* originator){
  CBaseEntity* originatorTemp = m_originator;
  m_originator = originator;
  m_descriptor -> fireInput(name, this, originator);
  m_originator = originatorTemp;
}

void CBaseEntity::setValue(const String& name, const json::mValue& value){
  m_descriptor -> setValue(name, this, value);
}

void CBaseEntity::print(CBaseEntity* originator){
  engine->log("rofl test");
}




REGISTER_ENTITY(CBaseEntity)
