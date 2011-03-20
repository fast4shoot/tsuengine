#include "FilteredClosestRayResultCallback.h"

FilteredClosestRayResultCallback::FilteredClosestRayResultCallback(const btVector3& rayFromWorld,const btVector3& rayToWorld):
ClosestRayResultCallback(rayFromWorld, rayToWorld)
{}

btScalar FilteredClosestRayResultCallback::addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace){
  if(m_filter.find(rayResult.m_collisionObject) != m_filter.end()){
	return 1.0;
  }
  return ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
}

void FilteredClosestRayResultCallback::addToBlacklist(btCollisionObject* object){
  m_filter.insert(object);
}
