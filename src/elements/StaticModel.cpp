#include "StaticModel.h"

#include <algorithm>
#include "CBaseEngine.h"


StaticModel::StaticModel(const json::mValue& value){
  json::mArray parts = value.get_obj().find("parts")->second.get_array();
  for(json::mArray::iterator it=parts.begin(); it!=parts.end(); ++it){
    m_parts.push_back(StaticModelPart(*it));
  }

  double radius;
  for(PartList::iterator it=m_parts.begin(); it!=m_parts.end(); ++it){
    radius = std::max(radius,(*it).getRadius());
  }
  m_radius = radius;
}
