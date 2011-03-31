#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include <map>
#include <list>
#include <set>
#include "datatypes.h"
#include "elements/Model.h"

class CBaseEntity;

class EntityRelation{
  public:
    void addRelation(CBaseEntity* ent, const String& input);
    void fire(CBaseEntity* originator);
  protected:
    typedef std::set< std::pair<CBaseEntity*, String> > EntityInputList;
    EntityInputList m_relations;
};

class CBaseEntityDescriptor;

class CBaseEntity{
  public:
    virtual void init();
    virtual void spawn();
    virtual void think();

    virtual void fireInput(const String& name, CBaseEntity* originator);
    virtual void setValue(const String& name, const json::mValue& value);
    virtual void addRelation(const String& output, CBaseEntity* callee, const String& input);

    CBaseEntityDescriptor* m_descriptor;

    virtual ~CBaseEntity(){}

  protected:
    virtual void fireOutput(const String& name);
    virtual void fireOutput(const String& name, CBaseEntity* originator);
    typedef std::map<String, EntityRelation> RelationList;
    RelationList m_relations;
    CBaseEntity* m_originator;

};



namespace json{
  void extract(Model*& result, const mValue& value);
}

class CBaseEntityDescriptor{
  public:
    virtual void registerEntity();
    virtual void doRegister(CBaseEntityDescriptor* descriptor);
    virtual CBaseEntity* create(const json::mValue& value);
    String getClassname();

    void fireInput(const String& name, CBaseEntity* receiver, CBaseEntity* originator);
    void setValue(const String& name, CBaseEntity* entity, const json::mValue& value);
  protected:

    virtual CBaseEntity* createInstance();

    class EntityValueBase{
      public:
        virtual void set(CBaseEntity* entity, const json::mValue& value)=0;
        virtual void setDefault(CBaseEntity* entity);
    };

    template< class T >
    class EntityValue: public EntityValueBase{
      protected:
        T CBaseEntity::*m_value;
      public:
        void set(CBaseEntity* entity, const json::mValue& value){
          json::extract(entity->*m_value, value);
        }
        void set(CBaseEntity* entity, const T& value){
          entity->*m_value = value;
        }
        void setDefault(CBaseEntity* entity){
          entity->*m_value = T();
        }
        EntityValue(T CBaseEntity::*variable):
          m_value(variable)
        {}
    };


    class EntityInputInterface{
      public:
        virtual bool invoke(CBaseEntity* entity, CBaseEntity* originator)=0;
    };

    template< class E >
    class EntityInput: public EntityInputInterface{
      protected:
        typedef void (E::*FunctionType)(CBaseEntity*);
        FunctionType m_function;
      public:
        EntityInput(FunctionType function):
          m_function(function)
        {}
        bool invoke(CBaseEntity* entity, CBaseEntity* originator);

    };

    typedef void (CBaseEntity::*InputType)(CBaseEntity*);
    typedef std::map<String, EntityInputInterface*> InputList;
    typedef std::set<String> OutputList;
    typedef std::map<String, EntityValueBase* > ValueList;

    void classname(const String& value);
    void spawnable(bool value);
    virtual void inherit(){}
    template< typename T > void input(const String& name, void (T::*function)(CBaseEntity*));
    void output(const String& name);
    template< typename T, typename D > void value(const String& name, D T::*variable);

    String m_classname;
    bool m_spawnable;
    CBaseEntityDescriptor* m_currDescriptor;
    InputList m_inputs;
    OutputList m_outputs;
    ValueList m_values;

    friend class CBaseEntity;
};

inline void CBaseEntityDescriptor::registerEntity(){
  classname("CBaseEntity");
  spawnable(false);
}

inline CBaseEntity* CBaseEntityDescriptor::createInstance(){
  return new CBaseEntity;
}

inline void CBaseEntityDescriptor::setValue(const String& name, CBaseEntity* entity, const json::mValue& value){
  m_values[name]->set(entity, value);
}

inline String CBaseEntityDescriptor::getClassname(){
  return m_classname;
}

inline void CBaseEntityDescriptor::classname(const String& value){
  m_classname = value;
}

inline void CBaseEntityDescriptor::spawnable(bool value){
  m_spawnable = value;
}

inline void CBaseEntityDescriptor::doRegister(CBaseEntityDescriptor* descriptor){
  m_currDescriptor = (CBaseEntityDescriptor*)descriptor;
  inherit();
  registerEntity();
}

template< typename T >
inline void CBaseEntityDescriptor::input(const String& name, void (T::*function)(CBaseEntity*)){
  m_currDescriptor->m_inputs[name] = new EntityInput<T>(function);
}

inline void CBaseEntityDescriptor::output(const String& name){
  m_currDescriptor->m_outputs.insert(name);
}

template< typename T, typename D >
inline void CBaseEntityDescriptor::value(const String& name, D T::*variable){
  m_currDescriptor->m_values[name] = new EntityValue<D>((D CBaseEntity::*)variable);
}

template< class E >
bool CBaseEntityDescriptor::EntityInput<E>::invoke(CBaseEntity* entity, CBaseEntity* originator){
  E* correctEntity = dynamic_cast<E*>(entity);
  if(correctEntity == NULL){
    return false;
  }else{
    (correctEntity->*m_function)(originator);
    return true;
  }
}



#endif
