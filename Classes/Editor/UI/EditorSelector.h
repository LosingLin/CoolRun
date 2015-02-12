//
//  EditorSelector.h
//  CoolRun
//
//  Created by ManYou on 15/2/2.
//
//

#ifndef __CoolRun__EditorSelector__
#define __CoolRun__EditorSelector__

#include "EditorNode.h"

using namespace std;

class EditorText;
class EditorSelector : public EditorNode
{
public:
    EditorSelector();
    ~EditorSelector();
    
    virtual bool init() override;
    bool init(__Array* arr, const string& title, const Size& csize);
    
    static EditorSelector* create(__Array* arr, const string& title, const Size& csize);
    
    void touchSelector();
    void selected(const string& key);
    void setSelected(const string& key);
public:
    std::function<void(EditorSelector* select)> active;
    std::function<void(const string& key)> selectedKey;
private:
    __Array* m_arr;
    EditorText* m_selector;
    Node* m_items;
};

class EditorSelectorValue : public Ref
{
public:
    EditorSelectorValue();
    ~EditorSelectorValue();
    
    bool init();
    
    int getValue() { return m_value; }
    void setValue(int v) { m_value = v; }
    
    static EditorSelectorValue* create(int v);
private:
    int m_value;
};

#endif /* defined(__CoolRun__EditorSelector__) */
