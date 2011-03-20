#ifndef CPROPSTATIC_H
#define CPROPSTATIC_H

#include "CWorldEntity.h"

class CPropStatic : public CWorldEntity{
  public:
    void spawn();
    Model* m_model;
};

ENTITY_DESCRIPTOR(CPropStatic, CWorldEntity)
  virtual void registerEntity(){
    spawnable(true);
    classname("prop_static");
    value("model",&CPropStatic::m_model);
  }
};

#endif // CPROPSTATIC_H
