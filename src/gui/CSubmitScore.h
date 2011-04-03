#ifndef CSUBMITSCORE_H
#define CSUBMITSCORE_H

#include "CCEnteredWindow.h"
#include "utils/network.h"
#include "utils/Thinker.h"
#include "CText.h"
#include "CTextField.h"

class CSubmitScore: public CCenteredWindow{
  public:
    CSubmitScore();
    //void think();
  protected:
    void submitAction(int id);
    CGuiPanel* m_button;
    CTextField* m_textField;
    CText* m_statusText;
    String m_name;


    enum{
      STATUS_NONE,
      STATUS_KEY,
      STATUS_SUBMIT
    } m_status;
};

#endif // CSUBMITSCORE_H
