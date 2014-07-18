#include "GameScreen.h"
#include "GameOverScreen.h"
#include "PauseScreen.h"
#include "extensions/cocos-ext.h"
#include "editor-support/cocostudio/cocostudio.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Point(0,-500));
    //scene->getPhysicsWorld()->setUpdateRate(0.0000001f);

    Size visibleSize2 = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize2, PHYSICSBODY_MATERIAL_DEFAULT,10);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize2.width/2,visibleSize2.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);



    // 'layer' is an autorelease object
    auto layer = GameScreen::create();

    layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    points = 0;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "GameScreen" splash screen"
    auto background = Sprite::create("Backgrounds/game_scene_background.png");


    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(background, 0);

    //pause button implementation
	auto menu_item_1 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScreen::Pause, this));
	auto menu_item_2 = MenuItemFont::create("Test Game Over", CC_CALLBACK_1(GameScreen::TestDeath, this));

	menu_item_1->setPosition(Point((visibleSize.width / 5) * 4, (visibleSize.height * 19 / 20)));
	menu_item_2->setPosition(Point((visibleSize.width / 5) * 4, (visibleSize.height * 18 / 20)));

	char text[256];
	sprintf(text,"Points: %d", points);
	ttf1 = CCLabelTTF::create(text, "Helvetica", 40,
		                                       CCSizeMake(245, 60), kCCTextAlignmentCenter);
	ttf1->setPosition(Point((visibleSize.width / 5) * 4, (visibleSize.height * 17 / 20)));
	ttf1->setColor(Color3B(cocos2d::Color3B::WHITE));
	this->addChild(ttf1);

	auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	//test game sprite
	spriteTetBoy = Sprite::create("Sprites/Robot.png");
	spriteTetBoy->setPosition(Point(visibleSize.width/2, visibleSize.height/6));
	//physiscs!!
	auto tetBoyBody = PhysicsBody::createBox(spriteTetBoy->getContentSize());
	tetBoyBody->setGravityEnable(true);
	tetBoyBody->setTag(1);
	//tetBoyBody->setContactTestBitmask(true);
	spriteTetBoy->setPhysicsBody(tetBoyBody);
	//~physiscs bitch!!
	this->addChild(spriteTetBoy, 0);

	//movement implementation
	//single touch listener

	//adding event listener
	auto singleListener = EventListenerTouchOneByOne::create();
	singleListener->setSwallowTouches(true);

	//singleListener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	//singleListener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	singleListener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);

	//this->schedule(schedule_selector(GameScreen::generateBox), 1.0f);
/*
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
*/

	//Left button
	auto leftButtonPic = cocos2d::extension::Scale9Sprite::create("UI/left_button.png");
	auto leftButtonPicPressed = cocos2d::extension::Scale9Sprite::create("UI/left_button_pressed.png");
	cocos2d::extension::ControlButton *leftButton = cocos2d::extension::ControlButton::create(leftButtonPic);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressLeftButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseLeftButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	leftButton->setBackgroundSpriteForState(leftButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	leftButton->setPosition(Point(100,100));
	leftButton->setPreferredSize(Size(100,100));
	this->addChild(leftButton);

	//Right button
	auto rightButtonPic = cocos2d::extension::Scale9Sprite::create("UI/right_button.png");
	auto rightButtonPicPressed = cocos2d::extension::Scale9Sprite::create("UI/right_button_pressed.png");
	cocos2d::extension::ControlButton *rightButton = cocos2d::extension::ControlButton::create(rightButtonPic);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressRightButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseRightButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	rightButton->setBackgroundSpriteForState(rightButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	rightButton->setPosition(Point(200,100));
	rightButton->setPreferredSize(Size(100,100));
	this->addChild(rightButton);

	//Jump button
	auto jumpButtonPic = cocos2d::extension::Scale9Sprite::create("UI/jump_button.png");
	auto jumpButtonPicPressed = cocos2d::extension::Scale9Sprite::create("UI/jump_button_pressed.png");
	cocos2d::extension::ControlButton *jumpButton = cocos2d::extension::ControlButton::create(jumpButtonPic);
	jumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressJumpButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	jumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseJumpButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	jumpButton->setBackgroundSpriteForState(jumpButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	jumpButton->setPosition(Point(700,100));
	jumpButton->setPreferredSize(Size(100,100));
	this->addChild(jumpButton);
	this->scheduleUpdate();

    return true;
}

void GameScreen::TestDeath(Ref *pSender)
{
	//test implementation of game over
	auto sceneGameOver = GameOverScreen::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,sceneGameOver));
}

void GameScreen::Pause(Ref *pSender)
{
	//implementation of pause scene
	auto scenePause = PauseScreen::createScene();

	//pushes pause scene to the top of scene stack
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME,scenePause));
}

bool GameScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	float posX = touch->getLocation().x;
	float robotHalfSize = spriteTetBoy->getContentSize().width / 2.0f;
	visibleSize = Director::getInstance()->getVisibleSize();

	if(touch->getLocation().x >= (visibleSize.width - robotHalfSize))
	{
		posX = visibleSize.width - robotHalfSize;
	}
	if(touch->getLocation().x <= robotHalfSize)
	{
		posX = robotHalfSize;
	}
	spriteTetBoy->setPositionX(posX);
	return true;
}

void GameScreen::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	float posX = touch->getLocation().x;
	float robotHalfSize = spriteTetBoy->getContentSize().width / 2.0f;
	visibleSize = Director::getInstance()->getVisibleSize();

	if(touch->getLocation().x >= (visibleSize.width - robotHalfSize))
	{
		posX = visibleSize.width - robotHalfSize;
	}
	if(touch->getLocation().x <= robotHalfSize)
	{
		posX = robotHalfSize;
	}
	spriteTetBoy->setPositionX(posX);
}

void GameScreen::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	//not needed
}

void GameScreen::generateBox(float dt)
{
	Sprite *box = Sprite::create("Sprites/Box.png");
	float boxSizeX = box->getContentSize().width;
	//physiscs!!
	auto body = PhysicsBody::createBox(box->getContentSize());
	body->setTag(2);
	body->setContactTestBitmask(true);
	box->setPhysicsBody(body);
	//~physiscs!!
	box->setPositionX(randomFloatBetween(boxSizeX, visibleSize.width - boxSizeX));
	box->setPositionY(visibleSize.height - box->getContentSize().height);
	this->addChild(box);

	float duration = 4.0f;

	//auto boxMove = MoveTo::create(duration, Point(box->getPosition().x, (0.0f - box->getContentSize().height)));
	//auto boxRemove = RemoveSelf::create(true);
	//auto sequence = Sequence::create(boxMove, boxRemove, NULL);
	//box->runAction(sequence);
}

float GameScreen::randomFloatBetween(float smallNumber ,float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}

bool GameScreen::onContactBegin(const PhysicsContact& contact)
{
	auto sp1 = (PhysicsBody*)contact.getShapeA()->getBody();
	auto sp2 = (PhysicsBody*)contact.getShapeB()->getBody();
	int tag1 = sp1->getTag();
	int tag2 = sp2->getTag();
	CCLog("tag1 = %d, tag2 = %d", tag1, tag2);
	if (tag1 == 1 && tag2 == 2)
	{
		CCLog("ouch!1");
		/*sp2->removeFromWorld();
		sp2->release();*/
		auto sp22 = (Sprite*)contact.getShapeB()->getBody()->getNode();
		sp22->removeFromParent();
		//sp22->removeAllComponents();
		points++;

	}
	if (tag1 == 2 && tag2 == 1)
	{
		CCLog("ouch!2");
		/*sp1->removeFromWorld();
		sp1->release();*/
		auto sp21 = (Sprite*)contact.getShapeA()->getBody()->getNode();
		sp21->removeFromParent();
		//sp21->removeAllComponents();
		points++;
	}
	char text[256];
	sprintf(text,"Points: %d", points);
	ttf1->setString(text);

	return true;
}

void GameScreen::MoveLeft(cocos2d::Ref *pSender)
{
	CCLog("Move left beatch!");
	moveLeft = true;
}

void GameScreen::MoveRight(cocos2d::Ref *pSender)
{
	CCLog("Move right beatch!");
	moveRight = true;
}

void GameScreen::MoveJump(cocos2d::Ref *pSender)
{
	CCLog("Jump beatch!");
	moveJump = true;
}
void GameScreen::PressLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press left");
	moveLeft = true;
}
void GameScreen::ReleaseLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release left");
	moveLeft = false;
}
void GameScreen::PressRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press right");
	moveRight = true;
}
void GameScreen::ReleaseRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release right");
	moveRight = false;
}
void GameScreen::PressJumpButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press jump");
	moveJump = true;
}
void GameScreen::ReleaseJumpButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release jump");
	//moveRight = false;
}

void GameScreen::update(float dt)
{
	//CCLog("update!");
	if (moveLeft == true)
	{
		spriteTetBoy->setPositionX(spriteTetBoy->getPositionX()-5.0f);
		//moveLeft = false;
	}
	if (moveRight == true)
	{
		spriteTetBoy->setPositionX(spriteTetBoy->getPositionX()+5.0f);
		//moveRight = false;
	}
	if (moveJump == true)
	{
		auto actionJump = MoveTo::create(0.5f,Point(spriteTetBoy->getPosition().x, spriteTetBoy->getPosition().y + 100.0f));
		spriteTetBoy->runAction(actionJump);
		moveJump = false;
	}

}

void GameScreen::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
