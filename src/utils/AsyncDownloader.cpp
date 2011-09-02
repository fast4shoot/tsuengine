#include "AsyncDownloader.h"

#include <stdexcept>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

void AsyncDownloader::download(String url){
  if(m_future.get_state() == boost::future_state::waiting) throw std::runtime_error("AsyncDownloader cannot download multiple files simultaneously.");
  m_task = packaged_task<std::stringstream&>(DownloadTask(url));
  m_future = m_task.get_future();
  m_thread = thread(boost::move(m_task));
}

bool AsyncDownloader::isReady(){
  return (m_future.get_state() == boost::future_state::ready);
}

std::stringstream& AsyncDownloader::get(){
  return m_future.get();
}

AsyncDownloader::DownloadTask::DownloadTask(const String& url):
  m_url(url)
{}

AsyncDownloader::DownloadTask::DownloadTask(const DownloadTask& other):
  m_url(other.m_url)
{}

std::stringstream& AsyncDownloader::DownloadTask::operator()(){
  curlpp::options::Url url(m_url);
  curlpp::Easy request;
  request.setOpt(url);
  m_data << request;
  return m_data;
}
