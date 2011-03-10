#ifndef CVISIBLEENTITY_H
#define CVISIBLEENTITY_H

#include "CBaseEntity.h"
#include "DescriptorList.h"


class CVisibleEntity: public CBaseEntity{
  public:
  protected:
};

ENTITY_DESCRIPTOR(CVisibleEntity, CBaseEntity)
  virtual void registerEntity(){
    spawnable(false);
    classname("CVisibleEntity");
  }
};


#endif // CVISIBLEENTITY_H
