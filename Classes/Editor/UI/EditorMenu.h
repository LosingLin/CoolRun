//
//  EditorMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#ifndef __CoolRun__EditorMenu__
#define __CoolRun__EditorMenu__

#include "EditorNode.h"

class EditorMenu : public EditorNode
{
public:
    enum class MenuType
    {
        NONE,
        MAIN,
        ITEM,
        OBJECT,
        COLLECION,
        ITEMOBJECT,
        DETAIL,
        OPENFILE,
        PAGE,
    };
public:
    EditorMenu();
    ~EditorMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorMenu);
    
    virtual void spaceCallback() {};
    
    void setMenuType(MenuType type) { m_type = type; };
    MenuType getMenuType() { return m_type; };
private:
    MenuType m_type;
};

#endif /* defined(__CoolRun__EditorMenu__) */
