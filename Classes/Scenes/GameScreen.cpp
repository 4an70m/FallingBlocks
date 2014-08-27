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
	pressedPause = false;

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

    //pause button declaration
	auto menu_item = MenuItemImage::create(PAUSE_BUTTON,PAUSE_BUTTON_PRESSED, CC_CALLBACK_1(GameScreen::Pause, this));
	auto menu = Menu::create(menu_item, NULL);
	menu->setPosition(Point(0 + visibleSize.width / 1920 * 200 / 2, visibleSize.height - visibleSize.height / 1920 * 200 / 2));
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
	tap1 = Sprite::create(TAP_PATH);

	newBlock = new Blocks();
	newBlock->init();
	coin = new Coins();
	pause = Sprite::create(PAUSE_BACKGROUND);
	pause = Sprite::create(GAMEOVER_BACKGROUND);
	musicIsOn = true;
	tutorial();
	return true;
}

void GameScreen::tutorial()
{
	newBlock = Blocks::create(Point(visibleSize.width/2, visibleSize.height), Blocks::BlockSuperType::NORMAL_BLOCK);
	newBlock->drawBlock(this, BLOCK_ZORDER, 10);

	Label *lab = Label::createWithBMFont("fonts/west_england-64.fnt", "Avoid!",TextHAlignment::RIGHT, visibleSize.width/7*2);
	lab->setHeight(visibleSize.height/20);
	auto small = ScaleTo::create(0.5, 0.3);
	auto big = ScaleTo::create(0.5, 1);
	auto seq = Sequence::create(small, big, NULL);
	auto rep = RepeatForever::create(seq);
	lab->runAction(rep);

	newBlock->getSprite()->addChild(lab,BLOCK_ZORDER);

	this->scheduleOnce(schedule_selector(GameScreen::startGeneration), 5);
}
void GameScreen::startGeneration(float dt)
{
	//blocks generation
	this->schedule(schedule_selector(GameScreen::generateBlock), 1);
	this->schedule(schedule_selector(GameScreen::generateBonusBlock), 10);
	this->schedule(schedule_selector(GameScreen::generateMegaBlock), 40);
}

//PAUSE
void GameScreen::Pause(Ref *pSender)
{
	if(!pressedPause)
	{
		pressedPause = !pressedPause;
		Director::getInstance()->pause();

		pause = Sprite::create(PAUSE_BACKGROUND);

		auto itemOn = MenuItemImage::create(SOUND_BUTTON,SOUND_BUTTON);
		auto itemOff = MenuItemImage::create(SOUND_BUTTON_PRESSED,SOUND_BUTTON_PRESSED);
		toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScreen::toggleSound, this),itemOn, itemOff, NULL);

		if (musicIsOn == false)
		{
			toggle->setSelectedIndex(1);
		}

		auto menu_item_1 = MenuItemImage::create(BACK_BUTTON, BACK_BUTTON_PRESSED, CC_CALLBACK_1(GameScreen::back, this));
		auto menu_item_3 = MenuItemImage::create(MENU_BUTTON,MENU_BUTTON_PRESSED, CC_CALLBACK_1(GameScreen::toMainMenu, this));

		Menu *menu = Menu::create(menu_item_1,toggle,menu_item_3,  NULL);
		menu->alignItemsHorizontallyWithPadding(visibleSize.height / 1920 * 40);
		menu->setPosition(Point(pause->getContentSize().width/ 2, pause->getContentSize().height/ 5 * 2));

		pause->addChild(menu, UI_ZORDER);
		pause->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(pause, UI_ZORDER);
	}
	else
	{
		pressedPause = !pressedPause;
		Director::getInstance()->resume();

		this->removeChild(pause, true);
	}
}
void GameScreen::back(Ref *pSender)
{
	pressedPause = !pressedPause;
	Director::getInstance()->resume();

	this->removeChild(pause, true);
}
void GameScreen::toggleSound(Ref *pSender)
{
	if(musicIsOn)
	{
		musicIsOn = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC, true);
		musicIsOn = true;
	}
}
void GameScreen::toMainMenu(Ref *pSender)
{
	Director::getInstance()->resume();
	auto mainMenuScene = MainMenuScreen::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0,mainMenuScene));
}
void GameScreen::gameOverHandler()
{
	this->pauseSchedulerAndActions();
	pause = Sprite::create(GAMEOVER_BACKGROUND);

	auto itemOn = MenuItemImage::create(SOUND_BUTTON,SOUND_BUTTON);
	auto itemOff = MenuItemImage::create(SOUND_BUTTON_PRESSED,SOUND_BUTTON_PRESSED);
	toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameScreen::toggleSound, this),itemOn, itemOff, NULL);

	if (musicIsOn == false)
	{
		toggle->setSelectedIndex(1);
	}

	auto menu_item_1 = MenuItemImage::create(RETRY_BUTTON, RETRY_BUTTON_PRESSED, CC_CALLBACK_1(GameScreen::retry, this));
	auto menu_item_3 = MenuItemImage::create(MENU_BUTTON,MENU_BUTTON_PRESSED, CC_CALLBACK_1(GameScreen::toMainMenu, this));

	Menu *menu = Menu::create(menu_item_1,toggle,menu_item_3,  NULL);
	menu->alignItemsHorizontallyWithPadding(visibleSize.height / 1920 * 40);
	menu->setPosition(Point(pause->getContentSize().width/ 2, pause->getContentSize().height/ 5 * 2));

	pause->addChild(menu, UI_ZORDER);
	pause->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pause, UI_ZORDER);
}
void GameScreen::retry(cocos2d::Ref *pSender)
{
	auto scenePlay = GameScreen::createScene();
	Director::getInstance()->replaceScene(scenePlay);
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
	megablockHelper();
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
		    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BONUS_PICKUP);
		}
		else
		{
			botoIsAlive = false;
			BotoSprite::remove(contact, this);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_DESTROYED);
			gameOverHandler();
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
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BLOCK_BREAK);
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

	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(COIN_PICKUP);
	}
	//collision with megablock
	if (CollisionManager::CheckCollision(contact, MEGABLOCK_BITMASK, BOTO_BITMASK) ||
			CollisionManager::CheckCollision(contact, MEGABLOCK_BITMASK, GROUND_BITMASK))
	{
		CCLog("MEGABLOCK PREVOZMOGAET!!");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_DESTROYED);
		botoSprite->remove(this);
		point = megaBlock->remove(this);
		for(int i = 0; i < 5; i++)
		{
			Blocks::emittParticles(this, Point(
					point.x + rand() % (int)visibleSize.width/10 - visibleSize.width/20,
					point.y + rand() % (int)visibleSize.height/10 - visibleSize.height/20));
		}
		gameOverHandler();
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
		int randomSound = rand() % 3;
		switch(randomSound)
		{
			case 0: {CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_HIT); break;}
			case 1: {CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_HIT2); break;}
			case 2: {CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_HIT3); break;}
		}
		bonusBlockHealth--;
		//if block was destoyed, lets just return normal blocks generation
		if(bonusBlockHealth <= 0)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(MEGABLOCK_DESTROYED);
			Blocks::createBlocks = true;
			Coins::generateCoins(this, numberOfBonuses * 10, current_node->getPosition(), COINS_ZORDER);
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
		if(botoIsAlive)
		{
			if(touch->getLocation().x<visibleSize.width/2)
			{
				botoSprite->stopMoveRight();
				botoSprite->startMoveLeft();
				if(botoSprite->getPosition().x < botoSprite->getSprite()->getContentSize().width)
				{
					CCLog("too left");
					botoSprite->setPosition(Point(botoSprite->getSprite()->getContentSize().width,botoSprite->getPosition().y));
				}
			}
			else
			{
				botoSprite->stopMoveLeft();
				botoSprite->startMoveRight();
				if(botoSprite->getPosition().x > visibleSize.width - botoSprite->getSprite()->getContentSize().width)
				{
					CCLog("too right");
					botoSprite->setPosition(Point(visibleSize.width - botoSprite->getSprite()->getContentSize().width ,botoSprite->getPosition().y));
				}
			}
		}
	}
	return true;
}
void GameScreen::megablockHelper()
{
	tap1 = Sprite::create(TAP_PATH);
	tap1->setScale(visibleSize.height / 1920);
	tap1->setPosition(Point((visibleSize.width / 8 * 2) , (visibleSize.height / 8 * 3)));
	tap1->setOpacity(0);
	this->addChild(tap1, BOTO_ZORDER);

	tap2 = Sprite::create(TAP_PATH);
	tap2->setScale(visibleSize.height / 1920);
	tap2->setPosition(Point((visibleSize.width / 8 * 4) , (visibleSize.height / 8 * 3)));
	tap2->setOpacity(0);
	this->addChild(tap2, BOTO_ZORDER);

	tap3 = Sprite::create(TAP_PATH);
	tap3->setScale(visibleSize.height / 1920);
	tap3->setPosition(Point((visibleSize.width / 8 * 6) , (visibleSize.height / 8 * 3)));
	tap3->setOpacity(0);
	this->addChild(tap3, BOTO_ZORDER);

	FadeIn *fade1 = FadeIn::create(0.2);
	ScaleTo *scDN1 = ScaleTo::create(0.5,0.3);
	ScaleTo *scUP1 = ScaleTo::create(0.5,visibleSize.height / 1920);
	FadeOut *fadeOut1 = FadeOut::create(0.2);
	RemoveSelf *rs1 = RemoveSelf::create();
	auto seq1 = Sequence::create(fade1,scDN1,scUP1,scDN1, scUP1, fadeOut1, rs1, NULL);

	FadeIn *fade2 = FadeIn::create(0.2);
	ScaleTo *scDN2 = ScaleTo::create(0.5,0.3);
	ScaleTo *scUP2 = ScaleTo::create(0.5,visibleSize.height / 1920);
	FadeOut *fadeOut2 = FadeOut::create(0.2);
	RemoveSelf *rs2 = RemoveSelf::create();
	auto seq2 = Sequence::create(fade2,scDN2,scUP2,scDN2, scUP2, fadeOut2, rs2, NULL);

	FadeIn *fade3 = FadeIn::create(0.2);
	ScaleTo *scDN3 = ScaleTo::create(0.5,0.3);
	ScaleTo *scUP3 = ScaleTo::create(0.5,visibleSize.height / 1920);
	FadeOut *fadeOut3 = FadeOut::create(0.2);
	RemoveSelf *rs3 = RemoveSelf::create();
	auto seq3 = Sequence::create(fade3,scDN3,scUP3,scDN3, scUP3, fadeOut3, rs3, NULL);


	tap1->runAction(seq1);
	tap2->runAction(seq2);
	tap3->runAction(seq3);



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
