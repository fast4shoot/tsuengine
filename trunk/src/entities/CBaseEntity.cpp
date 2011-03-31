#include "CBaseEntity.h"

#include <vector>
#include "CBaseEngine.h"
#include "globals.h"
#include "macros.h"
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

void CBaseEntity::fireOutput(const String& name, CBaseEntity* originator){
  RelationList::iterator it = m_relations.find(name);
  if(it != m_relations.end()){
    it->second.fire(originator);
  }
}

void CBaseEntity::addRelation(const String& output, CBaseEntity* callee, const String& input){
  if(m_descriptor->m_outputs.find(output) != m_descriptor->m_outputs.end()){
    m_relations[output].addRelation(callee, input);
  }else{
    throw std::runtime_error("Entity "+m_descriptor->getClassname()+" has no output '"+output+"'");
  }
}

void CBaseEntity::setValue(const String& name, const json::mValue& value){
  m_descriptor->setValue(name, this, value);
}

void EntityRelation::addRelation(CBaseEntity* ent, const String& input){
  m_relations.insert(std::make_pair(ent, input));
}

void EntityRelation::fire(CBaseEntity* originator){
  for(EntityInputList::iterator it = m_relations.begin(); it != m_relations.end(); ++it){
    it->first->fireInput(it->second, originator);
  }
}

namespace json{
  void extract(Model*& result, const mValue& value){
    if(engine->isReady()){
      result = engine->models->getModel(value.get_str());
    }
  }
}

CBaseEntity* CBaseEntityDescriptor::create(const json::mValue& value){
  if(!m_spawnable) throw std::logic_error(sformat("Entity %s is not spawnable", m_classname.c_str()));

  CBaseEntity* ent = createInstance();
  ent->m_descriptor = this;

  for(ValueList::iterator it = m_values.begin(); it != m_values.end(); ++it){
    json::mObject::const_iterator vIt = value.get_obj().find(it->first);
    if(vIt != value.get_obj().end()){
      it->second->set(ent, vIt->second);
    }
  }
  ent->init();
  return ent;
}

void CBaseEntityDescriptor::fireInput(const String& name, CBaseEntity* receiver, CBaseEntity* originator){
  if(m_inputs.find(name) == m_inputs.end()) return;
  if(!m_inputs[name]->invoke(receiver,originator)){
    engine->log(sformat("Can't fire input %s of entity %s, probably a programming bug.", name.c_str(), receiver->m_descriptor->getClassname().c_str()));
  }
}

REGISTER_ENTITY(CBaseEntity)
