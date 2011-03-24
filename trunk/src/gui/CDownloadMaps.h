#ifndef CDOWNLOADMAPS_H
#define CDOWNLOADMAPS_H

#include <vector>
#include "CCenteredWindow.h"
#include "CListBox.h"
#include "CText.h"

class CDownloadMaps: public CCenteredWindow{
  public:
    CDownloadMaps();

  protected:
    void setDescription(int);
    CListBox* m_list;
    CText* m_descText;
    std::vector<String> m_descList;

};

#endif // CDOWNLOADMAPS_H
