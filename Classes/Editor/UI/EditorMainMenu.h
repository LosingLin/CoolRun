//
//  EditorMainMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__EditorMainMenu__
#define __CoolRun__EditorMainMenu__

#include "EditorMenu.h"

class EditorMainMenu : public EditorMenu
{
public:
    EditorMainMenu();
    ~EditorMainMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorMainMenu);
    
    virtual void spaceCallback() override;
    void menuCallback(int index);
private:
    
};

#endif /* defined(__CoolRun__EditorMainMenu__) */
