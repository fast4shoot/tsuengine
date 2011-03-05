#include "CMapMgr.h"

#include <fstream>
#include "json/json.h"
#include "CBaseEngine.h"

CMapMgr::CMapMgr(){

}

void CMapMgr::loadMap(const String& name){
  try{
    /*std::ifstream file;
    file.open(("maps/"+name+".json").c_str());
    json::mValue value;
    json::read(file, value);
    const json::mArray& ents = value.get_obj()["entities"].get_array();

    for(json::mArray::const_iterator it = ents.begin(); it != ents.end(); ++it){

    }

    m_mapName = name;
    m_isLoaded = true;*/
  }catch(std::exception e){
    engine->warning("Couldn't load map "+name+": "+String(e.what()));
  }
}
