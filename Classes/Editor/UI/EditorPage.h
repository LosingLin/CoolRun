//
//  EditorPage.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__EditorPage__
#define __CoolRun__EditorPage__

#include "cocos2d.h"
#include "EditorNode.h"
#include "JsonHelp.h"

USING_NS_CC;

class MissionPage;
class MissionDataInterface;
class EditorPhysicNodeContainer;
class EditorPage : public EditorNode
{
public:
    EditorPage();
    ~EditorPage();
    
    virtual bool init() override;
    CREATE_FUNC(EditorPage);
    
    void clearPage();
    void loadMissionPage(MissionPage* page);
    
    void save(string* buffer);
    
    virtual void editorNodeTouchBegan() override;
    virtual void editorNodeTouchMoved(int x, int y) override;
    virtual void editorNodeNoneMoveEnded() override;
    virtual void editorNodeMoveEnded() override;
    
    void addObject(EditorPhysicNodeContainer *obj);
    void addEvent(EditorPhysicNodeContainer *evt);
    void addCollection(EditorPhysicNodeContainer *col, Collection* collection);
    void removeEditorPhysicNodeContainer(EditorPhysicNodeContainer *epnc);
private:
    void _clearArrayPhysicNode(__Array* arr);
    void _loadMissionDataInterface(MissionDataInterface* interface);
    void _loadArrayPhysicNode(__Array* arr);
private:
    
    //data
    __Array* m_objects;
    __Array* m_events;
    __Array* m_collections;
    
    __Array* m_realCollections;
};

#endif /* defined(__CoolRun__EditorPage__) */
