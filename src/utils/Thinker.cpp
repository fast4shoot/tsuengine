#include "Thinker.h"

#include "CBaseEngine.h"

Thinker::Thinker(){
  engine->registerThinker(this);
}
