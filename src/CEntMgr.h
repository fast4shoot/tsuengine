#ifndef CENTLIST_H
#define CENTLIST_H

#include "entities/CBaseEntity.h"
#include "datatypes.h"
#include "const.h"
#include <vector>
#include <list>

class CEntMgr{
  public:
    CEntMgr();
    void print();
    CBaseEntity* create(const String& classname);
    void doThink();
  private:
    typedef std::map<String, CBaseEntityDescriptor*> DescriptorMap;
    DescriptorMap m_descriptors;
    typedef std::list<CBaseEntity*> EntityList;
    EntityList    m_entities;
};

inline void CEntMgr::doThink(){
  for(EntityList::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
    (*it)->think();
  }
}

#endif
