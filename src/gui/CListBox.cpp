#include "CListBox.h"

#include "listeners/CListenerMemberFn.h"
#include "CAutoSizePanel.h"
#include "CScrollable.h"

CListBoxItem::CListBoxItem(const vec2d& pos, const vec2d& size, const String& text):
  CAbstractToggle(pos, size),
  m_label(new CLabel(vec2d(getH()/5., getH()/5.), size-vec2d(getH()/2.5, getH()/2.5), text))
{
  addChild(m_label);
  setBgColor(rgba(.1, .1, .1, .2));
  setFgColor(rgba(0., .8, .843, .4));
}

void CListBoxItem::draw(){
  if(getSelected()){
    setDrawColor(fgColor);
  }else{
    setDrawColor(bgColor);
  }
  drawFrame(0, 0, getW(), getH());
  drawQuad(1, 1, getW()-2, getH()-2);
  setDrawColor(glossColor);
  drawQuad(1, 1, getW()-2, getH()/2.-1.);
}

CListBox::CListBox(const vec2d& pos, const vec2d& size, double itemHeight):
  CGuiPanel(pos, size),
  m_itemHeight(itemHeight),
  m_selectedItem(-1),
  m_panel(new CAutoSizePanel())
{
  CScrollable* scroll = new CScrollable(vec2d(2., 2.), size-vec2d(4., 4.));
  addChild(scroll);
  scroll->setScrolledItem(m_panel);
  setBgColor(rgba(.1, .1, .1, .2));
}

void CListBox::addItem(const String& itemText){
  CListBoxItem* added = new CListBoxItem(vec2d(0,m_items.size()*m_itemHeight), vec2d(getW()-25., m_itemHeight), itemText);
  added->addListener(makeCListenerMemberFn((int)m_items.size(), this, &CListBox::setSelectedItem));
  m_items.push_back(added);
  m_panel->addChild(added);
}

void CListBox::setSelectedItem(int id){
  if(m_items[id]->getSelected()){
    m_selectedItem = id;
    for(ItemList::iterator it = m_items.begin(); it != m_items.end(); ++it){
      (*it)->setSelected(false);
    }
    m_items[id]->setSelected(true);
    fireListeners();
  }else{
    m_items[id]->setSelected(true);
  }
}

void CListBox::draw(){
  setDrawColor(fgColor);
  drawFrame(0, 0, getW(), getH());
  setDrawColor(bgColor);
  drawQuad(1, 1, getW()-2, getH()-2);
}
