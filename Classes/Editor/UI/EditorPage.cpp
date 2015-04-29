//
//  EditorPage.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "EditorPage.h"
#include "EditorMainMenu.h"
#include "GlobalDefined.h"
#include "EditorPhysicNodeContainer.h"
#include "MissionPage.h"
#include "MissionObjects.h"
#include "MissionCollection.h"
#include "Collection.h"

EditorPage::EditorPage()
: EditorNode()
, m_objects(nullptr)
, m_events(nullptr)
, m_collections(nullptr)
, m_realCollections(nullptr)
{
    
}
EditorPage::~EditorPage()
{
    CC_SAFE_RELEASE_NULL(m_objects);
    CC_SAFE_RELEASE_NULL(m_events);
    CC_SAFE_RELEASE_NULL(m_collections);
    CC_SAFE_RELEASE_NULL(m_realCollections);
}

bool EditorPage::init()
{
    if (!EditorNode::init())
    {
        return false;
    }
    
    CREATEANDRETAINARRAY(m_objects);
    CREATEANDRETAINARRAY(m_events);
    CREATEANDRETAINARRAY(m_collections);
    CREATEANDRETAINARRAY(m_realCollections);
    
    auto csize = Size(2528, 960);
    this->setContentSize(csize);
    
    this->getTouchListener()->setSwallowTouches(false);
    
    auto layer = LayerColor::create(Color4B(255, 255, 0, 150), csize.width/2, csize.height);
    this->addChild(layer);
    layer = LayerColor::create(Color4B(0, 255, 255, 150), csize.width/2, csize.height);
    layer->setPosition(csize.width/2, 0);
    this->addChild(layer);
//    layer = LayerColor::create(Color4B(0, 0, 255, 150), csize.width/3, csize.height);
//    layer->setPosition(csize.width/3 * 2, 0);
//    this->addChild(layer);
    
    auto enode1 = EditorNode::create();
    this->addChild(enode1);
    
    auto enode2 = EditorNode::create();
    this->addChild(enode2);
    
    return true;
}

void EditorPage::save(string* buffer)
{
    buffer->append("{");
    buffer->append("\"objects\": [");
    for (int i = 0; i < m_objects->count(); ++ i)
    {
        auto obj = dynamic_cast<EditorPhysicNodeContainer*>(m_objects->getObjectAtIndex(i));
        auto data = new string();
        data->append("{");
        obj->savePhysicNodeInfo(data);
        data->append("}");
        buffer->append(data->c_str());
        delete data;
        if (i != m_objects->count() - 1)
        {
            buffer->append(",");
        }
    }
    buffer->append("],");
    buffer->append("\"events\": [");
    for (int i = 0; i < m_events->count(); ++ i)
    {
        auto obj = dynamic_cast<EditorPhysicNodeContainer*>(m_events->getObjectAtIndex(i));
        auto data = new string();
        data->append("{");
        obj->savePhysicNodeInfo(data);
        data->append("}");
        buffer->append(data->c_str());
        delete data;
        if (i != m_events->count() - 1)
        {
            buffer->append(",");
        }
    }
    buffer->append("],");
    buffer->append("\"collections\": [");
    log("RealCollecion num is %ld", m_realCollections->count());
    log("Collection num is %ld", m_collections->count());
    CCASSERT(m_realCollections->count() == m_collections->count(), "Collection Num is error!");
    for (int i = 0; i < m_collections->count(); ++ i)
    {
        auto obj = dynamic_cast<EditorPhysicNodeContainer*>(m_collections->getObjectAtIndex(i));
        auto col = dynamic_cast<Collection*>(m_realCollections->getObjectAtIndex(i));
        auto data = new string();
        data->append("{");
        col->saveData(data);
        obj->savePhysicNodeInfo(data);
        data->append("}");
        buffer->append(data->c_str());
        delete data;
        if (i != m_collections->count() - 1)
        {
            buffer->append(",");
        }
    }
    buffer->append("]");
    buffer->append("}");
}

#pragma mark -

void EditorPage::clearPage()
{
    this->_clearArrayPhysicNode(m_objects);
    this->_clearArrayPhysicNode(m_events);
    this->_clearArrayPhysicNode(m_collections);
    m_realCollections->removeAllObjects();
}

void EditorPage::_clearArrayPhysicNode(__Array* arr)
{
    for (int i = 0; i < arr->count(); ++ i)
    {
        auto node = dynamic_cast<EditorNode*>(arr->getObjectAtIndex(i));
        node->removeFromParentAndCleanup(true);
    }
    arr->removeAllObjects();
}

void EditorPage::loadMissionPage(MissionPage* page)
{
    auto interface = page->getMissionInterface();
    this->_loadMissionDataInterface(interface->getMissionObjects());
    
    auto missionCollection = interface->getMissionCollection();
    auto collections = missionCollection->getCollections();
    for (int i = 0; i < collections->count(); ++ i)
    {
        auto col = dynamic_cast<Collection*>(collections->getObjectAtIndex(i));
        m_realCollections->addObject(col);
        auto pNode = col->createEditorPhysicNode();
        auto pos = pNode->getPosition();
        auto csize = pNode->getContentSize();
        pNode->setPosition(Vec2::ZERO);
        auto epnc = EditorPhysicNodeContainer::create();
        epnc->setEditorListener(this->getEditorListener());
        epnc->setPhysicNode(pNode);
        epnc->setPosition(pos);
        epnc->setContentSize(csize);
        this->addChild(epnc);
        m_collections->addObject(epnc);
    }
    //this->_loadMissionDataInterface(interface->getMissionCollection());
}

void EditorPage::_loadMissionDataInterface(MissionDataInterface* interface)
{
    this->_loadArrayPhysicNode(interface->getDirectionCollideObjects());
    this->_loadArrayPhysicNode(interface->getSimpleCollideObjects());
    this->_loadArrayPhysicNode(interface->getBulletCollideObjects());
}
void EditorPage::_loadArrayPhysicNode(__Array* arr)
{
    for (int i = 0; i < arr->count(); ++ i)
    {
        auto pNode = dynamic_cast<PhysicNode*>(arr->getObjectAtIndex(i));
        pNode->setForEditor(true);
        auto pos = pNode->getPosition();
        auto csize = pNode->getContentSize();
        pNode->setPosition(Vec2::ZERO);
        
        auto epnc = EditorPhysicNodeContainer::create();
        epnc->setEditorListener(this->getEditorListener());
        epnc->setPhysicNode(pNode);
        epnc->setPosition(pos);
        epnc->setContentSize(csize);
        this->addChild(epnc);
        m_objects->addObject(epnc);
        
    }
}

#pragma mark -

void EditorPage::editorNodeTouchBegan()
{
    
}
void EditorPage::editorNodeTouchMoved(int x, int y)
{
    
}
void EditorPage::editorNodeNoneMoveEnded()
{
    
    this->getEditorListener()->showMenu(EditorListener::MenuState::FIRST, EditorMainMenu::create());
}
void EditorPage::editorNodeMoveEnded()
{
    
}

void EditorPage::addObject(EditorPhysicNodeContainer *obj)
{
    m_objects->addObject(obj);
    this->addChild(obj);
}
void EditorPage::addEvent(EditorPhysicNodeContainer *evt)
{
    m_events->addObject(evt);
    this->addChild(evt);
}
void EditorPage::addCollection(EditorPhysicNodeContainer *col, Collection* collection)
{
    m_collections->addObject(col);
    m_realCollections->addObject(collection);
    this->addChild(col);
}
void EditorPage::removeEditorPhysicNodeContainer(EditorPhysicNodeContainer *epnc)
{
    m_objects->removeObject(epnc);
    m_events->removeObject(epnc);
    ssize_t index = m_collections->getIndexOfObject(epnc);
    if (CC_INVALID_INDEX != index)
    {
        m_collections->removeObject(epnc);
        m_realCollections->removeObjectAtIndex(index);
    }
    
    epnc->removeFromParentAndCleanup(true);
}