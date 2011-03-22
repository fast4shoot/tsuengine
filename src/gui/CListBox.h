#ifndef CLISTBOX_H
#define CLISTBOX_H

#include <vector>
#include "CGuiPanel.h"
#include "CAbstractToggle.h"
#include "CLabel.h"

class CListBoxItem: public CAbstractToggle{
  public:
    CListBoxItem(const vec2d& pos, const vec2d& size, const String& text);
    void draw();
  private:
    CLabel* m_label;
};

class CListBox: public CGuiPanel{
  public:
    CListBox(const vec2d& pos, const vec2d& size, double itemHeight = 20.);
    void addItem(const String& text);
    int getSelectedItem();
    void setSelectedItem(int id);
    void draw();
  protected:
    typedef std::vector<CListBoxItem*> ItemList;
    ItemList m_items;
    double m_itemHeight;
    int m_selectedItem;
    CGuiPanel* m_panel;

};

inline int CListBox::getSelectedItem(){
  return m_selectedItem;
}

#endif // CLISTBOX_H
