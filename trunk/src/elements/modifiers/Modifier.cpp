#include "Modifier.h"
#include <vector>
#include "CBaseEngine.h"
#include <boost/foreach.hpp>
#include "Linear.h"
#include "Sine.h"

namespace modifiers{

  PropertyMgr::PropertyMgr(const json::mValue& data){
    const json::mObject& obj = data.get_obj();
    BOOST_FOREACH(const json::mObject::value_type& properties, obj){
      engine->log("Property "+properties.first+"...");
      m_properties[properties.first] = ValuePtr(new Value(createValue(properties.second)));
    }
  }

#define MODIFIER_CREATE(className) if(type == #className) return Modifier(new className(properties))

  Value PropertyMgr::createModifier(const json::mObject& data){
    String type = data.begin()->first;
    PropertyList properties;
    engine->log("Modifier "+type);
    BOOST_FOREACH(const json::mObject::value_type& property, data.begin()->second.get_obj()){
      engine->log("Modifier property: "+property.first);
      properties[property.first] = createValue(property.second);
    }
    MODIFIER_CREATE(linear);
    MODIFIER_CREATE(sine);
  }

  Value PropertyMgr::createValue(const json::mValue& data){
    engine->log("createValue()");
    switch(data.type()){
      case json::int_type: engine->log("int_type"); return data.get_int(); break;
      case json::real_type: engine->log("real_type"); return data.get_real(); break;
      case json::str_type: engine->log("str_type"); return data.get_str(); break;
      case json::bool_type: engine->log("bool_type"); return data.get_bool(); break;
      case json::obj_type: {
        engine->log("obj_type");
        const json::mObject& obj = data.get_obj();
        if(obj.size() == 1){  // one property means this is probably a modifier
          return createModifier(obj);
        }
      }
      break;
      case json::array_type: {
        engine->log("array_type");
        VectorValue vec;
        BOOST_FOREACH(const json::mValue& val, data.get_array()){
          vec.push_back(createValue(val));
        }
        return vec;
      }
      break;
    }
  }

  Value PropertyMgr::getValuePointer(const String& name){
    engine->log("Finding "+name);
    if(m_properties.find(name) != m_properties.end()){
      engine->log("Found it!");
      return m_properties[name];
    }else{
      throw std::runtime_error("Couldn't find property named '"+name+"'");
    }
  }

  Value PropertyMgr::getValuePointer(const String& name, const Value& defaultVal){
    if(m_properties.find(name) == m_properties.end()){
      m_properties[name] = ValuePtr(new Value(defaultVal));
    }
    return m_properties[name];
  }

}
