#ifndef CBASEENTITY_H
#define CBASEENTITY_H

#include <string>
#include <list>
#include "datatypes.h"
#include "CParamMgr.h"

class CBaseEntity{
  private:
    vec3d             pos;
    int               visible;

    //parameter manager
    //parameter variables
  public:


    virtual void      think();
    virtual vec3d     getPos();

    Descriptor* m_descriptor;
};

class Descriptor{

};

template< class EntityType >
class CBaseEntityDescriptor: public Descriptor{
  public:
    void registerEntity();
    void doRegister(CBaseEntityDescriptor* descriptor);
    CBaseEntity* create();
  protected:

    class EntityValueBase{
      public:
        virtual void set(json::mValue value)=0;
    };

    template<class T >
    class EntityValue: public EntityValueBase{
      protected:
        T EntityType::*m_value;
        T m_default;
      public:
        void set(EntityType* entity, const json::mValue& value){
          json::extract(entity->*m_value, value);
        }
        EntityValue(T EntityType::*variable, const T& defaultVal){
          m_value = variable;
          m_default = defaultVal;
        }
    };

    typedef void (EntityType::*InputType)(CBaseEntity*);
    typedef InputType OutputType;
    typedef std::map<String, InputType> InputList;
    typedef std::map<String, OutputType> OutputList;
    typedef std::map<String, EntityValueBase* > ValueList;

    void classname(const String& value);
    void spawnable(bool value);
    template< typename T > void inherit();
    void input(String name, InputType function);
    void output(String name, OutputType function);
    template< typename T > void value(String name, T EntityType::*variable, const T& defaultValue);

    String m_classname;
    bool m_spawnable;
    CBaseEntityDescriptor* m_currDescriptor;
    InputList m_inputs;
    OutputList m_outputs;
    ValueList m_values;
    //std::list<CBaseEntityDescriptor*> m_parents;

    friend class CEntMgr;
};

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::registerEntity(){
  classname("CBaseEntity");
  spawnable(false);
}

template< class EntityType >
inline CBaseEntity* CBaseEntityDescriptor<EntityType>::create(){

}

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::classname(const String& value){
  m_classname = value;
}

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::spawnable(bool value){
  m_spawnable = value;
}

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::doRegister(CBaseEntityDescriptor* descriptor){
  m_currDescriptor = descriptor;
  registerEntity();
}

template< class EntityType >
template< typename T >
void CBaseEntityDescriptor<EntityType>::inherit(){
  T parent = T();
  parent.doRegister(m_currDescriptor);
  //m_parents.push_back(temp);
}

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::input(String name, InputType function){
  m_currDescriptor->m_input[name] = function;
}

template< class EntityType >
inline void CBaseEntityDescriptor<EntityType>::output(String name, OutputType function){
  m_currDescriptor->m_ouputs[name] = function;
}

template< class EntityType >
template< typename T >
inline void CBaseEntityDescriptor<EntityType>::value(String name, T EntityType::*variable, const T& defaultValue){
  m_values[name] = new EntityValue<T>(variable, defaultValue);
}

#endif
