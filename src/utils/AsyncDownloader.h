#ifndef ASYNCDOWNLOADER_H
#define ASYNCDOWNLOADER_H

#include <sstream>
#include <boost/thread.hpp>
using boost::thread;
using boost::packaged_task;
using boost::unique_future;
#include "typedefs.h"

class AsyncDownloader{
  public:
    void download(String url);
    bool isReady();
    std::stringstream& get();
  protected:
    class DownloadTask{
      public:
        DownloadTask(const String& url);
        DownloadTask(const DownloadTask& other);
        std::stringstream& operator()();
      private:
        std::stringstream m_data;
        String m_url;
    };
    thread m_thread;
    packaged_task<std::stringstream&> m_task;
    unique_future<std::stringstream&> m_future;
};

#endif // ASYNCDOWNLOADER_H
