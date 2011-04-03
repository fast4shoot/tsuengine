#ifndef CENDFAILURE_H
#define CENDFAILURE_H

#include "CCenteredWindow.h"

class CEndFailure: public CCenteredWindow{
  public:
    CEndFailure();
  protected:
    void endFailureAction(int id);
};

#endif // CENDFAILURE_H
