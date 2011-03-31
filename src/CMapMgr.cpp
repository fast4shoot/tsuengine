#include "CMapMgr.h"

#include <fstream>
#include "json/json.h"
#include "CBaseEngine.h"
#include "CGuiPanel.h"

CMapMgr::CMapMgr():
  m_isLoaded(false),
  m_shouldLoad(false)
{}

void CMapMgr::load(const String& name){
  m_newMapName = name;
  m_shouldLoad = true;
}

void CMapMgr::unload(){
  if(!m_isLoaded) return;
  engine->camera->removeAll();
  engine->ents->removeAll();
  engine->physics->removeAll();
  engine->models->removeAll();
  engine->materials->removeAll();


  engine->log("Map "+m_mapName+" unloaded");
  m_isLoaded = false;
  m_mapName = "";
}

void CMapMgr::update(){
  if(!m_background && engine->input->keyPressed(DIK_ESCAPE)){
    engine->gui->showMainMenu(!m_menuOpen);
    engine->setTimeScale(m_menuOpen * 1.f);
    m_menuOpen = !m_menuOpen;
  }

  try{
    if(!m_shouldLoad) return;
    if(m_isLoaded) unload();
    engine->log("Loading map "+m_newMapName);
    std::ifstream file;
    file.open(("maps/"+m_newMapName+".json").c_str());
    json::mValue value;
    json::read(file, value);

    std::vector<CBaseEntity*> tempEntList;

    const json::mArray& ents = value.get_obj()["entities"].get_array();
    for(json::mArray::const_iterator it = ents.begin(); it != ents.end(); ++it){
      tempEntList.push_back(engine->ents->create(*it));
    }

    engine->log("Creating relations...");
    if(value.get_obj().find("relations") != value.get_obj().end()){
      const json::mArray& rels = value.get_obj().find("relations")->second.get_array();
      for(json::mArray::const_iterator it = rels.begin(); it != rels.end(); ++it){
        try{
          CBaseEntity* e1 = tempEntList[it->get_obj().find("caller")->second.get_int()];
          CBaseEntity* e2 = tempEntList[it->get_obj().find("callee")->second.get_int()];
          if(e1 != NULL && e1 != NULL){
            e1->addRelation(it->get_obj().find("output")->second.get_str(), e2, it->get_obj().find("input")->second.get_str());
          }
        }catch(std::exception& e){
          engine->warning("Can't create relation: "+String(e.what()));
        }
      }
    }

    engine->gui->getHud()->deleteChildren();
    engine->input->setEnabled(true);

    m_background = true;
    engine->log("Spawning entities");
    engine->ents->doSpawn();

    m_menuOpen = m_background;
    engine->gui->showMainMenu(m_menuOpen);
    engine->setTimeScale(1.f);

    engine->models->uploadData();
    engine->resetGameTime();
    m_mapName = m_newMapName;
    m_newMapName = "";
    m_isLoaded = true;
    m_shouldLoad = false;
    engine->log("Map loaded");
  }catch(std::exception& e){
    engine->warning("Couldn't load map "+m_newMapName+": "+String(e.what()));
  }
}

void CMapMgr::setMapAsBackground(bool val){
  m_background = val;
}
