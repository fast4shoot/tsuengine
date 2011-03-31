#ifndef CLOGICENTITY_H
#define CLOGICENTITY_H

#include "CBaseEntity.h"
#include "CBaseEntityDescriptor.h"


class CLogicEntity : public CBaseEntity{
  public:
};

ENTITY_DESCRIPTOR(CLogicEntity, CBaseEntity)
  virtual void registerEntity(){
    classname("CLogicEntity");
    spawnable(false);
  }
};

#endif // CLOGICENTITY_H
