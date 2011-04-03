#include "CEndSuccess.h"

#include "CLabel.h"
#include "CText.h"
#include "CButton.h"
#include "CBaseEngine.h"
#include "CSubmitScore.h"

CEndSuccess::CEndSuccess():
  CCenteredWindow(vec2d(500,350),"",65.,false)
{
  addChild(new CLabel(vec2d(20.,20.), vec2d(getW()-40., 60.), "Výborně!", true, CLabel::ALIGN_CENTER));
  addChild(new CLabel(vec2d(20.,100.), vec2d(getW()-40., 28.), (format("Váš dosažený čas: %1%") % formatTime(engine->map->getMapTime()) ).str(), true, CLabel::ALIGN_CENTER));

  {
    CText* tmp;
    addChild(tmp = new CText(vec2d(20.,150.), vec2d(getW()-40., 21.), 21., CLabel::ALIGN_CENTER));
    tmp->setText("Pokud chcete čas odeslat na server, stiskněte tlačítko \"Odeslat čas\".");
  }


  CGuiPanel* tmp;

  addChild(tmp = new CButton(vec2d(getW()-150., getH()-45.), vec2d(130., 25.), "Odeslat čas"));
  tmp->addListener(makeCListenerMemberFn(0,this,&CEndSuccess::endSuccessAction));
  addChild(tmp = new CButton(vec2d(getW()-278., getH()-45.), vec2d(130., 25.), "Opakovat"));
  tmp->addListener(makeCListenerMemberFn(1,this,&CEndSuccess::endSuccessAction));
  addChild(tmp = new CButton(vec2d(getW()-406., getH()-45.), vec2d(130., 25.), "Hlavní menu"));
  tmp->addListener(makeCListenerMemberFn(2,this,&CEndSuccess::endSuccessAction));
}

void CEndSuccess::endSuccessAction(int id){
  if(id == 0){
    remove();
    engine->gui->addElement( new CSubmitScore() );
  }else if(id == 1){
    remove();
    engine->map->reload();
  }else if(id == 2){
    remove();
    engine->gui->showMainMenu(true);
  }
}
