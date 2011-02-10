#ifndef DESCRIPTORLIST_H
#define DESCRIPTORLIST_H

#include <vector>
#include "utils/Singleton.h"
#include "entities/CBaseEntity.h"

class DescriptorList: public Singleton<DescriptorList>{
  public:
    bool registerDescriptor(Descriptor* descriptor);
  protected:
    std::vector<Descriptor*> descriptors;
};

inline bool DescriptorList::registerDescriptor(Descriptor* descriptor){
  descriptors.push_back(descriptor);
}

#endif // DESCRIPTORLIST_H
