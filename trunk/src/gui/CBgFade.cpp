#include "CBgFade.h"

#include "CBaseEngine.h"
#include "utils/math.h"

CBgFade::CBgFade():
  CGuiPanel(vec2d(), vec2d(engine->getScreenWidth(), engine->getScreenHeight()))
{
  fadeTo(0., 5);
}

void CBgFade::draw(){
  setDrawColor(rgba(0., 0., 0.,1. ));
  drawQuad(0., 0., getW(), getH());
}


