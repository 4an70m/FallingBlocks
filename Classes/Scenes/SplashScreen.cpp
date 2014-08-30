#include "SplashScreen.h"

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    glClearColor(1.0,1.0,1.0,1.0);

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // add "SplashScreen" splash screen"
   splashScreen = Sprite::create(SPLASH_SCREEN);

    // position the splashScreen on the center of the screen
   splashScreen->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the splashScreen as a child to this layer
    this->addChild(splashScreen, 0);

    cover1 = Sprite::create(INTRO_PAGE_1);
    cover2 = Sprite::create(INTRO_PAGE_2);
    cover3 = Sprite::create(INTRO_PAGE_3);
    cover1->setVisible(false);
	cover2->setVisible(false);
	cover3->setVisible(false);
	cover1->setPosition(Vec2(visibleSize.width * 2, visibleSize.height/2 + origin.y));
	cover2->setPosition(Vec2(visibleSize.width * 2, visibleSize.height/2 + origin.y));
	cover3->setPosition(Vec2(visibleSize.width * 2 , visibleSize.height/2 + origin.y));
	this->addChild(cover1);
	this->addChild(cover2);
	this->addChild(cover3);

    //loading main menu scene in SPLASH_SCREEN_APPEAR_TIME seconds
    this->scheduleOnce(schedule_selector(SplashScreen::FinishSplashScreen), SPLASH_SCREEN_APPEAR_TIME);

    //skip button declaration
	auto menu_item_1 = MenuItemImage::create(SKIP_BUTTON, SKIP_BUTTON_PRESSED, CC_CALLBACK_1(SplashScreen::ToMainMenu, this));
	menu_item_1->setPosition(Point((visibleSize.width * 19) / 20, (visibleSize.height * 7) / 20));
	menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(Point((visibleSize.width) / 10, 0));
	this->addChild(menu);
	menu->setVisible(false);

	//single touch listener
	auto singleListener = EventListenerTouchOneByOne::create();
	singleListener->setSwallowTouches(true);
	singleListener->onTouchBegan = CC_CALLBACK_2(SplashScreen::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(singleListener, this);

    return true;
}

void SplashScreen::ToMainMenu(Ref *pSender)
{
	auto sceneMainMenu = MainMenuScreen::createScene();

	//transition to main menu
	Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_SCREEN_TRANSITION_LENGTH, sceneMainMenu));
}

void SplashScreen::FinishSplashScreen(float dt)
{
	this->removeChild(splashScreen, true);
	auto menuAction = MoveTo::create(COVER_APPEARANCE_SPEED,Point(0, 0));
	auto coverAction = MoveTo::create(COVER_APPEARANCE_SPEED,Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	cover1->setVisible(true);
	cover1->runAction(coverAction);
	menu->setVisible(true);
	menu->runAction(menuAction);
	visibleCover = 1;

}

bool SplashScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto coverAction = MoveTo::create(COVER_APPEARANCE_SPEED,Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	if (visibleCover == 1)
	{
		cover2->setVisible(true);
		cover2->runAction(coverAction);
	}
	if(visibleCover == 2)
	{
		cover3->setVisible(true);
		cover3->runAction(coverAction);
	}
	if(visibleCover == 3)
	{
		auto sceneMainMenu = MainMenuScreen::createScene();
		//transition to main menu
		Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_SCREEN_TRANSITION_LENGTH, sceneMainMenu));
	}
	visibleCover++;
	return true;
}


void SplashScreen::menuCloseCallback(Ref* pSender)
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
