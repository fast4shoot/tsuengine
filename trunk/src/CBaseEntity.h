#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include <string>
#include "datatypes.h"
#include "CParamMgr.h"

class CBaseEntity{
  private: 
    vec3d             pos;
    int               worldModel;
    int               collisionModel;
    MOVETYPE          movetype;
    int               visible;
    
    //parameter manager
    //parameter variables
    std::string       targetname;
  public:
    CParamMgr		  params;
    
    
                      CBaseEntity();
    virtual void      init();
    virtual void      think();
    virtual void      draw();
    virtual void      processCollision(CBaseEntity *collider);
    virtual vec3d     getPos();
};

#endif
