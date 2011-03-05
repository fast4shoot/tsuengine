#include <vector>
#include "CBaseEntity.h"
#include "CBaseEngine.h"
#include "globals.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "CEntMgr.h"
#include "DescriptorList.h"

void CBaseEntity::init(){}

void CBaseEntity::spawn(){}

void CBaseEntity::think(){}

void CBaseEntity::fireInput(const String& name, CBaseEntity* originator){
  CBaseEntity* originatorTemp = m_originator;
  m_originator = originator;
  m_descriptor->fireInput(name, this, originator);
  m_originator = originatorTemp;
}

void CBaseEntity::fireOutput(const String& name){
  RelationList::iterator it = m_relations.find(name);
  if(it != m_relations.end()){
    it->second.fire(m_originator);
  }
}

void CBaseEntity::addRelation(const String& output, CBaseEntity* callee, const String& input){
  m_relations[output].addRelation(callee, input);
}

void CBaseEntity::setValue(const String& name, const json::mValue& value){
  m_descriptor->setValue(name, this, value);
}

void CBaseEntity::print(CBaseEntity* originator){
  engine->log("rofl test");
}

void EntityRelation::addRelation(CBaseEntity* ent, const String& input){
  m_relations.push_back(std::make_pair(ent, input));
}

void EntityRelation::fire(CBaseEntity* originator){
  for(EntityInputList::iterator it = m_relations.begin(); it != m_relations.end(); ++it){
    (*it).first->fireInput((*it).second, originator);
  }
}

REGISTER_ENTITY(CBaseEntity)
