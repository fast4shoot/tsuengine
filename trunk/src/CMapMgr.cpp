#include "CMapMgr.h"

#include <fstream>
#include "json/json.h"
#include "CBaseEngine.h"

CMapMgr::CMapMgr(){

}

void CMapMgr::load(const String& name){
  try{
    engine->log("Loading map "+name);
    std::ifstream file;
    file.open(("maps/"+name+".json").c_str());
    json::mValue value;
    json::read(file, value);

    std::vector<CBaseEntity*> tempEntList;

    const json::mArray& ents = value.get_obj()["entities"].get_array();
    for(json::mArray::const_iterator it = ents.begin(); it != ents.end(); ++it){
      tempEntList.push_back(engine->ents->create(*it));
    }

    /*
    const json::mArray& rels = value.get_obj()["relations"].get_array();
    for(json::mArray::const_iterator it = ents.begin(); it != ents.end(); ++it){

      CBaseEntity* e1 = tempEntList[it->get_obj()["caller"];
    }*/

    engine->log("Spawning entities");
    engine->ents->doSpawn();

    m_mapName = name;
    m_isLoaded = true;
    engine->log("Map loaded");
  }catch(std::exception e){
    engine->warning("Couldn't load map "+name+": "+String(e.what()));
  }
}

void CMapMgr::unload(){
  if(!m_isLoaded) return;
  engine->ents->removeAll();
  engine->physics->removeAll();
  engine->models->removeAll();
  engine->materials->removeAll();
  engine->log("Map "+m_mapName+" unloaded");
  m_isLoaded = false;
  m_mapName = "";
}
