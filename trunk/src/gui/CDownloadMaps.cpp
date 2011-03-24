#include "CDownloadMaps.h"

#include <boost/network/include/http/client.hpp>
#include <boost/foreach.hpp>
#include "CBaseEngine.h"
#include "datatypes.h"

namespace net = boost::network;

CDownloadMaps::CDownloadMaps():
  CCenteredWindow(vec2d(500,350), "Stahování map")
{
  m_list = new CListBox(vec2d(20,50), vec2d(260, 280));

  m_list->addListener(makeCListenerMemberFn(0,this,&CDownloadMaps::setDescription));
  addChild(m_list);

  m_descText = new CText(vec2d(300., 50), vec2d(160, 280), 14);
  m_descText->setText("Vyberte mapu ke stažení");
  addChild(m_descText);

  net::http::client::request request("http://tsuengine.php5.cz/getMapList.php");
  //net::http::client::request request("http://www.boost.org/");
  //net::http::client::request request("http://fast4shoot.xf.cz");
  engine->log("Request built");
  request << net::header("Connection", "close");
  //client client;
  //net::http::client::response = ;
  net::http::client::response rsp = net::http::client().get(request);
  engine->log("Response got");
  std::string s = body(rsp);
  engine->log("Body extracted");
  //engine->log(s);

  json::mValue mapList;
  json::read(s, mapList);
  BOOST_FOREACH(const json::mValue& map, mapList.get_array()){
    engine->log("adding item");
    m_list->addItem(map.get_obj().find("name")->second.get_str());
    m_descList.push_back(map.get_obj().find("desc")->second.get_str());
  }

  //boost:network::body_directive
}

void CDownloadMaps::setDescription(int){
  m_descText->setText(m_descList[m_list->getSelectedItem()]);
}
