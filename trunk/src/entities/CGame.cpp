#include "CGame.h"

#include "CBaseEngine.h"
#include "DescriptorList.h"
#include "gui/CEndFailure.h"
#include "gui/CEndSuccess.h"

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
    m_timerText->setText(formatTime(m_time));
  }
}

void CGame::endGameSuccess(CBaseEntity* originator){
  engine->map->setMapTime(m_time);
  engine->gui->fadeTo(.9, 1.);
  CGuiPanel* temp = new CEndSuccess();
  temp->setOpacity(0.);
  temp->fadeTo(1., 1.);
  engine->setTimeScale(0.);
  engine->gui->addElement(temp);
  engine->gui->enableCursor(true);
  engine->gui->enableEscape(false);

}

void CGame::endGameFailure(CBaseEntity* originator){
  engine->gui->fadeTo(.9, 1.);
  CGuiPanel* temp = new CEndFailure();
  temp->setOpacity(0.);
  temp->fadeTo(1., 1.);
  engine->setTimeScale(0.);
  engine->gui->addElement(temp);
  engine->gui->enableCursor(true);
  engine->gui->enableEscape(false);
}

REGISTER_ENTITY(CGame)
