#include "CGuiPanel.h"
#include "macros.h"

#include <typeinfo>
#include "listeners/CListener.h"
#include "CBaseEngine.h"
#include "utils/math.h"
#include <algorithm>
#include <boost/foreach.hpp>


void CGuiPanel::init(){
  position.set(0.,0.);
  parent=NULL;
  opacity=1.;
  visible=true;
  mouseOver=false;
  mouseDown=false;
  allowMouseClickPropagation=true;
  fgColor.set(1.,1.,1.,1.);
  bgColor.set(0.,0.,0.,.25);
  glossColor.set(1., 1., 1., .1);
  m_alphaStart = (1.);
  m_alphaEnd = (1.);
  m_timeStart = (0.);
  m_time = (1.);
  m_remove = false;
  m_checkForRemoval = false;
  m_hideAfterFade = false;
}

CGuiPanel::~CGuiPanel(){
  deleteChildren();
  deleteListeners();
  engine->gui->stopKeyboardReceiving(this);
}

void CGuiPanel::remove(){
  m_remove = true;
  if(getParent()){
    getParent()->notifyRemoval();
  }
}

void CGuiPanel::notifyRemoval(){
  m_checkForRemoval = true;
  if(getParent()){
    getParent()->notifyRemoval();
  }
}



void CGuiPanel::doRemoval(){
  if(m_checkForRemoval){
    for(ChildrenList::iterator it = children.begin(); it != children.end();){
      if((*it)->m_remove){
        delete *it;
        it = children.erase(it);
      }else{
        ++it;
      }
    }
  }
  BOOST_FOREACH(CGuiPanel* pnl, children){
    pnl->doRemoval();
  }
}

bool CGuiPanel::isVisible()  const{
  if(parent){
    return getVisible() && parent->isVisible();
  }else{
    return getVisible();
  }
}

void CGuiPanel::addChild(CGuiPanel* newChild){
  children.remove(newChild);
  newChild->setParent(this);
  //newChild->setParentIndex(children.size());
  children.push_back(newChild);
  fireChildAdded(newChild);
}

/*
void CGuiPanel::removeChild(CGuiPanel* child){
  int size=children.size();
  for (int i=0; i<size; i++){
    if(children.at(i)==child){
      removeChild(i);
      break;
    }
  }
}

void CGuiPanel::removeChild(int childIndex){
  delete children[childIndex];
  children.erase(children.begin()+childIndex);
}
*/

void CGuiPanel::doDraw(){
  calcOpacity();
  draw();
  drawChildren();
  afterDraw();
}

void CGuiPanel::drawChildren(){
  for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i){
    CGuiPanel* child=*i;
    if(child->getVisible()){
      glPushMatrix();
      glTranslatef(child->getX(),child->getY(),0.);
      child->doDraw();
      glPopMatrix();
    }
  }
}

void CGuiPanel::requestFocus(){
  parent->giveFocusTo(this);
}

void CGuiPanel::giveFocusTo(CGuiPanel* child){
  if(*(children.rbegin()) != child){         //if the child already has focus, do nothing
    ChildrenList::iterator it = std::find(children.begin(), children.end(), child);
    if(it != children.end()){
      children.erase(it);
      children.push_back(child);
    }
  }
}

bool CGuiPanel::handleMouseClick(const vec2d& position, const MouseButton button, const bool up){
  bool childrenHasKeyboard=false;
  for(ChildrenList::reverse_iterator it = children.rbegin(); it != children.rend(); ++it){
    CGuiPanel* child=*it;
    vec2d positionInChild = position-(child->getPosition());
    if( child->getVisible() && child->isPointInside( positionInChild ) ){
      childrenHasKeyboard=true;
      if(child->handleMouseClick(positionInChild, button, up)){
        break;
      }else{
        return false;
      }
    }
  }
  bool wasMouseDown=mouseDown;
  mouseDown=!up;
  if(wasMouseDown && up){
    onMouseClick(position,button);
  }
  up?onMouseUp(position,button):onMouseDown(position,button);
  if(!up && !childrenHasKeyboard){
    requestKeyboardFocus();
  }
  return allowMouseClickPropagation;
}

void CGuiPanel::handleMouseMove(const vec2d& newPosition, const bool mouseOver){
  vec2d positionInChild;
  bool itemFound=false;

  for(ChildrenList::reverse_iterator it = children.rbegin(); it != children.rend(); ++it){
    CGuiPanel* child=*it;
    positionInChild = newPosition-(child->getPosition());
    if(!itemFound && child->getVisible() && child->isPointInside( positionInChild )){
      child->handleMouseMove( positionInChild, true);
      itemFound=true;
    }else{
      if(child->getMouseOver()){
        child->handleMouseMove( positionInChild, false);
      }
    }
  }
  if(getMouseOver() && !mouseOver){
    onMouseOut();
  }
  if(!getMouseOver() && mouseOver){
    onMouseOver();
  }

  this->mouseOver=mouseOver;

  if(newPosition.x!=0. && newPosition.y!=0.){
    mouseMove(newPosition,mouseOver);
  }
}

void CGuiPanel::addListener(CListener* al){
  listeners.push_back(al);
}

void CGuiPanel::drawQuad(float x, float y, float w, float h){
  glBegin(GL_QUADS);
  glVertex2f(x+w,y);
  glVertex2f(x,y);
  glVertex2f(x,y+h);
  glVertex2f(x+w,y+h);
  glEnd();
}

void CGuiPanel::drawVerticalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo){
  glBegin(GL_QUADS);
  setDrawColor(colOne);
  glVertex2f(x+w,y);
  glVertex2f(x,y);
  setDrawColor(colTwo);
  glVertex2f(x,y+h);
  glVertex2f(x+w,y+h);
  glEnd();
}

void CGuiPanel::drawHorizontalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo){
  glBegin(GL_QUADS);
  setDrawColor(colOne);
  glVertex2f(x,y);
  glVertex2f(x,y+h);
  setDrawColor(colTwo);
  glVertex2f(x+w,y+h);
  glVertex2f(x+w,y);
  glEnd();
}

void CGuiPanel::drawFrame(float x, float y, float w, float h){
  drawQuad(x,      y+1,    1.,   h-2.);
  drawQuad(x+1.,   y,      w-2., 1.);
  drawQuad(x+w-1., y+1.,   1.,   h-2);
  drawQuad(x+1.,   y+h-1., w-2., 1.);
}



void CGuiPanel::fireListeners(){
  for(ListenerList::iterator it = listeners.begin(); it!=listeners.end(); ++it){
    (*it)->actionPerformed();
  }
}

void CGuiPanel::firePositionChanged(){
  positionChanged();
  for(ListenerList::iterator it = listeners.begin(); it!=listeners.end(); ++it){
    (*it)->positionChangePerformed();
  }
}

void CGuiPanel::fireSizeChanged(){
  sizeChanged();
  for(ListenerList::iterator it = listeners.begin(); it!=listeners.end(); ++it){
    (*it)->sizeChangePerformed();
  }
}

void CGuiPanel::fireChildAdded(CGuiPanel* child){
  for(ListenerList::iterator it = listeners.begin(); it!=listeners.end(); ++it){
    (*it)->addChildPerformed(child);
  }
}

void CGuiPanel::requestKeyboardFocus(){
  engine->gui->setKeyboardReceiver(this);
}

void CGuiPanel::deleteChildren(){
  BOOST_FOREACH(CGuiPanel* pnl, children){
    delete pnl;
  }
  children.clear();
}

void CGuiPanel::deleteListeners(){
  BOOST_FOREACH(CListener* lstnr, listeners){
    delete lstnr;
  }
  listeners.clear();
}

void CGuiPanel::fadeTo(double alpha, double time, bool hideAfterFade){
  m_timeStart = engine->getRealTime();
  m_time = time;
  m_alphaStart = opacity;
  m_alphaEnd = alpha;
  m_hideAfterFade = hideAfterFade;
}

void CGuiPanel::calcOpacity(){
  opacity = (engine->getRealTime()-m_timeStart)/m_time;

  if(m_hideAfterFade && opacity >= 1.){
    visible = false;
    m_hideAfterFade = false;
  }

  opacity = clamp(double(opacity), 0., 1.);
  opacity = m_alphaStart+(m_alphaEnd-m_alphaStart)*opacity;

  if(getParent()){
    m_calculatedOpacity = getParent()->m_calculatedOpacity * opacity;
  }else{
    m_calculatedOpacity = opacity;
  }

}

void CGuiPanel::setVisible(bool vis){
  if(!visible && vis){
    setOpacity(0.);
    fadeTo(1., 0.5);
    visible=vis;
  }
  if(visible && !vis){
    fadeTo(0., 0.25, true);
  }

}
