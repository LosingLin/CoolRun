//
//  EditorCollectionMenu.h
//  CoolRun
//
//  Created by ManYou on 15/2/7.
//
//

#ifndef __CoolRun__EditorCollectionMenu__
#define __CoolRun__EditorCollectionMenu__

#include "EditorMenu.h"

class EditorCollectionMenu : public EditorMenu
{
public:
    EditorCollectionMenu();
    ~EditorCollectionMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorCollectionMenu);
    
    virtual void spaceCallback() override {};
    
    void menuCallback(int cmIndex);

};

#endif /* defined(__CoolRun__EditorCollectionMenu__) */
