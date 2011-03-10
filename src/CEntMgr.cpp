#include "CEntMgr.h"
#include "entities/CBaseEntity.h"
#include "const.h"

#include <map>
#include <typeinfo>

#include "CBaseEngine.h"
#include "DescriptorList.h"

CEntMgr::CEntMgr():
  m_entityCount(0)
{
  std::vector<CBaseEntityDescriptor*>& l = DescriptorList::instance()->descriptors;
  for(std::vector<CBaseEntityDescriptor*>::iterator it = l.begin(); it != l.end(); ++it){
    (*it)->doRegister(*it);
    m_descriptors[(*it)->getClassname()] = (*it);
  }
}

void CEntMgr::print(){
  engine->log("Zaregistrovane entity: ");
  for(DescriptorMap::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it){
    engine->log((*it).second->getClassname());
  }
}

CBaseEntity* CEntMgr::create(const json::mValue& value){
  try{
    json::mObject::const_iterator cnIt = value.get_obj().find("classname");
    if(cnIt == value.get_obj().end()) throw std::invalid_argument("No classname provided");

    const String& classname = cnIt->second.get_str();
    DescriptorMap::iterator it = m_descriptors.find(classname);

    if(it == m_descriptors.end()) throw std::invalid_argument("Unknown classname "+classname);

    CBaseEntity* ent = it->second->create(value);
    engine->log("Pushing entity back");
    m_entities.push_back(ent);
    engine->log(sformat("Returning entity %s", typeid(ent).name()));
    return ent;
  }catch(std::exception& e){
    engine->warning(String("Can't create entity: ")+e.what());
    return NULL;
  }
}

void CEntMgr::removeAll(){
  for(EntityList::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
    delete (*it);
  }
  m_entities.clear();
}
