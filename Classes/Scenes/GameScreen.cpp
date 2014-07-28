#include "GameScreen.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Point(0,-1000));

    //edge Node
    Size visibleSize2 = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize2, PHYSICSBODY_MATERIAL_DEFAULT,10);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize2.width/2,visibleSize2.height/2));
	edgeNode->setContentSize(Size(visibleSize2.width,visibleSize2.height/2));
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

    auto background = Sprite::create(GAME_SCENE_BACKGROUND);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

    //pause button declaration
	auto menu_item_1 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScreen::Pause, this));
	menu_item_1->setPosition(Point((visibleSize.width / 5) * 4, (visibleSize.height * 19 / 20)));
	auto *menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, 5);

	/*
	char text[256];
	sprintf(text,"Points: %d", points);
	ttf1 = CCLabelTTF::create(text, "Helvetica", 40,
											   CCSizeMake(245, 60), kCCTextAlignmentCenter);
	ttf1->setPosition(Point((visibleSize.width / 5) * 4, (visibleSize.height * 17 / 20)));
	ttf1->setColor(Color3B(cocos2d::Color3B::WHITE));
	this->addChild(ttf1);
	*/

	//single touch listener
	//adding event listener
	//auto singleListener = EventListenerTouchOneByOne::create();
	//singleListener->setSwallowTouches(true);

	//singleListener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	//singleListener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	//singleListener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


	//Left button
	auto sp1 = Sprite::create(LEFT_BUTTON);
	auto leftButtonPic = cocos2d::extension::Scale9Sprite::create(LEFT_BUTTON);
	auto leftButtonPicPressed = cocos2d::extension::Scale9Sprite::create(LEFT_BUTTON_PRESSED);
	cocos2d::extension::ControlButton *leftButton = cocos2d::extension::ControlButton::create(leftButtonPic);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressLeftButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseLeftButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	leftButton->setBackgroundSpriteForState(leftButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	leftButton->setPosition(Point(visibleSize.width / 8, visibleSize.height / 17));
	leftButton->setPreferredSize(sp1->getContentSize());
	this->addChild(leftButton, 2);

	//Right button
	auto sp2 = Sprite::create(RIGHT_BUTTON);
	auto rightButtonPic = cocos2d::extension::Scale9Sprite::create(RIGHT_BUTTON);
	auto rightButtonPicPressed = cocos2d::extension::Scale9Sprite::create(RIGHT_BUTTON_PRESSED);
	cocos2d::extension::ControlButton *rightButton = cocos2d::extension::ControlButton::create(rightButtonPic);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressRightButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseRightButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	rightButton->setBackgroundSpriteForState(rightButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	rightButton->setPosition(Point(visibleSize.width / 8 * 2.5f, visibleSize.height / 17));
	rightButton->setPreferredSize(sp2->getContentSize());
	this->addChild(rightButton, 2);

	//Jump button
	auto sp3 = Sprite::create(JUMP_BUTTON);
	auto jumpButtonPic = cocos2d::extension::Scale9Sprite::create(JUMP_BUTTON);
	auto jumpButtonPicPressed = cocos2d::extension::Scale9Sprite::create(JUMP_BUTTON_PRESSED);
	cocos2d::extension::ControlButton *jumpButton = cocos2d::extension::ControlButton::create(jumpButtonPic);
	jumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressJumpButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	jumpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseJumpButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	jumpButton->setBackgroundSpriteForState(jumpButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	jumpButton->setPosition(Point(visibleSize.width / 8 * 7, visibleSize.height / 17));
	jumpButton->setPreferredSize(sp3->getContentSize());
	this->addChild(jumpButton, 2);

	//boto sprite added
	botoSprite = new BotoSprite();
	botoSprite->Draw(this);


	this->scheduleUpdate();

	this->schedule(schedule_selector(GameScreen::generateBox), BLOCK_GENERATION_TIME);

	//add ground
	auto ground = Sprite::create(GAME_SCENE_GROUND);
	ground->setPosition(Point(visibleSize.width / 2, visibleSize.height / 15));
	auto groundBody = PhysicsBody::createEdgeBox(ground->getContentSize());
	groundBody->setDynamic(false);
	groundBody->setGravityEnable(false);
	groundBody->setContactTestBitmask(true);
	groundBody->setCollisionBitmask(GROUND_BITMASK);
	ground->setPhysicsBody(groundBody);
	this->addChild(ground, 1);

    return true;
}

void GameScreen::Pause(Ref *pSender)
{
	//implementation of pause scene
	auto scenePause = PauseOverlay::createScene();

	//pushes pause scene to the top of scene stack
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME,scenePause));
}

bool GameScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	current_node = nodeUnderTouch(touch);

	if(current_node == newBlock->getSprite())
	{
		CCLog("got it!");
		newBlock->setPosition(touch->getLocation());
	}
	else
	{
		CCLog("missed :c");
	}
	return true;
}

void GameScreen::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	newBlock->setPosition(touch->getLocation());
}

void GameScreen::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
}

void GameScreen::generateBox(float dt)
{
	newBlock = new Blocks(Point(0,0));
	float startWidth = newBlock->getSprite()->getContentSize().width/2;
	float endWidth =  visibleSize.width - newBlock->getSprite()->getContentSize().width/2;
	float height = visibleSize.height - newBlock->getSprite()->getContentSize().height/2;
	Vec2 point = Blocks::GeneratePoint(startWidth, endWidth, height);
	newBlock->setPosition(point);
	newBlock->drawBlock(this);
}



bool GameScreen::onContactBegin(const PhysicsContact& contact)
{
	//collision with ground for jumping
	if (CollisionManager::CheckCollision(contact, GROUND_BITMASK, BOTO_BITMASK))
	{
		botoSprite->yesJumpable();
		botoSprite->stopMoveJump();
	}
	//collision with brick
	//brick is destroyed
	if (CollisionManager::CheckCollision(contact, BLOCKS_BITMASK, BOTO_BITMASK))
	{
		if(BLOCKS_BITMASK == contact.getShapeA()->getBody()->getCollisionBitmask())
		{
			Coins::generateCoins(this, 10, Point(700,700));
			this->removeChild(contact.getShapeA()->getBody()->getNode());
		}
		else
		{
			Coins::generateCoins(this, 10, Point(700,700));
			this->removeChild(contact.getShapeB()->getBody()->getNode());
		}
	}
	//collsion with coin
	//coin is destroyed
	if (CollisionManager::CheckCollision(contact, COIN_BITMASK, BOTO_BITMASK))
	{
		if(COIN_BITMASK == contact.getShapeA()->getBody()->getCollisionBitmask())
		{
			this->removeChild(contact.getShapeA()->getBody()->getNode());
		}
		else
		{
			this->removeChild(contact.getShapeB()->getBody()->getNode());
		}
	}


/*

 	if (sp1CollBitmask == GROUND_BITMASK && sp2CollBitmask == BOTO_BITMASK
 			|| sp2CollBitmask == GROUND_BITMASK && sp1CollBitmask == BOTO_BITMASK)
 	{
 		botoSprite->yesJumpable();
 		botoSprite->stopMoveJump();
 	}
 	//hitting block
 	if (sp1CollBitmask == BLOCKS_BITMASK && sp2CollBitmask == BOTO_BITMASK)
	{
 		CCLog("Collision1");
 		auto temp = contact.getShapeA()->getBody()->getNode();
 		Coins::generateCoins(this, 10, temp->getPosition());
 		temp->removeFromParentAndCleanup(true);
	}
 	if (sp2CollBitmask == BLOCKS_BITMASK && sp1CollBitmask == BOTO_BITMASK)
 	{
 		CCLog("Collision2");
 		auto temp = contact.getShapeB()->getBody()->getNode();
 		Coins::generateCoins(this, 10, temp->getPosition());
 		temp->removeFromParentAndCleanup(true);
 	}
 	//hitting coin
	if (sp1CollBitmask == COIN_BITMASK && sp2CollBitmask == BOTO_BITMASK)
	{
		CCLog("Coin");
		auto temp = (Sprite*)contact.getShapeA()->getBody()->getNode();
		temp->removeFromParent();
	}
	if (sp2CollBitmask == COIN_BITMASK && sp1CollBitmask == BOTO_BITMASK)
	{
		CCLog("Coin");
		auto temp = (Sprite*)contact.getShapeB()->getBody()->getNode();
		temp ->removeFromParent();

	}
*/
	return true;
}

void GameScreen::PressLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press left");
	botoSprite->stopMoveRight();
	botoSprite->startMoveLeft();
}
void GameScreen::ReleaseLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release left");
	botoSprite->stopMoveLeft();
}
void GameScreen::PressRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press right");
	botoSprite->stopMoveLeft();
	botoSprite->startMoveRight();
}
void GameScreen::ReleaseRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release right");
	botoSprite->stopMoveRight();
}
void GameScreen::PressJumpButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Press jump");
	botoSprite->startMoveJump();
}
void GameScreen::ReleaseJumpButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	CCLog("Release jump");
}

void GameScreen::update(float dt)
{
	//CCLog("update!");

	botoSprite->Move(5.0f);
	botoSprite->Jump(70.0f);
}

Node* GameScreen::nodeUnderTouch(cocos2d::Touch *touch)
{
    Node* node = nullptr;
    auto location = this->convertTouchToNodeSpace(touch);
    auto scene = Director::getInstance()->getRunningScene();
    auto arr = scene->getPhysicsWorld()->getShapes(location);
    for (auto& obj : arr)
    {
        //find it
        if ( obj->getBody()->getNode() == newBlock->getSprite())
        {
            node = obj->getBody()->getNode();
            break;
        }
    }
    return node;
}

void GameScreen::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

    //destruction
    delete botoSprite;
    botoSprite = nullptr;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
