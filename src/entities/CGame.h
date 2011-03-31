#ifndef CGAME_H
#define CGAME_H

#include "CLogicEntity.h"

class CGame: public CLogicEntity{
  public:
    void init();
    void spawn();
    bool isBackground;
    void endGame(CBaseEntity* originator);
};

ENTITY_DESCRIPTOR(CGame, CLogicEntity)
  void registerEntity(){
    spawnable(true);
    classname("game_control");
    input("endGame", &CGame::endGame);
    output("onGameStart");
    value("mapIsBackground", &CGame::isBackground);
  }
};

#endif // CGAME_H
