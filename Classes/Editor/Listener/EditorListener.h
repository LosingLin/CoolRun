//
//  EditorListener.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__EditorListener__
#define __CoolRun__EditorListener__

#include "cocos2d.h"

class EditorNode;
class EditorMenu;
class Collection;
class EditorPhysicNodeContainer;
class EditorListener
{
public:
    enum class MenuState
    {
        NONE,
        FIRST,
        SECOND,
        THIRD,
    };
    virtual EditorMenu* getMenu(MenuState state) { return nullptr; };
    virtual void showMenu(MenuState state, EditorMenu* menu) {};
    virtual void hideMenu(MenuState state) {};
    virtual void addObject(EditorPhysicNodeContainer* obj) {};
    virtual void addEvent(EditorPhysicNodeContainer* evt) {};
    virtual void addCollection(EditorPhysicNodeContainer* col, Collection* collection) {};
    virtual void removeEditorPhysicNodeContainer(EditorPhysicNodeContainer* cor) {};
    virtual void openFile(const std::string& filePath) {};
    virtual void save(const std::string& filePath) {};
    virtual void run() {};
};

#endif /* defined(__CoolRun__EditorListener__) */
