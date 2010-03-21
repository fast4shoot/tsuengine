#ifndef CGUIPANEL_H
#define CGUIPANEL_H

#include <vector>
#include "datatypes.h"
#include "GLFT_Font.hpp"

class CActionListener;

class CGuiPanel{
  public:
    std::vector<CGuiPanel*> children;

                    CGuiPanel(double x, double y, double w, double h);
                    CGuiPanel(const vec2d& pos, const vec2d& size);
                    ~CGuiPanel();
    void            init();
    virtual void    draw();
    virtual void    drawChildren();

    void            setX(double x);
    void            setY(double y);
    void            setPosition(double x, double y);
    void            setPosition(vec2d& newPosition);
    double          getX();
    double          getY();
    vec2d           getPosition();


    void            setW(double w);
    void            setH(double h);
    void            setSize(double w, double h);
    void            setSize(vec2d& newSize);
    double          getW();
    double          getH();
    vec2d           getSize();
    virtual bool    isPointInside(const vec2d& point);

    void            setVisible(bool vis);
    bool            getVisible();
    void            setOpacity(float opacity);
    float           getOpacity();
    void            setParent(CGuiPanel* newParent);
    CGuiPanel*      getParent();
    void            setParentIndex(int newParentIndex);
    int             getParentIndex();
    void            addChild(CGuiPanel* newChild);
    void            removeChild(CGuiPanel* child);
    void            removeChild(int childIndex);
    void            requestFocus();
    void            giveFocusTo(int childIndex);
    std::string     toString();

    //mouse functions
    virtual bool    handleMouseClick(const vec2d& position,const  MouseButton button,const bool up);
    virtual void    onMouseDown(const vec2d& position,const  MouseButton button);
    virtual void    onMouseUp(const vec2d& position, const MouseButton button);
    virtual void    handleMouseMove(const vec2d& newPosition,const  bool mouseOver);
    virtual void    mouseMove(const vec2d& newPosition,const bool mouseOver);
    virtual void    onMouseOver();
    virtual void    onMouseOut();
    bool            getMouseOver();

    void            addActionListener(CActionListener* al);

    void            setBgColor(rgba newBg);
    rgba            getBgColor();
    void            setFgColor(rgba newFg);
    rgba            getFgColor();

    //draw functions
    void            drawQuad(float x, float y, float w, float h);

  protected:
    vec2d           position;
    vec2d           size;
    bool            visible;
    float           opacity;
    CGuiPanel*      parent;
    bool            hasParent;
    int             parentIndex;
    bool            mouseOver;
    bool            allowMouseClickPropagation;
    std::vector<CActionListener*> actionListeners;
    rgba            fgColor;
    rgba            bgColor;
};

inline void CGuiPanel::setX(double x){
  position.x=x;
}

inline void CGuiPanel::setY(double y){
  position.y=y;
}

inline void CGuiPanel::setPosition(double x, double y){
  position.set(x,y);
}

inline void CGuiPanel::setPosition(vec2d& newPosition){
  position=newPosition;
}

inline vec2d CGuiPanel::getPosition(){
  return position;
}

inline double CGuiPanel::getX(){
  return position.x;
}

inline double CGuiPanel::getY(){
  return position.y;
}

inline void CGuiPanel::setW(double w){
  size.x=w;
}

inline void CGuiPanel::setH(double h){
  size.y=h;
}

inline void CGuiPanel::setSize(double w, double h){
  size.set(w,h);
}

inline void CGuiPanel::setSize(vec2d& newSize){
  size=newSize;
}

inline double CGuiPanel::getW(){
  return size.x;
}

inline double CGuiPanel::getH(){
  return size.y;
}

inline vec2d CGuiPanel::getSize(){
  return size;
}

inline bool CGuiPanel::isPointInside(const vec2d& point){
  return point.x>=0. && point.y>=0. && size>point;
}

inline void CGuiPanel::setVisible(bool vis){
  visible=vis;
}

inline bool CGuiPanel::getVisible(){
  return visible;
}

inline void CGuiPanel::setOpacity(float opacity){
  this->opacity=opacity;
}

inline float CGuiPanel::getOpacity(){
  return opacity;
}

inline void CGuiPanel::setParent(CGuiPanel* newParent){
  parent=newParent;
  hasParent=parent!=NULL;
}

inline void CGuiPanel::setParentIndex(int newParentIndex){
  parentIndex=newParentIndex;
}

inline CGuiPanel* CGuiPanel::getParent(){
  return parent;
}

inline int CGuiPanel::getParentIndex(){
  return parentIndex;
}

inline void CGuiPanel::setBgColor(rgba newBg){
  bgColor=newBg;
}

inline rgba CGuiPanel::getBgColor(){
  return bgColor;
}

inline void CGuiPanel::setFgColor(rgba newFg){
  fgColor=newFg;
}

inline rgba CGuiPanel::getFgColor(){
  return fgColor;
}

#endif
