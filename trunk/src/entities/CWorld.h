#ifndef CWORLD_H
#define CWORLD_H

#include "CModelEntity.h"


class CWorld : public CModelEntity{
  public:
    void spawn();
};

ENTITY_DESCRIPTOR(CWorld, CModelEntity)
  virtual void registerEntity(){
    spawnable(true);
    classname("world");
  }
};
#endif // CWORLD_H
