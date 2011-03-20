#ifndef FILTEREDCLOSESTRAYRESULTCALLBACK_H
#define FILTEREDCLOSESTRAYRESULTCALLBACK_H

#include <set>
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

class FilteredClosestRayResultCallback : public btCollisionWorld::ClosestRayResultCallback{
  public:
    FilteredClosestRayResultCallback(const btVector3& rayFromWorld,const btVector3& rayToWorld);
    btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace);
    void addToBlacklist(btCollisionObject* object);
  protected:
    typedef std::set<btCollisionObject*> FilterList;
    FilterList m_filter;
  private:
};

#endif // FILTEREDCLOSESTRAYRESULTCALLBACK_H
