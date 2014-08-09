#include "GameScreen.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Point(0,-1000));
/*
    //edge Node
    Size visibleSize2 = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize2, PHYSICSBODY_MATERIAL_DEFAULT,10);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize2.width/2,visibleSize2.height/2));
	edgeNode->setContentSize(Size(visibleSize2.width,visibleSize2.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);
*/
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
	block = 0;
    points = 0;
    bonusIsOn = false;
    numberOfBonuses = 0;
    botoIsAlive = true;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add background
    auto background = Sprite::create(GAME_SCENE_BACKGROUND);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

	//boto sprite added
	botoSprite = new BotoSprite();
	botoSprite->draw(this, BOTO_ZORDER);

	//add ground
	ground = new Ground();
	ground->draw(this, GROUND_ZORDER);

	//covers movements updates
	this->scheduleUpdate();

	//blocks generation
	this->schedule(schedule_selector(GameScreen::generateBlock),
			//MIN_BLOCK_GENERATION_TIME + MAX_BLOCK_GENERATION_TIME / (points + 1));
			2);
	//bonus lvl generation
	//this->scheduleOnce(schedule_selector(GameScreen::generateBonusLevel), 5
	//		);

    //pause button declaration
	MenuItemFont::setFontName("fonts/Fat Pixels.ttf");
	MenuItemFont::setFontSize(visibleSize.height / 50.0f);
	MenuItemFont *menu_item_1 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScreen::Pause, this));
	menu_item_1->setPosition(Point((visibleSize.width / 5) , (visibleSize.height * 19 / 20)));
	Menu *menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, BUTTONS_ZORDER);

	//Points label for points output
	/*
	pointsLabel = LabelTTF::create("Points: 0", "fonts/Fat Pixels.ttf", visibleSize.height / 50.0f);
	pointsLabel->setPosition(Point((visibleSize.width / 5 * 4) , (visibleSize.height * 19 / 20)));
	this->addChild(pointsLabel, BUTTONS_ZORDER);
	 */

	//single touch listener
	//adding event listener
	auto singleListener = EventListenerTouchOneByOne::create();
	singleListener->setSwallowTouches(true);
	singleListener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);

	//contact listener

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Left button
	auto sp1 = Sprite::create(LEFT_BUTTON);
	auto leftButtonPic = cocos2d::extension::Scale9Sprite::create(LEFT_BUTTON);
	auto leftButtonPicPressed = cocos2d::extension::Scale9Sprite::create(LEFT_BUTTON_PRESSED);
	cocos2d::extension::ControlButton *leftButton = cocos2d::extension::ControlButton::create(leftButtonPic);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressLeftButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressLeftButton),cocos2d::extension::Control::EventType::DRAG_ENTER);
	leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseLeftButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	leftButton->setBackgroundSpriteForState(leftButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	leftButton->setPosition(Point(visibleSize.width / 8, visibleSize.height / 17));
	leftButton->setPreferredSize(sp1->getContentSize());
	this->addChild(leftButton, BUTTONS_ZORDER);

	//Right button
	auto sp2 = Sprite::create(RIGHT_BUTTON);
	auto rightButtonPic = cocos2d::extension::Scale9Sprite::create(RIGHT_BUTTON);
	auto rightButtonPicPressed = cocos2d::extension::Scale9Sprite::create(RIGHT_BUTTON_PRESSED);
	cocos2d::extension::ControlButton *rightButton = cocos2d::extension::ControlButton::create(rightButtonPic);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressRightButton),cocos2d::extension::Control::EventType::TOUCH_DOWN);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::PressRightButton),cocos2d::extension::Control::EventType::DRAG_ENTER);
	rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScreen::ReleaseRightButton),cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
	rightButton->setBackgroundSpriteForState(rightButtonPicPressed, cocos2d::extension::ControlButton::State::HIGH_LIGHTED);
	rightButton->setPosition(Point(visibleSize.width / 8 * 7, visibleSize.height / 17));
	rightButton->setPreferredSize(sp2->getContentSize());
	this->addChild(rightButton, BUTTONS_ZORDER);

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
	//if bonus lvl is not playing then lets just proceede
	if(bonusIsOn == false)
	{
		return true;
	}
	current_node = nodeUnderTouch(touch);

	if(current_node != nullptr)
	{
		bonusBlockHealth--;
		//if block was destoyed, lets just return normal blocks generation
		if(bonusBlockHealth <= 0)
		{
			Blocks::createBlocks = true;
			bonusIsOn = false;
			Coins::generateCoins(this, numberOfBonuses * 20, current_node->getPosition(), COINS_ZORDER);
		}
		Coins::generateCoins(this, 1, touch->getLocation(), COINS_ZORDER);
	}

	return true;
}

void GameScreen::generateBonusLevel(float dt)
{
	bonusIsOn = true;
	bonusBlockHealth = Blocks::RandomIntBetween(MIN_BONUS_BLOCK_HEALTH + numberOfBonuses * 15, MIN_BONUS_BLOCK_HEALTH + numberOfBonuses * 20);
	Blocks::createBlocks = false;

	bonusBlock = new Blocks(Point(0,0), true);

	float width = visibleSize.width / 2;
	float height = visibleSize.height + bonusBlock->getSprite()->getContentSize().height / 2;
	bonusBlock->setPosition(Point(width, height));

	auto falling = MoveTo::create(MAX_FALLING_TIME, Point(width, 0));
	bonusBlock->getSprite()->runAction(falling);
	bonusBlock->drawBlock(this, BLOCK_ZORDER);
}

void GameScreen::generateBlock(float dt)
{
	CCLog("Generate block");
	if(Blocks::createBlocks == false)
		return;
	CCLog("Block %d was generated", ++block);

	float startWidth = visibleSize.width / 10;
	float endWidth =  visibleSize.width / 10 * 9;
	float height = visibleSize.height / 10 * 9;
	Vec2 pointQ = Blocks::GeneratePoint(startWidth, endWidth, height);

	newBlock = new Blocks(pointQ, false);
	CCLog("Block type = %s", newBlock->getBlockType());
	newBlock->drawBlock(this, BLOCK_ZORDER);


}

bool GameScreen::onContactBegin(const PhysicsContact& contact)
{
	//Boto collision with brick
	//Boto is destroyed
	if (CollisionManager::CheckCollision(contact, BLOCKS_BITMASK, BOTO_BITMASK))
	{
		CCLog("Block collision with boto");
		botoIsAlive = false;
		BotoSprite::remove(contact, this);
		point = Blocks::remove(contact, this);
		Blocks::emittParticles(this, point);
		//endgame
	}

	//Block collision with Ground
	//Block is destroyed
	if (CollisionManager::CheckCollision(contact, BLOCKS_BITMASK, GROUND_BITMASK))
	{
		CCLog("Block collision with ground");
		point = Blocks::remove(contact, this);
		CCLog("Block %d was destroyed", block);
		CCLog("Emitter went crazy");
		Blocks::emittParticles(this, point);
		Coins::generateCoins(this, 1, point, COINS_ZORDER);
		return false;
	}

	//collsion with coin
	//coin is destroyed
	if (CollisionManager::CheckCollision(contact, COIN_BITMASK, BOTO_BITMASK))
	{
		CCLog("Coin collision with boto");
		Coins::remove(contact, this);
		/*
		points += POINTS;
		sprintf(text, "Points: %d", points);
		pointsLabel->setString(text);
		pointsLabel->draw();
		*/
	}
	return true;

}

void GameScreen::PressLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	if(botoIsAlive)
	{
		botoSprite->stopMoveRight();
		botoSprite->startMoveLeft();
	}
}
void GameScreen::ReleaseLeftButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	if(botoIsAlive)
	{
		botoSprite->stopMoveLeft();
	}
}
void GameScreen::PressRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	if(botoIsAlive)
	{
		botoSprite->stopMoveLeft();
		botoSprite->startMoveRight();
	}
}
void GameScreen::ReleaseRightButton(Object *sender, cocos2d::extension::Control::EventType controlEvent)
{
	if(botoIsAlive)
	{
		botoSprite->stopMoveRight();
	}
}

void GameScreen::update(float dt)
{
	if(botoIsAlive)
	{
		botoSprite->move(5.0f);
	}
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
        if ( obj->getBody()->getCollisionBitmask() == BIGBLOCK_BITMASK)
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
