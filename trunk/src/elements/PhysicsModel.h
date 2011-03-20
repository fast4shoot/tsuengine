#ifndef PHYSICSMODEL_H
#define PHYSICSMODEL_H

#include "btBulletDynamicsCommon.h"
#include "json/json.h"

class PhysicsModel{
    public:
      PhysicsModel();
      ~PhysicsModel();
      PhysicsModel(const json::mValue& value);
      btCollisionShape* getCollisionShape() const;
      double getMass() const;
    protected:
      btCollisionShape* m_shape;
      double m_mass;

      btScalar* m_vertices;
      int*  m_indices;
      btStridingMeshInterface* m_meshInterface;
};

inline btCollisionShape* PhysicsModel::getCollisionShape() const{
  return m_shape;
}

inline double PhysicsModel::getMass() const{
  return m_mass;
}

#endif // PHYSICSMODEL_H
