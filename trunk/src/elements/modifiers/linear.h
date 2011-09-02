#ifndef MODIFIERS_LINEAR_H
#define MODIFIERS_LINEAR_H

#include "ModifierBase.h"
#include "Modifier.h"

namespace modifiers{
  class linear: public ModifierBase{
    protected:
      Value calculate(){
        return value_cast<double>(increasePerSec)*engine->getTime();
      }
      Value increasePerSec;
    public:
      linear(const PropertyList& properties):
        increasePerSec(properties.find("increasePerSec")->second)
      {}

  };
}

#endif
