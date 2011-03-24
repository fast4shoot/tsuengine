#include "CNewGame.h"
#include "CListBox.h"
#include "CButton.h"
#include <boost/filesystem.hpp>


namespace fs = boost::filesystem;


CNewGame::CNewGame():
  CCenteredWindow(vec2d(300,350), "Nová hra", 65.)
{

  addChild(new CLabel(vec2d(20,40),vec2d(10,18), "Vyberte mapu"));
  addChild(new CButton(vec2d(20, getH()-110.), vec2d(getW()-40., 25), "Stahovat mapy"));
  addChild(new CButton(vec2d(getW()-120., getH()-45.), vec2d(100, 25), "Hrát"));
  CListBox* list = new CListBox(vec2d(20,65), vec2d(getW()-40.,getH()-195.  ));
  addChild(list);
  fs::directory_iterator end;
  for(fs::directory_iterator it("maps"); it!=end; ++it){
    if(fs::is_regular_file(it->path())){
      list->addItem(it->path().stem().string());
    }
  }
}
