#ifndef CGAME_H
#define CGAME_H

#include "CLogicEntity.h"
#include "gui/CLabel.h"

class CGame: public CLogicEntity{
  public:
    void init();
    void spawn();
    void think();
    bool isBackground;
    void endGameSuccess(CBaseEntity* originator);
    void endGameFailure(CBaseEntity* originator);
  protected:
    CLabel* m_startTimerText;
    CLabel* m_timerText;
    double m_time;
};

ENTITY_DESCRIPTOR(CGame, CLogicEntity)
  void registerEntity(){
    spawnable(true);
    classname("game_control");
    input("endGameSuccess", &CGame::endGameSuccess);
    input("endGameFailure", &CGame::endGameFailure);
    output("onGameStart");
    value("mapIsBackground", &CGame::isBackground);
  }
};

#endif // CGAME_H
