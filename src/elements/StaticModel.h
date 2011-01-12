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
  protected:
    PartList m_parts;

  friend class CModelMgr;
};

#endif // STATICMODEL_H
