#ifndef MODIFIERS_MODIFIERBASE_H
#define MODIFIERS_MODIFIERBASE_H

#include <boost/shared_ptr.hpp>
#include "Value.h"


namespace modifiers{
  class ModifierBase{
    public:
      Value get();
    protected:
      virtual Value calculate()=0;
    private:
      unsigned long long int m_lastFrame;
      Value m_value;
  };

  typedef boost::shared_ptr<ModifierBase> Modifier;

}

#endif // MODIFIERS_MODIFIERBASE_H
