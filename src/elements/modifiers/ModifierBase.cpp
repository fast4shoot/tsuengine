#include "ModifierBase.h"
#include "CBaseEngine.h"

namespace modifiers{
  Value ModifierBase::get(){
    if(engine->getFrameCount() != m_lastFrame){
      m_value = calculate();
      m_lastFrame = engine->getFrameCount();
    }
    return m_value;
  }
}
