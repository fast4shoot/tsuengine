#ifndef STATICMODEL_H
#define STATICMODEL_H

#include <list>
#include "typedefs.h"
#include "Vertex.h"
#include "libs/json/json.h"
#include "elements/StaticModelPart.h"
#include "elements/Model.h"

class StaticModel: public Model{
  typedef std::list<StaticModelPart> PartList;
  public:
    StaticModel(const json::mValue& value);
    double getRadius() const {return m_radius;};
  protected:
    PartList m_parts;
    double m_radius;

  friend class CModelMgr;
};

#endif // STATICMODEL_H
