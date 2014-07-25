#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__
#define TRANSITION_TIME 1.0f

#include "cocos2d.h"
#include "MainMenuScreen.h"
#include "PauseOverlay.h"
#include "Defenitions.h"
#include "CollisionManager.h"
#include "BotoSprite.h"
#include "Blocks.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/cocostudio.h"

class GameScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScreen);

    void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}

    void Pause(cocos2d::Ref *pSender);
    void TestDeath(cocos2d::Ref *pSender);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void generateBox(float dt);
    float randomFloatBetween(float smallNumber ,float bigNumber);
    bool onContactBegin(const cocos2d::PhysicsContact& contact);
    void MoveLeft(cocos2d::Ref *pSender);
    void MoveRight(cocos2d::Ref *pSender);
    void MoveJump(cocos2d::Ref *pSender);
    void update(float dt);
    void PressLeftButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void ReleaseLeftButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void PressRightButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void ReleaseRightButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void PressJumpButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void ReleaseJumpButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
private:
    BotoSprite *botoSprite;
    cocos2d::CCSprite *leftButton;
    cocos2d::CCSprite *rightButton;
    cocos2d::CCSprite *jumpButton;
    cocos2d::PhysicsWorld* m_world;
    cocos2d::Size visibleSize;
    int points;
    cocos2d::CCLabelTTF* ttf1;
};

#endif // __GAME_SCREEN_H__
