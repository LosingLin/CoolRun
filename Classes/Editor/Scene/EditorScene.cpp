//
//  EditorScene.cpp
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#include "EditorScene.h"
#include "EditorUIBase.h"
#include "EditorZOrder.h"
#include "MYTextInput.h"
#include "EditorPage.h"
#include "EditorScrollMenu.h"
#include "EditorMainMenu.h"
#include "EditorPhysicNodeContainer.h"
#include "JsonHelp.h"
#include "MissionPage.h"
#include <sys/stat.h>
//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>

#include "Mission.h"
#include "CoolRunScene.h"
#include "MYScene.h"


#define kEditorTempFile  "Temp"

EditorScene::EditorScene()
: Layer()
, m_scrollView(nullptr)
, m_content(nullptr)
, m_firstMenuContainer(nullptr)
, m_state(MenuState::NONE)
, m_secondMenuContainer(nullptr)
, m_thirdMenuContainer(nullptr)
, m_curPage(nullptr)
, m_fileName(nullptr)
{
}
EditorScene::~EditorScene()
{
    if (m_fileName)
    {
        delete m_fileName;
        m_fileName = nullptr;
    }
    
}

bool EditorScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    m_content = Node::create();
    m_scrollView = ScrollView::create(Size(visibleSize.width, 640), m_content);
    m_scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    m_scrollView->setDelegate(this);
    m_scrollView->setLocalZOrder(kPageScrollViewZOrder);
    this->addChild(m_scrollView);
    
    m_curPage = EditorPage::create();
    m_curPage->setEditorListener(this);
    m_content->addChild(m_curPage);
    m_scrollView->setContentSize(m_curPage->getContentSize());
    
    //m_scrollView->setViewSize(Size(visibleSize.width - 200, visibleSize.height));
    
    m_firstMenuContainer = EditorScrollMenu::create();
    m_firstMenuContainer->setAnchorPoint(Vec2(0, 0));
    m_firstMenuContainer->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
    m_firstMenuContainer->setLocalZOrder(kFirstMenuScrollViewZOrder);
    this->addChild(m_firstMenuContainer);
    
    m_secondMenuContainer = EditorScrollMenu::create();
    m_secondMenuContainer->setAnchorPoint(Vec2(0, 0));
    m_secondMenuContainer->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
    m_secondMenuContainer->setLocalZOrder(kSecondMenuScrollViewZOrder);
    this->addChild(m_secondMenuContainer);
    
    m_thirdMenuContainer = EditorScrollMenu::create();
    m_thirdMenuContainer->setAnchorPoint(Vec2(0, 0));
    m_thirdMenuContainer->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
    m_thirdMenuContainer->setLocalZOrder(kThirdMenuScrollViewZOrder);
    this->addChild(m_thirdMenuContainer);
    
    auto savaFilePath = FileUtils::getInstance()->getWritablePath();
    savaFilePath.append("D_Editor/");
    if (access(savaFilePath.c_str(), F_OK) != 0)
    {
        if (mkdir(savaFilePath.c_str(), S_IRWXU | S_IRGRP | S_IXGRP) != 0)
        {
            this->showAlter("ERROR: mkdir xx_Editor failed!");
            
        }
    }
    savaFilePath.append(kEditorTempFile);
    if (access(savaFilePath.c_str(), F_OK) != 0)
    {
        FILE* fp = fopen(savaFilePath.c_str(), "wt");
        if (!fp)
        {
            this->showAlter("ERROR: create temp file failed!");
        }
        else
        {
            auto data = new string();
            data->append("{\"objects\":[], \"events\":[], \"collections\":[]}");
            fwrite(data->c_str(), strlen(data->c_str()), 1, fp);
            fclose(fp);
            delete data;
        }
        
    }
    
    this->openFile(kEditorTempFile);
    
    return true;
}

Scene* EditorScene::createScene()
{
    auto scene = MYScene::create();
    auto layer = EditorScene::create();
    scene->addChild(layer);
    return scene;
}

void EditorScene::setFileName(const string& filename)
{
    if (m_fileName)
    {
        delete m_fileName;
        m_fileName = nullptr;
    }
    
    m_fileName = new string(filename);
    
}

void EditorScene::showAlter(const string& msg)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto alter = EditorText::create(msg, Size(600, 100), 40);
    alter->setAnchorPoint(Vec2(0.5, 0.5));
    alter->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    alter->setZOrder(kAlterPopViewZOrder);
    this->addChild(alter);
    alter->setScale(0.5);
    
    auto scaleTo = ScaleTo::create(0.2, 1);
    auto delayTime = DelayTime::create(0.2);
    auto fadeOut = FadeOut::create(0.2);
    auto call = CallFunc::create(CC_CALLBACK_0(EditorScene::showAlterDone, this, alter));
    alter->runAction(Sequence::create(scaleTo, delayTime, fadeOut, call, NULL));
}
void EditorScene::showAlterDone(Node* alter)
{
    alter->removeFromParentAndCleanup(true);
}

#pragma mark - editor listener
EditorMenu* EditorScene::getMenu(MenuState state)
{
    EditorMenu* menu = nullptr;
    switch (state)
    {
        case MenuState::FIRST:
        {
            menu = m_firstMenuContainer->getMenu();
        }
            break;
        case MenuState::SECOND:
        {
            menu = m_secondMenuContainer->getMenu();
        }
            break;
        case MenuState::THIRD:
        {
            menu = m_thirdMenuContainer->getMenu();
        }
            break;
        default:
            break;
    }
    
    return menu;
}

void EditorScene::showMenu(MenuState state, EditorMenu* menu)
{
    menu->setEditorListener(this);
    
    switch (state)
    {
        case MenuState::FIRST:
        {
            this->_hideMenu(m_secondMenuContainer);
            this->_hideMenu(m_thirdMenuContainer);
            
            if (m_state == MenuState::FIRST)
            {
                auto _menu = m_firstMenuContainer->getMenu();
                
                
                if (_menu->getMenuType() != menu->getMenuType())
                {
                    this->_hideMenu(m_firstMenuContainer);
                }
                else
                {
                    return;
                }
            }
            m_firstMenuContainer->setMenu(menu);
            this->_showMenu(m_firstMenuContainer);
            
            m_state = MenuState::FIRST;
        }
            break;
        case MenuState::SECOND:
        {
            if (m_state == MenuState::NONE)
            {
                CCASSERT(0, "MENU ERROR!");
            }
            this->_hideMenu(m_thirdMenuContainer);
            if (m_state == MenuState::SECOND)
            {
                auto _menu = m_secondMenuContainer->getMenu();
                if (_menu->getMenuType() != menu->getMenuType())
                {
                    this->_hideMenu(m_secondMenuContainer);
                }
                else
                {
                    return;
                }
            }
            
            m_secondMenuContainer->setMenu(menu);
            this->_showMenu(m_secondMenuContainer);
            
            m_state = MenuState::SECOND;
        } break;
            
        case MenuState::THIRD:
        {
            if (m_state == MenuState::NONE || m_state == MenuState::FIRST)
            {
                CCASSERT(0, "MENU ERROR!");
            }
            if (m_state == MenuState::THIRD)
            {
                auto _menu = m_thirdMenuContainer->getMenu();
                if (_menu->getMenuType() != menu->getMenuType())
                {
                    this->_hideMenu(m_thirdMenuContainer);
                }
                else
                {
                    return;
                }
            }
            
            m_thirdMenuContainer->setMenu(menu);
            this->_showMenu(m_thirdMenuContainer);
            
            m_state = MenuState::THIRD;
        } break;
            
        default:
            break;
    }
    
    this->layoutScene();
}

void EditorScene::hideMenu(MenuState state)
{
    switch (state)
    {
        case MenuState::FIRST:
        {
            this->_hideMenu(m_firstMenuContainer);
            this->_hideMenu(m_secondMenuContainer);
            this->_hideMenu(m_thirdMenuContainer);
            m_state = MenuState::NONE;
        }
            break;
        case MenuState::SECOND:
        {
            this->_hideMenu(m_secondMenuContainer);
            this->_hideMenu(m_thirdMenuContainer);
            m_state = MenuState::FIRST;
        }
            break;
        case MenuState::THIRD:
        {
            this->_hideMenu(m_thirdMenuContainer);
            m_state = MenuState::SECOND;
        }
            break;
        default:
            break;
    }
    this->layoutScene();
}

void EditorScene::addObject(EditorPhysicNodeContainer* obj)
{
    auto offset = m_scrollView->getContentOffset();
//    auto viewSize = m_scrollView->getViewSize();
    auto pos = Vec2(-offset.x, -offset.y);
    obj->setPosition(pos);
    obj->setEditorListener(this);
    m_curPage->addObject(obj);
}
void EditorScene::addEvent(EditorPhysicNodeContainer* evt)
{
    
}
void EditorScene::addCollection(EditorPhysicNodeContainer* col, Collection* collection)
{
    col->setEditorListener(this);
    m_curPage->addCollection(col, collection);
}
void EditorScene::removeEditorPhysicNodeContainer(EditorPhysicNodeContainer* cor)
{
    m_curPage->removeEditorPhysicNodeContainer(cor);
    this->hideMenu(EditorListener::MenuState::FIRST);
}
void EditorScene::openFile(const std::string& filePath)
{
    if ("" == filePath || " " == filePath)
    {
        this->showAlter("Please input file name");
        return;
    }
    string data = string();
    bool isExist = false;
    if (FileUtils::getInstance()->isFileExist(filePath))
    {
        
        data = FileUtils::getInstance()->getStringFromFile(filePath);
        log("FILEPATH: %s\n", FileUtils::getInstance()->fullPathForFilename(filePath).c_str());
        
        this->setFileName(FileUtils::getInstance()->fullPathForFilename(filePath));
        isExist = true;
    }
    else
    {
        auto doc = FileUtils::getInstance()->getWritablePath();
        doc.append("D_Editor/").append(filePath);
        log("FILEPATH: %s\n", doc.c_str());
        if (access(doc.c_str(), F_OK) == 0)
        {
            this->setFileName(doc);
            
            unsigned char* buffer = nullptr;
            ssize_t size = 0;
            size_t readsize;
           
            FILE *fp = fopen(doc.c_str(), "rt");
            if (!fp)
            {
                isExist = false;
            }
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            
            buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
            buffer[size] = '\0';
            
            readsize = fread(buffer, sizeof(unsigned char), size, fp);
            fclose(fp);
            
            
            if (nullptr == buffer || 0 == readsize)
            {
                std::string msg = "Get data from file(";
                msg.append(filePath).append(") failed!");
                this->showAlter(msg);
            }
            else
            {
                data = string((const char*)buffer);
            }
            
            isExist = true;
        }
    }
    
    log("Load Data : %s", data.c_str());
    
    if (isExist)
    {
        rapidjson::Document doc;
        doc.Parse<0>(data.c_str());
        if (doc.HasParseError())
        {
            CCASSERT(false, "json parse error");
        }
        m_curPage->clearPage();
        auto missionPage = MissionPage::create(doc);
        m_curPage->loadMissionPage(missionPage);
        
        this->hideMenu(EditorListener::MenuState::FIRST);
    }
    else
    {
        this->showAlter("FILE IS NOT EXIST!");
    }
    
}
void EditorScene::save(const std::string& filePath)
{
    string savaFilePath = string();
    //打开的文件
    if (this->getFileName())
    {
        if (access(this->getFileName()->c_str(), W_OK) == 0)
        {
            savaFilePath = string(this->getFileName()->c_str());
        }
        else
        {
            string str = string(this->getFileName()->c_str());
            str.append(" CAN'T BE WRITE!");
            this->showAlter(str);
        }
    }
    //新建或者覆盖文件
    else
    {
        if ("" == filePath || " " == filePath)
        {
            this->showAlter("Please input file name");
            return;
        }

        savaFilePath = FileUtils::getInstance()->getWritablePath();
        savaFilePath.append("D_Editor/");
        savaFilePath.append(filePath);
        
    }
    
    log("SAVE FILE PATH: %s", savaFilePath.c_str());
    
    FILE* fp = fopen(savaFilePath.c_str(), "wt");
    if (fp)
    {
        auto data = new string();
        m_curPage->save(data);
        fwrite(data->c_str(), strlen(data->c_str()), 1, fp);
        fclose(fp);
        log("SAVE: %s", data->c_str());
        delete data;
        
        this->showAlter("SAVE SUCCESSED!");
    }
    else
    {
        string str = string(filePath.c_str());
        str.append(" CAN'T BE SAVE!");
        this->showAlter(str);
    }
    

    int r = access(savaFilePath.c_str(), W_OK);
    log("WRITE : %d", r);
    
    r = access(savaFilePath.c_str(), R_OK);
    log("READ : %d", r);
}

void EditorScene::run()
{
    //default save
    this->save("");
    
    auto data = new string();
    data->append("{");
    data->append("\"pages\":[");
    m_curPage->save(data);
    data->append("]}");
    log("%s", data->c_str());
    auto mission = Mission::createWithDataStr(data->c_str());
    mission->setMissionRepeatModel(Mission::MissionRepeatModel::ALL);
    auto cr = CoolRun::createScene(mission);
    Director::getInstance()->replaceScene(cr);
}


#pragma mark - help

void EditorScene::layoutScene()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    auto menuSize = m_menuContainer->getContentSize();
//    m_scrollView->setViewSize(Size(visibleSize.width - menuSize.width, visibleSize.height));
    switch (m_state)
    {
        case MenuState::NONE:
        {
            m_scrollView->setViewSize(Size(visibleSize.width, 640));
        }
            break;
        case MenuState::FIRST:
        {
            auto pos = m_firstMenuContainer->getPosition();
            m_scrollView->setViewSize(Size(pos.x, 640));
        }
            break;
        case MenuState::SECOND:
        {
            auto pos = m_secondMenuContainer->getPosition();
            m_scrollView->setViewSize(Size(pos.x, 640));
        }
            break;
        case MenuState::THIRD:
        {
            auto pos = m_thirdMenuContainer->getPosition();
            m_scrollView->setViewSize(Size(pos.x, 640));
        }
            break;
            
        default:
            break;
    }
}

void EditorScene::_hideMenu(EditorScrollMenu* container)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    container->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
    container->setMenu(EditorMenu::create());
}
void EditorScene::_showMenu(EditorScrollMenu* container)
{
    if (container == m_firstMenuContainer)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto csize = m_firstMenuContainer->getContentSize();
        auto pos = m_firstMenuContainer->getPosition();
        container->setPosition(Vec2(origin.x + visibleSize.width - csize.width, pos.y));
    }
    else if (container == m_secondMenuContainer)
    {
        auto csize = m_secondMenuContainer->getContentSize();
        auto pos = m_firstMenuContainer->getPosition();
        container->setPosition(Vec2(pos.x - csize.width, pos.y));
    }
    else if (container == m_thirdMenuContainer)
    {
        auto csize = m_thirdMenuContainer->getContentSize();
        auto pos = m_secondMenuContainer->getPosition();
        container->setPosition(Vec2(pos.x - csize.width, pos.y));
    }
}

