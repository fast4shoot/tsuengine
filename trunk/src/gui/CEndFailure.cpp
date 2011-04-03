#include "CEndFailure.h"

#include "Clabel.h"
#include "CButton.h"
#include "CBaseEngine.h"

CEndFailure::CEndFailure():
  CCenteredWindow(vec2d(500,250),"",65.,false)
{
  addChild(new CLabel(vec2d(0,60), vec2d(getW(), 60.), "Konec hry!", true, CLabel::ALIGN_CENTER));
  CGuiPanel* tmp;
  addChild(tmp = new CButton(vec2d(getW()-150., getH()-45.), vec2d(130., 25.), "Opakovat"));
  tmp->addListener(makeCListenerMemberFn(0,this,&CEndFailure::endFailureAction));
  addChild(tmp = new CButton(vec2d(getW()-300., getH()-45.), vec2d(130., 25.), "Hlavní menu"));
  tmp->addListener(makeCListenerMemberFn(1,this,&CEndFailure::endFailureAction));
}

void CEndFailure::endFailureAction(int id){
  if(id == 0){
    remove();
    engine->map->reload();
  }else if(id == 1){
    remove();
    engine->gui->showMainMenu(true);
  }
}
