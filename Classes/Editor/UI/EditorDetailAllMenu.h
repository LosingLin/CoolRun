//
//  EditorDetailAllMenu.h
//  CoolRun
//
//  Created by ManYou on 15/5/11.
//
//

#ifndef __CoolRun__EditorDetailAllMenu__
#define __CoolRun__EditorDetailAllMenu__

#include "EditorDetailMenu.h"

class EditorTextInput;
class EditorPhysicNodeContainer;
class EditorSelector;
class EditorText;
class EditorDetailAllMenu : public EditorDetailMenu
{
public:
    EditorDetailAllMenu();
    ~EditorDetailAllMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorDetailAllMenu);
    
    virtual void setPhysicNodeContaner(EditorPhysicNodeContainer* pNodeCor);
    
    virtual void spaceCallback() override;
    virtual void updateMenu();
    
    virtual void textInputDone(const string& text, EditorTextInput* input);
    virtual void selectedActive(EditorSelector* selector);
    virtual void selectedDone(const string& key, EditorSelector* selector);
private:
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
    //SpiderPoison
    EditorSelector* m_spiderPosionDir;
    //Bullet
    EditorSelector* m_isAnimalHurt;
    EditorSelector* m_isRunnerHurt;
    EditorSelector* m_isAtkable;
    //Item
    EditorTextInput* m_flyV;
};
#endif /* defined(__CoolRun__EditorDetailAllMenu__) */
