#ifndef DESCRIPTORLIST_H
#define DESCRIPTORLIST_H

#include <vector>
#include "utils/Singleton.h"
#include "entities/CBaseEntityDescriptor.h"

class DescriptorList: public Singleton<DescriptorList>{
  public:
    bool registerDescriptor(CBaseEntityDescriptor* descriptor);
  protected:
    std::vector<CBaseEntityDescriptor*> descriptors;
  friend class CEntMgr;
};

inline bool DescriptorList::registerDescriptor(CBaseEntityDescriptor* descriptor){
  descriptors.push_back(descriptor);
}

#endif // DESCRIPTORLIST_H
