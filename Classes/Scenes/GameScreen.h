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
#include "Ground.h"
#include "Coins.h"
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
    //TOUCHES
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    Node* nodeUnderTouch(cocos2d::Touch *touch);
    //GENERATIONS
    void generateBlock(float dt);
    void generateBonusLevel(float dt);
    void generateBonusBlock(float dt);
    //CONTACTS
    bool onContactBegin(const cocos2d::PhysicsContact& contact);
    //MOVES
    void MoveLeft(cocos2d::Ref *pSender);
    void MoveRight(cocos2d::Ref *pSender);
    void MoveJump(cocos2d::Ref *pSender);
    void update(float dt);
    //BUTTONS
    void PressLeftButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void ReleaseLeftButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void PressRightButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    void ReleaseRightButton(cocos2d::Object *sender, cocos2d::extension::Control::EventType controlEvent);
    //BONUS
    void bonusHandler();
    void acceptBonus();
    void negateBonus(float dt);

private:
    BotoSprite *botoSprite;
    Ground *ground;

    cocos2d::Sprite *leftButton;
    cocos2d::Sprite *rightButton;

    cocos2d::PhysicsWorld* m_world;
    cocos2d::Size visibleSize;
    cocos2d::Node *current_node;
    cocos2d::LabelTTF *pointsLabel;
    cocos2d::Point point;
    char text[256];
    //block
    Blocks *newBlock;
    Blocks *bonusBlock;
    unsigned int points;
    bool botoIsAlive;
    //megablock
    bool bonusIsOn;
    int bonusBlockHealth;
    unsigned int numberOfBonuses;
    //bonuses
    int bonusGenSpeed;
	int bonus;
	int time;
	int multiplier;

};

#endif // __GAME_SCREEN_H__
