//
//  EditorObjectMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#ifndef __CoolRun__EditorObjectMenu__
#define __CoolRun__EditorObjectMenu__

#include "EditorMenu.h"
#include "PhysicNodeFactory.h"

class EditorObjectMenu : public EditorMenu
{
public:
    EditorObjectMenu();
    ~EditorObjectMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorObjectMenu);
    
    virtual void spaceCallback() override {};
    
    void menuCallback(PhysicNodeType type);
private:
    
};

#endif /* defined(__CoolRun__EditorObjectMenu__) */
