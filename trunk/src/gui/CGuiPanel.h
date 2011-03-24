#ifndef CGUIPANEL_H
#define CGUIPANEL_H

#include <vector>
#include <boost/foreach.hpp>
#include "datatypes.h"
#include "CGuiMgr.h"
#include "glew/glew.h"

class CListener;

class CGuiPanel{

  public:
                    CGuiPanel(const vec2d& pos, const vec2d& size);
    virtual         ~CGuiPanel();
    virtual void            init();
    virtual void    draw();
    virtual void    drawChildren();
    virtual void    afterDraw();

    void            setX(double x);
    void            setY(double y);
    void            setPosition(double x, double y);
    void            setPosition(const vec2d& newPosition);
    double          getX() const;
    double          getY() const;
    vec2d           getPosition() const;
    void            doPositionChange(const vec2d& newPosition);
    virtual void    positionChanged(){}


    void            setW(double w);
    void            setH(double h);
    void            setSize(double w, double h);
    void            setSize(const vec2d& newSize);
    double          getW() const;
    double          getH() const;
    vec2d           getSize() const;
    void            doSizeChange(const vec2d& newSize);
    virtual void    sizeChanged(){}

    virtual bool    isPointInside(const vec2d& point);


    void            setVisible(bool vis);
    bool            getVisible() const;
    bool            isVisible() const;
    void            setOpacity(float opacity);
    float           getOpacity() const;

    CGuiPanel*      getParent() const;

    int             getParentIndex() const;
    void            addChild(CGuiPanel* newChild);
    void            removeChild(CGuiPanel* child);
    void            removeChild(int childIndex);
    void            deleteChildren();
    void            requestFocus();
    void            giveFocusTo(int childIndex);

    //mouse functions
    virtual bool    handleMouseClick(const vec2d& position,const  MouseButton button,const bool up);
    virtual void    onMouseDown(const vec2d& position,const  MouseButton button){};
    virtual void    onMouseUp(const vec2d& position, const MouseButton button){};
    virtual void    onMouseClick(const vec2d& position, const MouseButton button){};
    virtual void    handleMouseMove(const vec2d& newPosition,const  bool mouseOver);
    virtual void    mouseMove(const vec2d& newPosition,const bool mouseOver){};
    virtual void    onMouseOver(){};
    virtual void    onMouseOut(){};
    bool            getMouseOver() const;
    bool            getMouseDown() const;

    //keyboard function
    virtual void    onKeyboard(const String& string){};
    void            requestKeyboardFocus();
    bool            getAllowKeyboardInput() const;
    void            addListener(CListener* al);

    //basic color functions
    void            setBgColor(rgba newBg);
    rgba            getBgColor() const;
    void            setFgColor(rgba newFg);
    rgba            getFgColor() const;

    //drawing functions
    void            setDrawColor(const rgba& color);
    void            drawQuad(float x, float y, float w, float h);
    void            drawVerticalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo);
    void            drawHorizontalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo);
    void            drawFrame(float x, float y, float w, float h);

  protected:
    typedef std::vector<CListener*> ListenerList;
    typedef std::vector<CGuiPanel*> ChildrenList;
    void            setParent(CGuiPanel* newParent);
    void            setParentIndex(int newParentIndex);
    void            fireListeners();
    void            firePositionChanged();
    void            fireSizeChanged();
    void            fireChildAdded(CGuiPanel* child);

    ChildrenList    children;
    ListenerList    listeners;
    vec2d           position;
    vec2d           size;
    bool            visible;
    float           opacity;
    CGuiPanel*      parent;
    bool            hasParent;
    int             parentIndex;
    bool            mouseOver;
    bool            mouseDown;
    bool            allowMouseClickPropagation;
    bool            allowKeyboardInput;
    rgba            fgColor;
    rgba            bgColor;
    rgba            glossColor;

};

inline CGuiPanel::~CGuiPanel(){
  deleteChildren();
}

inline CGuiPanel::CGuiPanel(const vec2d& position, const vec2d& size){
  init();
  this->position=position;
  this->size=size;
}

inline void CGuiPanel::draw(){}

inline void CGuiPanel::afterDraw(){}

inline void CGuiPanel::setX(double x){
  doPositionChange(vec2d(x, getY()));
}

inline void CGuiPanel::setY(double y){
  doPositionChange(vec2d(getX(), y));
}

inline void CGuiPanel::setPosition(double x, double y){
  doPositionChange(vec2d(x, y));
}

inline void CGuiPanel::setPosition(const vec2d& newPosition){
  doPositionChange(newPosition);
}

inline vec2d CGuiPanel::getPosition() const{
  return position;
}

inline double CGuiPanel::getX() const{
  return position.x;
}

inline double CGuiPanel::getY() const{
  return position.y;
}

inline void CGuiPanel::doPositionChange(const vec2d& newPosition){
  if(position!=newPosition){
    position=newPosition;
    firePositionChanged();
  }
}

inline void CGuiPanel::setW(double w){
  doSizeChange(vec2d(w, getH()));
}

inline void CGuiPanel::setH(double h){
  doSizeChange(vec2d(getW(), h));
}

inline void CGuiPanel::setSize(double w, double h){
  doSizeChange(vec2d(w, h));
}

inline void CGuiPanel::setSize(const vec2d& newSize){
  doSizeChange(newSize);
}

inline double CGuiPanel::getW() const{
  return size.x;
}

inline double CGuiPanel::getH() const{
  return size.y;
}

inline vec2d CGuiPanel::getSize() const{
  return size;
}

inline void CGuiPanel::doSizeChange(const vec2d& newSize){
  if(size!=newSize){
    size=newSize;
    fireSizeChanged();
  }
}

inline bool CGuiPanel::isPointInside(const vec2d& point){
  return point.x>=0. && point.y>=0. && size>point;
}

inline void CGuiPanel::setVisible(bool vis){
  visible=vis;
}

inline bool CGuiPanel::getVisible() const{
  return visible;
}

inline void CGuiPanel::setOpacity(float opacity){
  this->opacity=opacity;
}

inline float CGuiPanel::getOpacity() const{
  return opacity;
}

inline void CGuiPanel::setParent(CGuiPanel* newParent){
  parent=newParent;
  hasParent=parent!=NULL;
}

inline void CGuiPanel::setParentIndex(int newParentIndex){
  parentIndex=newParentIndex;
}

inline CGuiPanel* CGuiPanel::getParent() const{
  return parent;
}

inline bool CGuiPanel::getMouseOver() const{
  return mouseOver;
}

inline bool CGuiPanel::getMouseDown() const{
  return mouseDown;
}

inline int CGuiPanel::getParentIndex() const{
  return parentIndex;
}

inline bool CGuiPanel::getAllowKeyboardInput() const{
  return allowKeyboardInput;
}

inline void CGuiPanel::setBgColor(rgba newBg){
  bgColor=newBg;
}

inline rgba CGuiPanel::getBgColor() const{
  return bgColor;
}

inline void CGuiPanel::setFgColor(rgba newFg){
  fgColor=newFg;
}

inline rgba CGuiPanel::getFgColor() const{
  return fgColor;
}

inline void CGuiPanel::setDrawColor(const rgba& color){
  glColor4f(color.r,color.g,color.b,color.a);
}
#endif
