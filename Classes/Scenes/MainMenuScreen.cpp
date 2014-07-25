#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "HighscoresScreen.h"

USING_NS_CC;

Scene* MainMenuScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "MainMenuScreen" splash screen"
    auto background = Sprite::create("Backgrounds/main_menu_background.png");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);
    //add background falling blocks
	this->schedule(schedule_selector(MainMenuScreen::generateBox), FALLING_BLOCK_GENERATION_TIME);
    //main menu items
    auto menu_item_1 = MenuItemImage::create("UI/MainMenu/button_play.png","UI/MainMenu/button_play_pressed.png", CC_CALLBACK_1(MainMenuScreen::Play, this));
    //menu_item_1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    auto *menu = Menu::create(menu_item_1, NULL);
    menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 15));
    this->addChild(menu);
    //animation of waving Boto
    cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(BOTO_MM_PNG,BOTO_MM_PLIST,BOTO_MM_JSON);
    cocostudio::CCArmature *armature = cocostudio::CCArmature::create("MainMenuBoto");
	armature->setPosition(Point(visibleSize.width / 2, visibleSize.height / 16 * 3));
	armature->getAnimation()->playWithIndex(0);
	this->addChild(armature, 2);
	//add ground
	auto ground = Sprite::create("Backgrounds/ground.png");
	ground->setPosition(Point(visibleSize.width / 2, visibleSize.height / 16 * 2));
	this->addChild(ground, 1);

    return true;
}

//implementation of menu functions

void MainMenuScreen::Play(Ref *pSender)
{
	auto scenePlay = GameScreen::createScene();

	//transition to play scene
	Director::getInstance()->replaceScene(TransitionFade::create(TO_PLAY_SCENE_TRANSITION_TIME, scenePlay));
}

void MainMenuScreen::generateBox(float dt)
{
	//generating block
	Blocks *newBlock = new Blocks(Point(0,0));
	//positioning block
	float startWidth = newBlock->getSprite()->getContentSize().width/2;
	float endWidth =  visibleSize.width - newBlock->getSprite()->getContentSize().width/2;
	float height = visibleSize.height - newBlock->getSprite()->getContentSize().height/2;
	Vec2 point = Blocks::GeneratePoint(startWidth, endWidth, height);
	newBlock->setPosition(point);
	newBlock->DrawBlock(this);
	//setting scale and opacity
	float time =  Blocks::RandomFloatBetween(MIN_FALLING_TIME,MAX_FALLING_TIME);
	float farScale = 0.3f;
	float middleScale = 0.5f;
	float closeScale = 0.7f;
	if(time < 20.0f)
	{
		newBlock->getSprite()->setScale(closeScale);
		newBlock->getSprite()->setOpacity(225);
	}
	if(time >= 20.0f && time < 40.0f)
	{
		newBlock->getSprite()->setScale(middleScale);
		newBlock->getSprite()->setOpacity(178);
	}
	if(time >= 40.0f && time <= MAX_FALLING_TIME)
	{
		newBlock->getSprite()->setScale(farScale);
		newBlock->getSprite()->setOpacity(127);
	}
	//moving block
	auto move = MoveTo::create(time, Point(newBlock->getSprite()->getPosition().x, 0));
	auto remove = RemoveSelf::create(true);
	auto sequence = Sequence::create(move, remove, NULL);
	newBlock->getSprite()->runAction(sequence);
}

void MainMenuScreen::menuCloseCallback(Ref* pSender)
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
