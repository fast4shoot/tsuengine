#include "CSubmitScore.h"

#include "CText.h"
#include "CTextField.h"
#include "CButton.h"
#include "CBaseEngine.h"
#include "md5/md5.hh"

CSubmitScore::CSubmitScore():
  CCenteredWindow( vec2d(300, 200), "", 65., false )
{
  CGuiPanel* c = getContent();
  CGuiPanel* tmp;
  m_status = STATUS_NONE;

  c->addChild( m_statusText = new CText( vec2d(20., 20.), c->getSize()-vec2d(40., 155), 21., CLabel::ALIGN_CENTER ) );
  m_statusText->setText("Zadejte jméno, pod kterým bude čas na serveru uložen");
  c->addChild( m_textField = new CTextField( vec2d(20., c->getH() - 50.), vec2d(c->getW() - 105., 30.) ) );
  m_textField->addListener( makeCListenerMemberFn(0, this, &CSubmitScore::submitAction) );
  c->addChild( tmp = new CButton( c->getSize() - vec2d( 120., 45. ), vec2d( 100., 25.), "Odeslat" ) );
  tmp->setOpacity(0.);
  tmp->setVisible(false);
  tmp->addListener( makeCListenerMemberFn( 1, this, &CSubmitScore::submitAction ) );
  m_button = tmp;

}

void CSubmitScore::submitAction(int id){
  if(id == 0){
    m_button->setVisible(!m_textField->getText().empty());
  }else if(id == 1){
    m_button->remove();
    m_name = m_textField->getText();
    m_textField->remove();
    m_statusText->setText("Komunikuji se serverem...");
    //m_status = STATUS_KEY;

    String body;

    {
      net::http::client::request request_("http://tsuengine.php5.cz/generateKey.php?map="+engine->map->getMapName()+"&player="+m_name);
      request_ << net::header("Connection", "close");
      net::http::client client_;
      net::http::client::response response_ = client_.get(request_);
      body = net::http::body(response_);
      engine->log(body);
    }

    String key, hash;
    {
      json::mValue data;
      json::read(body, data);
      key = data.get_obj().find("key")->second.get_str();
      hash = (format("%1%%2%%3%") % data.get_obj().find("player")->second.get_int() % data.get_obj().find("map")->second.get_int() % key).str();

      MD5 hasher = MD5(hash);
      hash = hasher.hex_digest();
    }

    {
      net::http::client::request request_((format(
        "http://tsuengine.php5.cz/submitTime.php?hash=%s&key=%s&time=%f") % hash % key % engine->map->getMapTime()
      ).str() );
      request_ << net::header("Connection", "close");
      net::http::client client_;
      net::http::client::response response_ = client_.get(request_);
      body = net::http::body(response_);
      engine->log(body);
    }
    /*
    String url = "http://tsuengine.php5.cz/generateKey.php?map="+engine->map->getMapName()+"&player="+m_name;

    //String url = "http://tsuengine.php5.cz/test.json";
    engine->log(url);
    AsyncClient::request request(url);
    engine->log("request");
    request << net::header("Connection", "close");
    engine->log(net::http::query(request));
    engine->log("get");
    engine->net->response = engine->net->client.get(request);
    engine->log("win");*/
  }
}

/*
void CSubmitScore::think(){
  if(m_status != STATUS_NONE){
    if(net::http::ready(engine->net->response)){
      engine->log("rofl");
      if(m_status == STATUS_KEY){
        if( net::http::status(engine->net->response) == 200 ){
          String s = net::http::body(engine->net->response);
          engine->log(format("(%2%)>>>>(%1%)<<<<") % s % s.length());
          engine->log("something after");
          m_status = STATUS_NONE;
          json::mValue data;
          json::read(s, data);
          String key = data.get_obj().find("key")->second.get_str();
          String hash = data.get_obj().find("player")->second.get_str()+
                        data.get_obj().find("map")->second.get_str()+key;

          MD5 hasher = MD5(hash);
          hash = hasher.hex_digest();



          AsyncClient::request request( (format(
            "http://tsuengine.php5.cz/submitTime.php?hash=%s&key=%s&time=%f") % hash % key % engine->map->getMapTime()
          ).str() );
          request << net::header("Connection", "close");
          engine->net->response = engine->net->client.get(request);

        }else{
          throw std::runtime_error("Došlo k chybě při získávání klíče.");
        }
      }else if(m_status == STATUS_SUBMIT){
        m_status = STATUS_NONE;
      }
    }
  }
}
*/
