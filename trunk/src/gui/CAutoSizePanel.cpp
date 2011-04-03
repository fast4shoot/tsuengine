#include "CAutoSizePanel.h"

#include "listeners/CListenerMemberFn.h"
#include "CBaseEngine.h"

CAutoSizePanel::CAutoSizePanel():
  CGuiPanel(vec2d(), vec2d())
{
  addListener(makeCListenerMemberFn(0, this, (void(CAutoSizePanel::*)(int))NULL,
                                             (void(CAutoSizePanel::*)(int))NULL,
                                             (void(CAutoSizePanel::*)(int))NULL, &CAutoSizePanel::recalcSizeOnNewChildCallback));
}

void CAutoSizePanel::recalcSizeOnNewChildCallback(int id, CGuiPanel* panel){
  panel->addListener(makeCListenerMemberFn(0, this, (void(CAutoSizePanel::*)(int))NULL, &CAutoSizePanel::recalcSizeCallback, &CAutoSizePanel::recalcSizeCallback));
  recalc();
}

void CAutoSizePanel::recalcSizeCallback(int id){
  recalc();
}

void CAutoSizePanel::recalc(){
  double maxX = 0.;
  double maxY = 0.;
  for(ChildrenList::iterator it = children.begin(); it != children.end(); ++it){
    maxX = std::max((*it)->getX() + (*it)->getW(), maxX);
    maxY = std::max((*it)->getY() + (*it)->getH(), maxY);
  }
  setSize(vec2d(maxX, maxY));
}
