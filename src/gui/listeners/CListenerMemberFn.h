#ifndef CLISTENERMEMBERFN_H
#define CLISTENERMEMBERFN_H

#include "CListener.h"

template<class idType, class objectType>
class CListenerMemberFn: public CListener{
  typedef void (objectType::*fn0)(idType);
  typedef void (objectType::*fn1)(idType, CGuiPanel*);

  public:
                    CListenerMemberFn(idType id, objectType* object, fn0 actionFn=NULL, fn0 positionChangeFn=NULL, fn0 sizeChangeFn=NULL, fn1 addChildFn=NULL);
    virtual void    actionPerformed();
    virtual void    positionChangePerformed();
    virtual void    sizeChangePerformed();
    virtual void    addChildPerformed(CGuiPanel* child);

  protected:
    idType _id;
    objectType* _object;
    fn0 _actionFn;
    fn0 _positionChangeFn;
    fn0 _sizeChangeFn;
    fn1 _addChildFn;

};

template<class idType, class objectType>
CListenerMemberFn<idType, objectType>::CListenerMemberFn(idType id, objectType* object, fn0 actionFn, fn0 positionChangeFn, fn0 sizeChangeFn, fn1 addChildFn){
  _id = id;
  _object = object;
  _actionFn = actionFn;
  _positionChangeFn = positionChangeFn;
  _sizeChangeFn = sizeChangeFn;
  _addChildFn = addChildFn;
}

template<class idType, class objectType>
void CListenerMemberFn<idType, objectType>::actionPerformed(){
  if(_actionFn){
    (_object->*_actionFn)(_id);
  }
}

template<class idType, class objectType>
void CListenerMemberFn<idType, objectType>::positionChangePerformed(){
  if(_positionChangeFn){
    (_object->*_positionChangeFn)(_id);
  }
}

template<class idType, class objectType>
void CListenerMemberFn<idType, objectType>::sizeChangePerformed(){
  if(_sizeChangeFn){
    (_object->*_sizeChangeFn)(_id);
  }
}

template<class idType, class objectType>
void CListenerMemberFn<idType, objectType>::addChildPerformed(CGuiPanel* child){
  if(_addChildFn){
    (_object->*_addChildFn)(_id, child);
  }
}

template<class idType, class objectType>
inline CListenerMemberFn<idType, objectType>* makeCListenerMemberFn(idType id, objectType* object,
                                                                                void (objectType::*actionFn)(idType) =NULL,
                                                                                void (objectType::*positionChangeFn)(idType) =NULL,
                                                                                void (objectType::*sizeChangeFn)(idType) =NULL,
                                                                                void (objectType::*addChildFn)(idType, CGuiPanel*) =NULL)
{
  return new CListenerMemberFn<idType, objectType>(id, object, actionFn, positionChangeFn, sizeChangeFn, addChildFn);
}

#endif // CACTIONLISTENERMEMBERFN_H
