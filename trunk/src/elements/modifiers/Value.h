#include "utils/any.h"
#include <vector>
#include <map>
#include "typedefs.h"

namespace modifiers{

  typedef any Value;
  typedef std::vector< Value > VectorValue;
  typedef boost::shared_ptr< Value > ValuePtr;
  typedef std::map<String,Value> PropertyList;

}
