#ifndef CDOWNLOADMAPS_H
#define CDOWNLOADMAPS_H

#include <vector>
#include "utils/network.h"
#include "datatypes.h"
#include "CCenteredWindow.h"
#include "CListBox.h"
#include "CText.h"
#include "utils/Thinker.h"
#include "utils/AsyncDownloader.h"



class CStatusOverlay: public CGuiPanel{
  public:
    CStatusOverlay(const vec2d& pos, const vec2d& size);
    void draw();
    void closeOverlay(int);
  protected:
    CGuiPanel* m_btn;

  friend class CDownloadMaps;
};

class CDownloadMaps: public CCenteredWindow, Thinker{
  public:
    CDownloadMaps();
    void doDownload(int);
    void think();
  protected:
    void setDescription(int);
    void downloadNextFile();
    void finishDownload(const String& text);

    CGuiPanel* m_downloadButton;
    CListBox* m_list;
    CText* m_descText;
    CText* m_statusMessage;
    CGuiPanel* m_overlayButton;
    CStatusOverlay* m_overlay;
    std::vector<String> m_descList;

    int m_lastFile;
    std::vector<String> m_fileList;

    enum{
      DDS_NONE,
      DDS_FILELIST,
      DDS_FILES
    } m_dataDownloadStatus;

    AsyncDownloader m_downloader;


};

#endif // CDOWNLOADMAPS_H
