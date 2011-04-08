#ifndef CTRIGGERSPHERE_H
#define CTRIGGERSPHERE_H

#include "CWorldEntity.h"


class CTriggerSphere : public CWorldEntity{
  public:
    CTriggerSphere();
    void think();
    double m_radius;
    String m_classname;
  private:
    typedef std::set<CWorldEntity*> EntSet;
    EntSet m_entsInside;
};

ENTITY_DESCRIPTOR(CTriggerSphere, CWorldEntity)
  void registerEntity(){
    classname("trigger_sphere");
    spawnable(true);
    value("radius", &CTriggerSphere::m_radius);
    value("classnameToDetect", &CTriggerSphere::m_classname);
    output("onEnter");
    output("onLeave");
  }
};
#endif // CTRIGGERSPHERE_H
