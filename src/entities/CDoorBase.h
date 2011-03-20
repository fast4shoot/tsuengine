#ifndef CDOORBASE_H
#define CDOORBASE_H

#include "CWorldEntity.h"


class CDoorBase : public CWorldEntity{
  public:
    void init();
    virtual void open(CBaseEntity* originator);
    virtual void close(CBaseEntity* originator);
    virtual void toggle(CBaseEntity* originator);
    void think();
    float m_moveSpeed;
  protected:
    bool m_open;
    int m_direction;
    float m_fraction;
};

ENTITY_DESCRIPTOR(CDoorBase, CWorldEntity)
  virtual void registerEntity(){
    spawnable(false);
    classname("CDoorBase");
    value("speed",&CDoorBase::m_moveSpeed);
    input("use",&CDoorBase::toggle);
    input("open",&CDoorBase::open);
    input("close",&CDoorBase::close);
    input("toggle",&CDoorBase::toggle);
    output("onOpen");
    output("onClose");
  }
};


#endif // CDOORBASE_H
