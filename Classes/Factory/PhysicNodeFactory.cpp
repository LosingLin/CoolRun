//
//  PhysicNodeFactory.cpp
//  CoolRun
//
//  Created by ManYou on 14-8-15.
//
//

#include "PhysicNodeFactory.h"
#include "PhysicNode.h"
#include "Stone.h"
#include "Coin.h"
#include "Enemy.h"
#include "Spider.h"
#include "SpiderKind.h"
#include "SpiderPoison.h"
#include "SpiderSpines.h"
#include "SpiderFly.h"
#include "PoisonBullet.h"
#include "AlertBulletPoison.h"
#include "AlertBulletNet.h"
#include "Item.h"
#include "ItemSpare.h"
#include "ItemMagnet.h"
#include "ItemTimesCoin.h"
#include "ItemTimesJump.h"
#include "ItemDad.h"
#include "ItemLandBuild.h"
#include "ItemFly.h"
#include "Saw.h"
#include "TreasureBox.h"
#include "Jade.h"

PhysicNodeFactory* PhysicNodeFactory::m_instance = NULL;

PhysicNodeFactory::PhysicNodeFactory()
{

}
PhysicNodeFactory::~PhysicNodeFactory()
{
    this->purgeInstance();
}

PhysicNodeFactory* PhysicNodeFactory::getInstance()
{
    if (m_instance == NULL) {
        m_instance = new PhysicNodeFactory();
    }
    
    return m_instance;
}
void PhysicNodeFactory::purgeInstance()
{
    if (m_instance) {
        delete m_instance;
    }
}


PhysicNode* PhysicNodeFactory::create(rapidjson::Value& _value)
{
    auto pNodeType = kPhysicNodeUnknown;
    PhysicNode *_pNode = NULL;
    if (_value.HasMember("pNodeType")) {
        pNodeType = (PhysicNodeType)JsonHelp::getInt(_value["pNodeType"]);
    }
    switch (pNodeType) {
        case kPhysicNodeStone:
        {
            _pNode = Stone::create();
        } break;
        case kPhysicNodeCoin:
        {
            _pNode = Coin::create();
        } break;
        case kPhysicNodeSaw:
        {
            _pNode = Saw::create();
        } break;
        case kPhysicNodeEnemy:
        {
            _pNode = Enemy::create();
        } break;
        case kPhysicNodeSpider:
        {
            _pNode = Spider::create();
        } break;
        case kPhysicNodeSpiderKind:
        {
            _pNode = SpiderKind::create();
        } break;
        case kPhysicNodeSpiderPoison:
        {
            _pNode = SpiderPoison::create();
        } break;
        case kPhysicNodeSpiderSpines:
        {
            _pNode = SpiderSpines::create();
            
        } break;
        case kPhysicNodeSpiderFly:
        {
            _pNode = SpiderFly::create();
            
        } break;
        case kPhysicNodeBulletPoison:
        {
            _pNode = PoisonBullet::create();
            
        } break;
        case kPhysicNodeBulletAlertPoison:
        {
            _pNode = AlertBulletPoison::create();
        } break;
        case kPhysicNodeBulletAlertNet:
        {
            _pNode = AlertBulletNet::create();
        } break;
        case kPhysicNodeItem:
        {
            _pNode = Item::create();
        } break;
        case kPhysicNodeItemSpare:
        {
            _pNode = ItemSpare::create();
        } break;
        case kPhysicNodeItemMagnet:
        {
            _pNode = ItemMagnet::create();
        } break;
        case kPhysicNodeItemTimesCoin:
        {
            _pNode = ItemTimesCoin::create();
        } break;
        case kPhysicNodeItemTimesJump:
        {
            _pNode = ItemTimesJump::create();
        } break;
        case kPhysicNodeItemDad:
        {
            _pNode = ItemDad::create();
        } break;
        case kPhysicNodeItemLandBuild:
        {
            _pNode = ItemLandBuild::create();
        } break;
        case kPhysicNodeItemFly:
        {
            _pNode = ItemFly::create();
        } break;
        case kPhysicNodeTreasureBox:
        {
            _pNode = TreasureBox::create();
        } break;
        case kPhysicNodeJade:
        {
            _pNode = Jade::create();
        } break;
        default:
            break;
    }
    _pNode->setPhysicNodeType(pNodeType);
    _pNode->loadJson(_value);
    
    return _pNode;
}

Item* PhysicNodeFactory::createRandomItem()
{
    Item* _item = nullptr;
    int r = rand()%6;
    //r = 5;
    switch (r)
    {
        case 0:
        {
            _item = ItemMagnet::create();
        } break;
        case 1:
        {
            _item = ItemTimesCoin::create();
        } break;
        case 2:
        {
            _item = ItemTimesJump::create();
        } break;
        case 3:
        {
            _item = ItemDad::create();
        } break;
        case 4:
        {
            _item = ItemLandBuild::create();
        } break;
        case 5:
        {
            _item = ItemFly::create();
        } break;
            
        default:
            break;
    }
    
    return _item;
}