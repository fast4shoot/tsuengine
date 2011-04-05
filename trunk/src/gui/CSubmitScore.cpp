#include "CSubmitScore.h"

#include "CText.h"
#include "CBox.h"
#include "CTextField.h"
#include "CButton.h"
#include "CBaseEngine.h"
#include "md5/md5.hh"

CSubmitScore::CSubmitScore():
  CCenteredWindow( vec2d(300, 200), "", 65., false )
{
  CGuiPanel* c = getContent();
  CGuiPanel* tmp;

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
      String query = "http://tsuengine.php5.cz/generateKey.php?map="+urlencode(engine->map->getMapName())+"&player="+urlencode(m_name);
      net::http::client::request request_( query );
      engine->log(query);
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
      String query = (format( "http://tsuengine.php5.cz/submitTime.php?hash=%s&key=%s&time=%f") % hash % key % engine->map->getMapTime() ).str();
      engine->log(query);
      net::http::client::request request_(query);
      request_ << net::header("Connection", "close");
      net::http::client client_;
      net::http::client::response response_ = client_.get(request_);
      body = net::http::body(response_);
      engine->log(body);
    }
    {
      double h = engine->getScreenHeight();
      double w = engine->getScreenWidth();
      double part = std::min(h/9., w/13.);
      json::mValue data;
      json::read(body, data);

      setVisible(false);

      CGuiPanel* pnl = new CGuiPanel( vec2d( (w-part*13.)/2., (h-part*9.)/2. ),
                                      vec2d( part*13., part*9. ) );
      m_finalPanel = pnl;

      CWindow* leftWnd = new CWindow( vec2d( part, part ),
                                      vec2d( part*5., part*7. ),
                                      "",
                                      0.,
                                      false );

      pnl->addChild(leftWnd);
      leftWnd->addChild( new CLabel( vec2d( 0., 0. ), vec2d( part*5, part/2. ), "Nejlepší časy", true, CLabel::ALIGN_CENTER ) );
      CBox* topBox = new CBox( vec2d(part/4., 3*part/4.), vec2d(part*4.5, part*6) );

      const json::mArray& tops = data.get_obj().find("top")->second.get_array();
      int i = 0;
      double topBoxW = topBox->getW()-4.;
      double topBoxH = topBox->getH()-4.;

      BOOST_FOREACH(const json::mValue& row, tops){
        topBox->addChild( new CLabel( vec2d(2., 2.+topBoxH/40.+i*topBoxH/20.), vec2d( topBoxH/15., topBoxH/40. ), (format("%d.")%(i+1)).str() ) );
        topBox->addChild( new CLabel( vec2d(2.+topBoxW/13., 2.+i*topBoxH/20.), vec2d( topBoxW - topBoxW/13., topBoxH/20. ),
                          row.get_obj().find("name")->second.get_str() ));
        topBox->addChild( new CLabel( vec2d(2.+topBoxW/13., 2.+i*topBoxH/20.), vec2d( topBoxW - topBoxW/13., topBoxH/20. ),
                          formatTime(row.get_obj().find("time")->second.get_real()), false, CLabel::ALIGN_RIGHT ));
        i++;
      }

      leftWnd->addChild(topBox);

      CWindow* rghtWnd = new CWindow( vec2d( part*7., part ),
                                      vec2d( part*5., part*7. ),
                                      "",
                                      part,
                                      false );

      const json::mObject& curr = data.get_obj().find("current")->second.get_obj();

      rghtWnd->addChild( new CLabel( vec2d( 0., 0. ), vec2d( part*5, part/2. ), "Vaše umístění", true, CLabel::ALIGN_CENTER ) );
      rghtWnd->addChild( new CLabel( vec2d( 0., 3*part/4. ), vec2d( part*5, part/2. ), (format("%d. místo") % curr.find("position")->second.get_int() ).str(), false, CLabel::ALIGN_CENTER  ) );
      rghtWnd->addChild( new CLabel( vec2d( 0., 7*part/4. ), vec2d( part*5, part/2. ), "s časem", true, CLabel::ALIGN_CENTER  ) );
      rghtWnd->addChild( new CLabel( vec2d( 0., 11*part/4. ), vec2d( part*5, part/2. ), formatTime(curr.find("time")->second.get_real() ), false, CLabel::ALIGN_CENTER  ) );

      CGuiPanel* tmp;

      double btnW = (rghtWnd->getW() - 3*part/2) / 2;

      tmp = new CButton( vec2d( part/2, rghtWnd->getH() - 3*part/4 ), vec2d( btnW, part/2.), "Opakovat" );
      tmp->addListener(makeCListenerMemberFn(3, this, &CSubmitScore::submitAction));
      rghtWnd->addChild(tmp);

      tmp = new CButton( vec2d( rghtWnd->getW() - 18*(part)/4., rghtWnd->getH() - 3*part/4 ), vec2d( btnW, part/2.), "Hlavní menu" );
      tmp->addListener(makeCListenerMemberFn(2, this, &CSubmitScore::submitAction));
      rghtWnd->addChild(tmp);

      pnl->addChild(rghtWnd);

      engine->gui->addElement(pnl);

    }
    /*
    TODO: ASYNC!
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

  }else if(id == 2){
    remove();
    m_finalPanel->remove();
    engine->gui->showMainMenu(true);
  }else if(id == 3){
    remove();
    m_finalPanel->remove();
    engine->map->reload();
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
