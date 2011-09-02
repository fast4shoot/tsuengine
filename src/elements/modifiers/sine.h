#ifndef MODIFIERS_SINE_H
#define MODIFIERS_SINE_H

#include "ModifierBase.h"
#include "Modifier.h"
#include "utils/math.h"

namespace modifiers{
  class sine: public ModifierBase{
    protected:
      Value calculate(){
        double min = value_cast<double>(m_min);
        double max = value_cast<double>(m_max);
        double diff = max - min;
        return ( sin( saw(engine->getTime(), 1. / value_cast<double>(m_cyclesPerSec), 2 * PI ) + 1. ) / 2 ) * diff + min;
      }
      Value m_min;
      Value m_max;
      Value m_cyclesPerSec;
    public:
      sine(const PropertyList& properties):
        m_min(properties.find("min")->second),
        m_max(properties.find("max")->second),
        m_cyclesPerSec(properties.find("cyclesPerSec")->second)
      {}

  };
}

#endif
