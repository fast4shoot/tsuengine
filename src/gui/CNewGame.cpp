#include "CNewGame.h"
#include "CListBox.h"
#include "CButton.h"
#include <boost/filesystem.hpp>
#include "listeners/CListenerMemberFn.h"
#include "CBaseEngine.h"

namespace fs = boost::filesystem;


CNewGame::CNewGame():
  CCenteredWindow(vec2d(300,350), "Nová hra", 65.)
{

  addChild(new CLabel(vec2d(20,40),vec2d(10,18), "Vyberte mapu"));
  addChild(new CButton(vec2d(20, getH()-110.), vec2d(getW()-40., 25), "Stahovat mapy"));
  addChild(m_loadGameButton = new CButton(vec2d(getW()-120., getH()-45.), vec2d(100, 25), "Hrát"));
  m_loadGameButton->setVisible(false);
  m_loadGameButton->addListener(makeCListenerMemberFn(1, this, &CNewGame::newGameLoad));

  m_mapList = new CListBox(vec2d(20,65), vec2d(getW()-40.,getH()-195.  ));
  addChild(m_mapList);
  m_mapList->addListener(makeCListenerMemberFn(0, this, &CNewGame::newGameLoad));
  fs::directory_iterator end;
  for(fs::directory_iterator it("maps"); it!=end; ++it){
    if(fs::is_regular_file(it->path())){
      m_mapList->addItem(it->path().stem().string());
    }
  }
}

void CNewGame::newGameLoad(int id){
  if(id == 0){
    m_loadGameButton->setVisible(true);
  }
  if(id == 1){
    engine->map->load(m_mapList->getSelectedString());
  }
}
