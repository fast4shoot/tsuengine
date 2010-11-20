#include "CMaterialMgr.h"

#include "libs/IL/il.h"
#include "libs/IL/ilu.h"
#include "libs/IL/ilut.h"

CMaterialMgr::CMaterialMgr(){
  ilInit();
  iluInit();
  ilutRenderer(ILUT_OPENGL);
}

CMaterialMgr::~CMaterialMgr()
{
    //dtor
}
