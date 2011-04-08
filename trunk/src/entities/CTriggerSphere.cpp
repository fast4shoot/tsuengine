#include "CTriggerSphere.h"

#include <boost/foreach.hpp>
#include "CBaseEngine.h"

CTriggerSphere::CTriggerSphere():
  CWorldEntity(),
  m_radius(1.),
  m_classname("player")
{}

void CTriggerSphere::think(){
  BOOST_FOREACH(CBaseEntity* ent, engine->ents->m_entities){
    if(ent->m_descriptor->getClassname() == m_classname){
      CWorldEntity* e = dynamic_cast<CWorldEntity*>(ent);
      if(e != NULL){
        /*engine->log(format("%1%, %2%, %3% - %4%, %5%, %6%") % getPosition().x % getPosition().y % getPosition().z % e->getPosition().x % e->getPosition().y % e->getPosition().z );
        engine->log(format("%1%") % (getPosition() - e->getPosition()).length());
        engine->log(format("%1%") % m_radius);*/
        if((getPosition() - e->getPosition()).length() <= m_radius){
          if(m_entsInside.find(e) == m_entsInside.end()){
            fireOutput("onEnter");
            m_entsInside.insert(e);
          }
        }else{
          if(m_entsInside.find(e) != m_entsInside.end()){
            fireOutput("onLeave");
            m_entsInside.erase(e);
          }
        }
      }
    }
  }
}

REGISTER_ENTITY(CTriggerSphere)
