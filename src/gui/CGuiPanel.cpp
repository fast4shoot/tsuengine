#include "CGuiPanel.h"
#include "macros.h"
#include <gl/gl.h>
#include <typeinfo>
#include "CActionListener.h"

void CGuiPanel::init(){
  position.set(0.,0.);
  parent=NULL;
  opacity=1.;
  visible=true;
  mouseOver=false;
  mouseDown=false;
  children.reserve(8);
  allowMouseClickPropagation=true;
  fgColor.set(1.,1.,1.,1.);
  bgColor.set(0.,0.,0.,.25);
  glossColor.set(1., 1., 1., .1);
}

bool CGuiPanel::isVisible()  const{
  if(parent){
    return getVisible() && parent->isVisible();
  }else{
    return getVisible();
  }
}

void CGuiPanel::addChild(CGuiPanel* newChild){
  newChild->setParent(this);
  newChild->setParentIndex(children.size());
  children.push_back(newChild);
  fireChildAdded(newChild);
}

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
  children.at(childIndex)->setParent(NULL);
  children.erase(children.begin()+childIndex);
}



void CGuiPanel::drawChildren(){
  for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i){
    CGuiPanel* child=*i;
    if(child->getVisible()){
      glPushMatrix();
      glTranslatef(child->getX(),child->getY(),0.);
      child->draw();
      child->drawChildren();
      child->afterDraw();
      glPopMatrix();
    }
  }
}

void CGuiPanel::requestFocus(){
  parent->giveFocusTo(parentIndex);
}

void CGuiPanel::giveFocusTo(int childIndex){
  if(children.size()-1!=childIndex){         //if the child already has focus, do nothing
    CGuiPanel* temp = children.at(childIndex);
    children.erase(children.begin()+childIndex);
    children.push_back(temp);

    //now update the indexes for affected children
    for(int i=childIndex;i<children.size();i++){
      children.at(i)->setParentIndex(i);
    }
  }
}

std::string CGuiPanel::toString(){
  char buff[1024];
  //sprintf(buff,"CGuiPanel[x=%.0lf,y=%.0lf,w=%.0lf,h=%.0lf]",position.x,position.y,size.x,size.y);
  std::string ret=buff;
  return ret;
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

void CGuiPanel::addActionListener(CActionListener* al){
  actionListeners.push_back(al);
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

void CGuiPanel::setDrawColor(const rgba& color){
  glColor4f(color.r,color.g,color.b,color.a);
}

void CGuiPanel::fireListeners(){
  for(ActionListenerList::iterator it = actionListeners.begin(); it!=actionListeners.end(); ++it){
    (*it)->actionPerformed();
  }
}

void CGuiPanel::firePositionChanged(){
  positionChanged();
  for(ActionListenerList::iterator it = actionListeners.begin(); it!=actionListeners.end(); ++it){
    (*it)->positionChangePerformed();
  }
}

void CGuiPanel::fireSizeChanged(){
  sizeChanged();
  for(ActionListenerList::iterator it = actionListeners.begin(); it!=actionListeners.end(); ++it){
    (*it)->sizeChangePerformed();
  }
}

void CGuiPanel::fireChildAdded(CGuiPanel* child){
  for(ActionListenerList::iterator it = actionListeners.begin(); it!=actionListeners.end(); ++it){
    (*it)->addChildPerformed(child);
  }
}
