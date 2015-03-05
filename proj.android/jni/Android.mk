LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/CoolRunScene.cpp \
                   ../../Classes/GameController.cpp \
                   ../../Classes/Base/DrawableNode.cpp \
                   ../../Classes/Editor/Listener/EditorListener.cpp \
                   ../../Classes/Editor/Scene/EditorScene.cpp \
                   ../../Classes/Editor/UI/EditorCollectionMenu.cpp \
                   ../../Classes/Editor/UI/EditorDetailMenu.cpp \
                   ../../Classes/Editor/UI/EditorItemMenu.cpp \
                   ../../Classes/Editor/UI/EditorMainMenu.cpp \
                   ../../Classes/Editor/UI/EditorMenu.cpp \
                   ../../Classes/Editor/UI/EditorNode.cpp \
                   ../../Classes/Editor/UI/EditorObjectMenu.cpp \
                   ../../Classes/Editor/UI/EditorOpenFileMenu.cpp \
                   ../../Classes/Editor/UI/EditorPage.cpp \
                   ../../Classes/Editor/UI/EditorPhysicNodeContainer.cpp \
                   ../../Classes/Editor/UI/EditorPhysicNodeMenu.cpp \
                   ../../Classes/Editor/UI/EditorScrollMenu.cpp \
                   ../../Classes/Editor/UI/EditorSelector.cpp \
                   ../../Classes/Editor/UI/EditorText.cpp \
                   ../../Classes/Editor/UI/EditorTextInput.cpp \
                   ../../Classes/Event/Event.cpp \
                   ../../Classes/Factory/CollectionFactory.cpp \
                   ../../Classes/Factory/PhysicNodeFactory.cpp \
                   ../../Classes/Mission/Mission.cpp \
                   ../../Classes/Mission/MissionCollection.cpp \
                   ../../Classes/Mission/MissionDataInterface.cpp \
                   ../../Classes/Mission/MissionEvent.cpp \
                   ../../Classes/Mission/MissionInterface.cpp \
                   ../../Classes/Mission/MissionObjects.cpp \
                   ../../Classes/Mission/MissionPage.cpp \
                   ../../Classes/Object/AlertBullet.cpp \
                   ../../Classes/Object/AlertBulletPoison.cpp \
                   ../../Classes/Object/AlertBulletNet.cpp \
                   ../../Classes/Object/Animal.cpp \
                   ../../Classes/Object/Boss.cpp \
                   ../../Classes/Object/BossBullet.cpp \
                   ../../Classes/Object/BossDoubleHeads.cpp \
                   ../../Classes/Object/Bullet.cpp \
                   ../../Classes/Object/Coin.cpp \
                   ../../Classes/Object/Collection.cpp \
                   ../../Classes/Object/CollectionCoin.cpp \
                   ../../Classes/Object/CollideNode.cpp \
                   ../../Classes/Object/Enemy.cpp \
                   ../../Classes/Object/Home.cpp \
                   ../../Classes/Object/HomeHelp.cpp \
                   ../../Classes/Object/Item.cpp \
                   ../../Classes/Object/ItemDad.cpp \
                   ../../Classes/Object/ItemFly.cpp \
                   ../../Classes/Object/ItemLandBuild.cpp \
                   ../../Classes/Object/ItemMagnet.cpp \
                   ../../Classes/Object/ItemSpare.cpp \
                   ../../Classes/Object/ItemTimesCoin.cpp \
                   ../../Classes/Object/ItemTimesJump.cpp \
                   ../../Classes/Object/Land.cpp \
                   ../../Classes/Object/PoisonBullet.cpp \
                   ../../Classes/Object/Runner.cpp \
                   ../../Classes/Object/Spider.cpp \
                   ../../Classes/Object/SpiderKind.cpp \
                   ../../Classes/Object/SpiderPoison.cpp \
                   ../../Classes/Object/SpiderSpines.cpp \
                   ../../Classes/Object/SpiderFly.cpp \
                   ../../Classes/Object/Stone.cpp \
                   ../../Classes/Object/Saw.cpp \
                   ../../Classes/Object/Villager.cpp \
                   ../../Classes/Physics/CollideRect.cpp \
                   ../../Classes/Physics/CollideTrack.cpp \
                   ../../Classes/Physics/CollideTrackListener.cpp \
                   ../../Classes/Physics/GravityPhysics.cpp \
                   ../../Classes/Physics/MultipleCollideNode.cpp \
                   ../../Classes/Physics/PhysicHelp.cpp \
                   ../../Classes/Physics/PhysicNode.cpp \
                   ../../Classes/Physics/PhysicNodeDirection.cpp \
                   ../../Classes/Physics/PhysicNodeSimple.cpp \
                   ../../Classes/Scene/ChapterScene.cpp \
                   ../../Classes/Scene/MenuScene.cpp \
                   ../../Classes/Scene/SettingScene.cpp \
                   ../../Classes/Scene/VillageScene.cpp \
                   ../../Classes/UI/Background.cpp \
                   ../../Classes/UI/Dialog.cpp \
                   ../../Classes/UI/HpBar.cpp \
                   ../../Classes/UI/MYButton.cpp \
                   ../../Classes/UI/MYTextInput.cpp \
                   ../../Classes/UI/PopViewLayer.cpp \
                   ../../Classes/UI/Score.cpp \
                   ../../Classes/UI/Stretch.cpp \
                   ../../Classes/Utils/ActionHelp.cpp \
                   ../../Classes/Utils/JsonHelp.cpp 


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Base \
					$(LOCAL_PATH)/../../Classes/Editor \
					$(LOCAL_PATH)/../../Classes/Editor/Help \
					$(LOCAL_PATH)/../../Classes/Editor/IO \
					$(LOCAL_PATH)/../../Classes/Editor/Listener \
					$(LOCAL_PATH)/../../Classes/Editor/Scene \
					$(LOCAL_PATH)/../../Classes/Editor/UI \
					$(LOCAL_PATH)/../../Classes/Event \
					$(LOCAL_PATH)/../../Classes/Factory \
					$(LOCAL_PATH)/../../Classes/Mission	\
					$(LOCAL_PATH)/../../Classes/Object \
					$(LOCAL_PATH)/../../Classes/Physics \
					$(LOCAL_PATH)/../../Classes/Scene \
					$(LOCAL_PATH)/../../Classes/UI \
					$(LOCAL_PATH)/../../Classes/Utils 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

$(call import-module,extensions)
$(call import-module,editor-support/cocostudio)


# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
