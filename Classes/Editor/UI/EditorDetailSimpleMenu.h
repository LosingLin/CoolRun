//
//  EditorDetailSimpleMenu.h
//  CoolRun
//
//  Created by ManYou on 15/5/11.
//
//

#ifndef __CoolRun__EditorDetailSimpleMenu__
#define __CoolRun__EditorDetailSimpleMenu__

#include "EditorDetailMenu.h"

class EditorTextInput;
class EditorPhysicNodeContainer;
class EditorSelector;
class EditorText;
class EditorDetailSimpleMenu : public EditorDetailMenu
{
public:
    EditorDetailSimpleMenu();
    ~EditorDetailSimpleMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorDetailSimpleMenu);
    
    virtual void setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor);
    
    virtual void spaceCallback() override;
    virtual void updateMenu();
    
    virtual void textInputDone(const string& text, EditorTextInput* input);
    virtual void selectedActive(EditorSelector* selector);
    virtual void selectedDone(const string& key, EditorSelector* selector);
private:
    //V
    EditorTextInput* m_x_v;
    EditorTextInput* m_x_a;
    
    //contentsize
    EditorTextInput* m_csizeWidth;
    
    //Spider
    EditorSelector* m_spideState;
    //SpiderPoison
    EditorSelector* m_spiderPosionDir;

    //Item
    //EditorTextInput* m_flyV;
};

#endif /* defined(__CoolRun__EditorDetailSimpleMenu__) */
