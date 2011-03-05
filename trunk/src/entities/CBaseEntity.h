#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include <map>
#include <list>
#include "datatypes.h"

class CBaseEntityDescriptor;
class EntityRelation;


class CBaseEntity{
  public:
    virtual void init();
    virtual void spawn();
    virtual void think();
    virtual void print(CBaseEntity* originator);

    void fireInput(const String& name, CBaseEntity* originator);
    void setValue(const String& name, const json::mValue& value);
    void addRelation(const String& output, CBaseEntity* callee, const String& input);

    CBaseEntityDescriptor* m_descriptor;

  protected:
    void fireOutput(const String& name);
    typedef std::map<String, EntityRelation> RelationList;
    RelationList m_relations;
    CBaseEntity* m_originator;

};

class EntityRelation{
  public:
    void addRelation(CBaseEntity* ent, const String& input);
    void fire(CBaseEntity* originator);
  protected:
    typedef std::list< std::pair<CBaseEntity*, const String&> > EntityInputList;
    EntityInputList m_relations;
};

#endif
