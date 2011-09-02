#ifndef MODIFIER_H
#define MODIFIER_H



#include <vector>
#include "vec2d.h"
#include "json/json.h"
#include "Value.h"
#include "ModifierBase.h"

namespace modifiers{

  class PropertyMgr{
    private:
      std::map<String, ValuePtr> m_properties;
      Value createModifier(const json::mObject& data);
      Value createValue(const json::mValue& data);
    public:
      PropertyMgr(const json::mValue& data);
      Value getValuePointer(const String& name);
      Value getValuePointer(const String& name, const Value& defaultVal);
  };

  template < typename T > T value_cast(const Value& value);

#define MAKE_BASIC_CONVERTOR(finalType) void operator()(const finalType& value){ result = value; }
#define MAKE_MODIFIER_CONVERTOR void operator()(const Modifier& value){ value->get().visit(*this); }
#define MAKE_POINTER_CONVERTOR void operator()(const ValuePtr& value){ value->visit(*this); }
#define MAKE_MAIN_CONVERTORS(finalType) MAKE_BASIC_CONVERTOR(finalType) MAKE_MODIFIER_CONVERTOR MAKE_POINTER_CONVERTOR

  template < typename T >
  class Convertor:
    public any::Visitor<T>,
    public any::Visitor<Modifier>,
    public any::Visitor<ValuePtr>
  {
    public:
      T result;
      MAKE_MAIN_CONVERTORS(T)
  };

  template <>
  class Convertor <double>:
    public any::Visitor<double>,
    public any::Visitor<float>,
    public any::Visitor<int>,
    public any::Visitor<Modifier>,
    public any::Visitor<ValuePtr>
  {
    public:
      double result;
      MAKE_MAIN_CONVERTORS(double)
      MAKE_BASIC_CONVERTOR(float)
      MAKE_BASIC_CONVERTOR(int)
  };

  template <>
  class Convertor <float>:
    public any::Visitor<float>,
    public any::Visitor<int>,
    public any::Visitor<Modifier>,
    public any::Visitor<ValuePtr>
  {
    public:
      float result;
      MAKE_MAIN_CONVERTORS(float)
      MAKE_BASIC_CONVERTOR(int)
  };

  template <>
  class Convertor <int>:
    public any::Visitor<int>,
    public any::Visitor<Modifier>,
    public any::Visitor<ValuePtr>
  {
    public:
      int result;
      MAKE_MAIN_CONVERTORS(int)
  };

  template <>
  class Convertor <vec2d>:
    public any::Visitor<vec2d>,
    public any::Visitor<Modifier>,
    public any::Visitor<ValuePtr>,
    public any::Visitor<VectorValue>
  {
    public:
      vec2d result;
      MAKE_MAIN_CONVERTORS(vec2d)
      void operator()(const VectorValue& value){
        if(value.size() == 2){
          result = vec2d(value_cast<double>(value.at(0)), value_cast<double>(value.at(1)));
        }
      }

  };

  template < typename T >
  inline T value_cast(const Value& value){
    Convertor<T> cnv;
    value.visit(cnv);
    return cnv.result;
  }

}

using modifiers::value_cast;
using modifiers::PropertyMgr;

#endif // MODIFIER_H
