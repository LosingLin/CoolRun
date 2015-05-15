//
//  EditorItemObjectMenu.h
//  CoolRun
//
//  Created by ManYou on 15/5/12.
//
//

#ifndef __CoolRun__EditorItemObjectMenu__
#define __CoolRun__EditorItemObjectMenu__

#include "EditorMenu.h"
#include "PhysicNodeFactory.h"

class EditorItemObjectMenu : public EditorMenu
{
public:
    EditorItemObjectMenu();
    ~EditorItemObjectMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorItemObjectMenu);
    
    virtual void spaceCallback() override {};
    
    void menuCallback(PhysicNodeType type);
private:
    
};

#endif /* defined(__CoolRun__EditorItemObjectMenu__) */
