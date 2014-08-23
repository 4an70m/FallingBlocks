#include "GameScreen.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Point(0,-1000));

    //edge Node
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height * 1.5f), PHYSICSBODY_MATERIAL_DEFAULT,10);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/4 * 3));
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
    botoIsAlive = true;
	bonus = 0;
	multiplier = 1;
	numberOfBonuses = 1;

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
	this->schedule(schedule_selector(GameScreen::generateBlock), 1);
	this->schedule(schedule_selector(GameScreen::generateBonusBlock), 10);
	this->schedule(schedule_selector(GameScreen::generateMegaBlock), 40);

    //pause button declaration
	auto menuLabel = Label::createWithBMFont("fonts/west_england-64.fnt", "Pause",TextHAlignment::LEFT, visibleSize.width/5);
	menuLabel->setHeight(visibleSize.height/20);
	menuLabel->setScale(0.7);
	//menuLabel->setPosition(Point((visibleSize.width / 10 * 7) , (visibleSize.height * 19 / 20)));
	MenuItemLabel *menu_item_1 = MenuItemLabel::create(menuLabel, CC_CALLBACK_1(GameScreen::Pause, this));
	menu_item_1->setPosition(Point((visibleSize.width / 5) , (visibleSize.height * 19 / 20)));
	Menu *menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, BUTTONS_ZORDER);

	//Points label for points output

	pointsLabel = Label::createWithBMFont("fonts/west_england-64.fnt", "Points: 0",TextHAlignment::LEFT, visibleSize.width/7*2);
	pointsLabel->setHeight(visibleSize.height/20);
	pointsLabel->setScale(0.7);
	pointsLabel->setPosition(Point((visibleSize.width / 7 * 5) , (visibleSize.height * 19 / 20)));
	this->addChild(pointsLabel, BUTTONS_ZORDER);

	//single touch listener
	auto singleListener = EventListenerTouchOneByOne::create();
	singleListener->setSwallowTouches(true);
	singleListener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	singleListener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);

	//contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//sprites' textures initialization
	bonusSprite = Sprite::create(BONUS_SPEED);
	bonusSprite = Sprite::create(BONUS_SGRAVITY);
	bonusSprite = Sprite::create(BONUS_FGRAVITY);
	bonusSprite = Sprite::create(BONUS_SBOTO);
	bonusSprite = Sprite::create(BONUS_X2);

	newBlock = new Blocks();
	newBlock->init();
	coin = new Coins();

	return true;
}
//TRANSITIONS
void GameScreen::Pause(Ref *pSender)
{
	//implementation of pause scene
	auto scenePause = PauseOverlay::createScene();

	//pushes pause scene to the top of scene stack
	Director::getInstance()->pushScene(TransitionFade::create(TRANSITION_TIME,scenePause));
}

//GENERATION
void GameScreen::generateBlock(float dt)
{
	if (Blocks::createBlocks == false)
		return;
	newBlock = Blocks::create(
			Blocks::GeneratePoint(visibleSize.width / 10,
					visibleSize.width / 10 * 9,
					visibleSize.height / 10 * 9),
					Blocks::BlockSuperType::NORMAL_BLOCK);
	newBlock->drawBlock(this, BLOCK_ZORDER);
}
void GameScreen::generateBonusBlock(float dt)
{
	if (Blocks::createBlocks == false)
		return;
	newBlock = Blocks::create(
			Blocks::GeneratePoint(visibleSize.width / 10,
					visibleSize.width / 10 * 9,
					visibleSize.height / 10 * 9),
					Blocks::BlockSuperType::BONUS_BLOCK);
	newBlock->drawBlock(this, BLOCK_ZORDER);
}
void GameScreen::generateMegaBlock(float dt)
{
	if (!Blocks::createBlocks)
		return;
	Blocks::createBlocks = false;
	bonusBlockHealth = Blocks::RandomIntBetween(MIN_BONUS_BLOCK_HEALTH + numberOfBonuses * 5, MIN_BONUS_BLOCK_HEALTH + numberOfBonuses * 10);
	megaBlock = Blocks::create(Point(visibleSize.width / 2,
					visibleSize.height / 10 * 12),
					Blocks::BlockSuperType::MEGA_BLOCK);
	megaBlock->drawBlock(this, BLOCK_ZORDER, 20);
	numberOfBonuses++;
}
bool GameScreen::onContactBegin(const PhysicsContact& contact)
{
	//Boto collision with brick
	//Boto is destroyed
	if (CollisionManager::CheckCollision(contact, BLOCKS_BITMASK, BOTO_BITMASK))
	{
		CCLog("Block collision with boto");
		if(contact.getShapeA()->getBody()->getTag() != 0 || contact.getShapeB()->getBody()->getTag() != 0)
		{
			//we got bonus here
			if(contact.getShapeA()->getBody()->getCollisionBitmask() == BLOCKS_BITMASK)
			{
				bonus = contact.getShapeA()->getBody()->getTag();
			}
			else
			{
				bonus = contact.getShapeB()->getBody()->getTag();
			}
			bonusHandler();
		}
		else
		{
			botoIsAlive = false;
			BotoSprite::remove(contact, this);
			//endgame
		}
		point = Blocks::remove(contact, this);
		Blocks::emittParticles(this, point);
	}
	//block collision with Ground
	//block is destroyed
	if (CollisionManager::CheckCollision(contact, BLOCKS_BITMASK, GROUND_BITMASK))
	{
		CCLog("Block collision with ground");
		point = Blocks::remove(contact, this);
		Blocks::emittParticles(this, point);
		Coins::generateCoins(this, 1, point, COINS_ZORDER);
	}
	//collsion with coin
	//coin is destroyed
	if (CollisionManager::CheckCollision(contact, COIN_BITMASK, BOTO_BITMASK))
	{
		CCLog("Coin collision with boto");
		Coins::remove(contact, this);
		points += POINTS * multiplier;
		sprintf(text, "Points: %d", points);
		pointsLabel->setString(text);
	}
	return true;

}

//BONUS
void GameScreen::bonusHandler()
{
	acceptBonus();
	this->scheduleOnce(schedule_selector(GameScreen::negateBonus), 7.0f);
}
void GameScreen::acceptBonus()
{
	char *bonusName;
	switch(Blocks::BonusType(bonus))
	{
		case Blocks::BonusType::FAST_BOTO:
		{
			bonusName = BONUS_SPEED;
			botoSprite->setSpeed(10.0f);
			break;
		}
		case Blocks::BonusType::SLOW_GRAV:
		{
			bonusName = BONUS_SGRAVITY;
			m_world->setGravity(Vec2(0, -200));
			break;
		}
		case Blocks::BonusType::FAST_GRAV:
		{
			bonusName = BONUS_FGRAVITY;
			m_world->setGravity(Vec2(0, -1500));
			break;
		}
		case Blocks::BonusType::SMALL_BOTO:
		{
			bonusName = BONUS_SBOTO;
			botoSprite->createBody(0.5f);
			break;
		}
		case Blocks::BonusType::X2_POINTS:
		{
			bonusName = BONUS_X2;
			multiplier = 2;
			break;
		}
	}
	CCLog("%s", bonusName);
	bonusSprite = Sprite::create(bonusName);
	bonusSprite->setPosition(visibleSize.width / 2, visibleSize.height / 10);
	bonusSprite->setOpacity(0);
	this->addChild(bonusSprite, BUTTONS_ZORDER);

	auto fadeIn = FadeIn::create(0.8f);
	auto moveTo = MoveTo::create(0.8f, Point(visibleSize.width / 2, visibleSize.height / 10 * 6));
	auto fadeOut = FadeOut::create(1.2f);
	auto removeSelf = RemoveSelf::create(true);
	auto sequence =Sequence::create(fadeIn, fadeOut, removeSelf, NULL);

	bonusSprite->runAction(moveTo);
	bonusSprite->runAction(sequence);
}
void GameScreen::negateBonus(float dt)
{
	switch(Blocks::BonusType(bonus))
	{
		case Blocks::BonusType::FAST_BOTO:
		{
			botoSprite->setSpeed(5.0f);
			break;
		}
		case Blocks::BonusType::SLOW_GRAV:
		{
			m_world->setGravity(Vec2(0, -1000));
			break;
		}
		case Blocks::BonusType::FAST_GRAV:
		{
			m_world->setGravity(Vec2(0, -1000));
			break;
		}
		case Blocks::BonusType::SMALL_BOTO:
		{
			botoSprite->createBody(1.0f);
			break;
		}
		case Blocks::BonusType::X2_POINTS:
		{
			multiplier = 1;
			break;
		}
	}
	bonus = 0;
}

//TOUCHES
bool GameScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	current_node = nodeUnderTouch(touch);

	if(current_node != nullptr)
	{
		bonusBlockHealth--;
		//if block was destoyed, lets just return normal blocks generation
		if(bonusBlockHealth <= 0)
		{
			Blocks::createBlocks = true;
			Coins::generateCoins(this, numberOfBonuses * 20, current_node->getPosition(), COINS_ZORDER);
			point = megaBlock->remove(this);
			for(int i = 0; i < 5; i++)
			{
				Blocks::emittParticles(this, Point(
						point.x + rand() % (int)visibleSize.width/10 - visibleSize.width/20,
						point.y + rand() % (int)visibleSize.height/10 - visibleSize.height/20));
			}
		}
		Coins::generateCoins(this, 1, touch->getLocation(), COINS_ZORDER);
	}
	else
	{
		if(touch->getLocation().x<visibleSize.width/2)
		{

			if(botoIsAlive)
			{
				botoSprite->stopMoveRight();
				botoSprite->startMoveLeft();
			}
		}
		else
		{
			if(botoIsAlive)
			{
				botoSprite->stopMoveLeft();
				botoSprite->startMoveRight();
			}
		}
	}
	return true;
}

void GameScreen::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if(touch->getLocation().x<visibleSize.width/2)
	{

		if(botoIsAlive)
		{
			botoSprite->stopMoveLeft();
		}
	}
	else
	{
		if(botoIsAlive)
		{
			botoSprite->stopMoveRight();
		}
	}
}
Node* GameScreen::nodeUnderTouch(cocos2d::Touch *touch)
 {
	if (bonusBlockHealth <= 0)
		return nullptr;
     Node* node = nullptr;
     auto location = this->convertTouchToNodeSpace(touch);
     auto scene = Director::getInstance()->getRunningScene();
     auto arr = scene->getPhysicsWorld()->getShapes(location);
     for (auto& obj : arr)
     {
         //find it
         if ( obj->getBody()->getCollisionBitmask() == MEGABLOCK_BITMASK)
         {
             node = obj->getBody()->getNode();
             break;
         }
     }
     return node;
 }
//UPDATE
void GameScreen::update(float dt)
{
	if(botoIsAlive)
	{
		botoSprite->move(botoSprite->getSpeed());
	}
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
    delete newBlock;
    newBlock = nullptr;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
