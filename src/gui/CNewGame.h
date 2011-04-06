#ifndef CNEWGAME_H
#define CNEWGAME_H

#include "CCenteredWindow.h"
#include "CButton.h"
#include "CListBox.h"

class CNewGame: public CCenteredWindow{
  public:
    CNewGame();
    void reloadList();
  protected:
    void newGameLoad(int id);
    CButton* m_loadGameButton;
    CListBox* m_mapList;

};

#endif // CNEWGAME_H
