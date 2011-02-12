#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include <map>
#include <set>
#include "datatypes.h"
#include "utils/TemplateFriend.h"

class CBaseEntityDescriptor;

class CBaseEntity{
  public:
    virtual void      think();
    virtual vec3d     getPos();
    virtual void print(CBaseEntity* originator);
    CBaseEntityDescriptor* m_descriptor;
    CBaseEntity* m_originator;

    void fireInput(const String& name, CBaseEntity* originator);
    void setValue(const String& name, const json::mValue& value);

  protected:
    void fireOutput(String name);

  private:
    vec3d             pos;
    int               visible;
};


#endif
