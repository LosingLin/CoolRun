//
//  EditorDetailMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/31.
//
//

#ifndef __CoolRun__EditorDetailMenu__
#define __CoolRun__EditorDetailMenu__

#include "EditorMenu.h"

#define NORMALDIS(x) (x) -= 80
#define BIGDIS(x) (x) -= 120

class EditorTextInput;
class EditorPhysicNodeContainer;
class EditorSelector;
class EditorText;
class EditorDetailMenu : public EditorMenu
{
public:
    EditorDetailMenu();
    ~EditorDetailMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorDetailMenu);
    
    virtual void setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor);
    EditorPhysicNodeContainer* getPhysicNodeContainer() { return m_pNodeCor; }
    
    virtual void spaceCallback() override;
    virtual void updateMenu();
    
    void deleteEditorNode();
    virtual void textInputDone(const string& text, EditorTextInput* input);
    virtual void selectedActive(EditorSelector* selector);
    virtual void selectedDone(const string& key, EditorSelector* selector);
protected:
    EditorPhysicNodeContainer* m_pNodeCor;
    
    EditorText* m_delete;
    
    //position
    EditorTextInput* m_posX;
    EditorTextInput* m_posY;
    
    float m_y;
};

#endif /* defined(__CoolRun__EditorDetailMenu__) */
