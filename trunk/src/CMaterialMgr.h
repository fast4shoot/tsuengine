#ifndef CMATERIALMGR_H
#define CMATERIALMGR_H

#include <map>
#include "typedefs.h"
#include "elements/Material.h"

class CMaterialMgr{
  typedef std::map<String,Material*> MaterialList;
  public:
    CMaterialMgr();
    Material* getMaterial(const String& name);
    Material* getPersistentMaterial(const String& name);
    void removeAll();
  protected:
    MaterialList matList;
};

#endif // CMATERIALMGR_H
