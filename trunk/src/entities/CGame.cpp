#include "CGame.h"

#include "CBaseEngine.h"
#include "DescriptorList.h"

void CGame::init(){
  isBackground = false;
  m_time = 0;
}

void CGame::spawn(){
  engine->map->setMapAsBackground(isBackground);
  CGuiPanel* hud = engine->gui->getHud();
  engine->log("Adding label");
  hud->addChild(m_startTimerText = new CLabel( vec2d(engine->getScreenWidth()/2., engine->getScreenHeight()/3. ),
                                               vec2d(0., engine->getScreenHeight()/6. ),"", true, CLabel::ALIGN_CENTER));

  hud->addChild(m_timerText = new CLabel( vec2d(engine->getScreenWidth()-10., 6*engine->getScreenHeight()/7-10. ),
                                               vec2d(0., engine->getScreenHeight()/7. ),"0:00.00", true, CLabel::ALIGN_RIGHT));
  fireOutput("onGameStart", this);
  engine->input->setEnabled(false);
}

void CGame::think(){
  if(engine->getTime() < 2.){
  }else if(engine->getTime() < 5.){
    m_startTimerText->setText((format("%1%") % floor(6. - engine->getTime())).str());
  }else if(engine->getTime() < 6.){
    m_startTimerText->setText("Běž!");
    engine->input->setEnabled(true);
  }else{
    m_startTimerText->setText("");
  }
  if(engine->getTime() >= 5.){
    m_time = engine->getTime()-5.;
    int min = floor(m_time/60.);
    int sec = floor(m_time) - min*60.;
    int dec = (m_time - floor(m_time))*100;
    m_timerText->setText((format("%d:%02d.%02d") % min % sec % dec).str());
  }
}

void CGame::endGameSuccess(CBaseEntity* originator){}
void CGame::endGameFailure(CBaseEntity* originator){}

REGISTER_ENTITY(CGame)
