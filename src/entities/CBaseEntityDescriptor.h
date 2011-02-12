#ifndef CBASEENTITYDESCRIPTOR_H
#define CBASEENTITYDESCRIPTOR_H

#include "entities/CBaseEntity.h"
#include "CBaseEngine.h"

class CBaseEntityDescriptor{
  public:
    typedef CBaseEntity EntityType;
    virtual void registerEntity();
    virtual void doRegister(CBaseEntityDescriptor* descriptor);
    virtual CBaseEntity* create();
    virtual String getClassname();

    void fireInput(const String& name, CBaseEntity* receiver, CBaseEntity* originator);
    void setValue(const String& name, CBaseEntity* entity, const json::mValue& value);
  protected:

    virtual CBaseEntity* createInstance();

    class EntityValueBase{
      public:
        virtual void set(EntityType* entity, const json::mValue& value)=0;
    };

    template< class T >
    class EntityValue: public EntityValueBase{
      protected:
        T EntityType::*m_value;
        T m_default;
      public:
        void set(EntityType* entity, const json::mValue& value){
          json::extract(entity->*m_value, value);
        }
        EntityValue(T EntityType::*variable, const T& defaultVal):
          m_value(variable),
          m_default(defaultVal)
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

    typedef void (EntityType::*InputType)(CBaseEntity*);
    typedef std::map<String, EntityInputInterface*> InputList;
    typedef std::set<String> OutputList;
    typedef std::map<String, EntityValueBase* > ValueList;

    void classname(const String& value);
    void spawnable(bool value);
    template< typename T > void inherit();
    template< typename T > void input(const String& name, void (T::*function)(CBaseEntity*));
    void output(const String& name);
    template< typename T, typename D > void value(const String& name, D T::*variable, const D& defaultValue);

    String m_classname;
    bool m_spawnable;
    CBaseEntityDescriptor* m_currDescriptor;
    InputList m_inputs;
    OutputList m_outputs;
    ValueList m_values;
    //std::list<CBaseEntityDescriptor*> m_parents;

    friend class CEntMgr;
    //friend class EntityType;
};

inline void CBaseEntityDescriptor::registerEntity(){
  classname("CBaseEntity");
  spawnable(false);
  input("print",&CBaseEntity::print);
}

inline CBaseEntity* CBaseEntityDescriptor::create(){
  EntityType* temp = createInstance();
  temp->m_descriptor = this;
  return temp;
}

inline CBaseEntity* CBaseEntityDescriptor::createInstance(){
  return new CBaseEntity();
}

inline void CBaseEntityDescriptor::fireInput(const String& name, CBaseEntity* receiver, CBaseEntity* originator){
  if(!m_inputs[name]->invoke(receiver,originator)){
    engine->log(sformat("Can't fire input %s of entity %s, probably a programming bug.", name.c_str(), receiver->m_descriptor->getClassname().c_str()));
  }
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
  registerEntity();
}

template< typename T >
inline void CBaseEntityDescriptor::inherit(){
  T parent = T();
  parent.doRegister(m_currDescriptor);
  //m_parents.push_back(temp);
}

template< typename T >
inline void CBaseEntityDescriptor::input(const String& name, void (T::*function)(CBaseEntity*)){
  m_currDescriptor->m_inputs[name] = new EntityInput<T>(function);
}

inline void CBaseEntityDescriptor::output(const String& name){
  m_currDescriptor->m_outputs.insert(name);
}

template< typename T, typename D >
inline void CBaseEntityDescriptor::value(const String& name, D T::*variable, const D& defaultValue){
  m_values[name] = new EntityValue<D>((D CBaseEntity::*)variable, defaultValue);
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


#endif // CBASEENTITYDESCRIPTOR_H
