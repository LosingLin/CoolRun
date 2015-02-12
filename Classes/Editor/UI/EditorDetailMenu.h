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
    
    void setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor);
    EditorPhysicNodeContainer* getPhysicNodeContainer() { return m_pNodeCor; }
    
    virtual void spaceCallback() override;
    virtual void updateMenu();
    
    void deleteEditorNode();
    void textInputDone(const string& text, EditorTextInput* input);
    void selectedActive(EditorSelector* selector);
    void selectedDone(const string& key, EditorSelector* selector);
private:
    EditorPhysicNodeContainer* m_pNodeCor;
    
    EditorText* m_delete;
    
    //position
    EditorTextInput* m_posX;
    EditorTextInput* m_posY;
    //contentsize
    EditorTextInput* m_csizeWidth;
    EditorTextInput* m_csizeHeight;
    //V
    EditorTextInput* m_x_v;
    EditorTextInput* m_x_a;
    EditorTextInput* m_y_v;
    EditorTextInput* m_y_a;
    //align
    EditorTextInput* m_alignX;
    EditorTextInput* m_alignY;
//    //ColideRect
//    EditorTextInput* m_cR_left;
//    EditorTextInput* m_cR_down;
//    EditorTextInput* m_cR_right;
//    EditorTextInput* m_cR_up;
    EditorSelector* m_isScreenPos;
    EditorSelector* m_isGEffect;
    EditorSelector* m_isCEffect;
    EditorSelector* m_isVIgnore;
    EditorSelector* m_cType;
    
    //Spider
    EditorSelector* m_spideState;
    //Bullet
    EditorSelector* m_isAnimalHurt;
    EditorSelector* m_isRunnerHurt;
    //Item
    EditorTextInput* m_flyV;
    
    float m_y;
};

#endif /* defined(__CoolRun__EditorDetailMenu__) */
