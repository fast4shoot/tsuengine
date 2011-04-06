#ifndef CPROPTOGGLE_H
#define CPROPTOGGLE_H

#include "CPropStatic.h"

class CPropToggle: public CPropStatic{
  public:
    void toggle(CBaseEntity* originator);
    void show(CBaseEntity* originator);
    void hide(CBaseEntity* originator);
};

ENTITY_DESCRIPTOR(CPropToggle, CPropStatic)
  void registerEntity(){
    spawnable(true);
    classname("prop_toggle");
    input("toggle", &CPropToggle::toggle);
    input("show", &CPropToggle::show);
    input("hide", &CPropToggle::hide);
  }
};

#endif // CPROPTOGGLE_H
