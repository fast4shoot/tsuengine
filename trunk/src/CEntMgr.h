#ifndef CENTLIST_H
#define CENTLIST_H

#include "entities/CBaseEntity.h"
#include "datatypes.h"
#include "const.h"
#include <vector>

class CEntMgr{
  public:
    CEntMgr();
    void print();
  private:
    typedef std::map<String, CBaseEntityDescriptor*> DescriptorMap;
    DescriptorMap m_descriptors;
//    typedef vector<CBaseEntity> EntityList;
//    EntityList    entities;
};

#endif
