#ifndef CENTLIST_H
#define CENTLIST_H

#include "entities/CBaseEntity.h"
#include "datatypes.h"
#include "const.h"
#include <map>

class CEntMgr{
  public:
    CEntMgr();
    void print();
    CBaseEntity* create(const json::mValue& value);
    void doThink();
    void doSpawn();
    void removeAll();
  private:
    typedef std::map<String, CBaseEntityDescriptor*> DescriptorMap;
    DescriptorMap m_descriptors;
    typedef std::vector<CBaseEntity*> EntityList;
    int m_entityCount;
    EntityList    m_entities;
};

inline void CEntMgr::doThink(){
  for(EntityList::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
    (*it)->think();
  }
}

inline void CEntMgr::doSpawn(){
  for(EntityList::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
    (*it)->spawn();
  }
}

#endif
