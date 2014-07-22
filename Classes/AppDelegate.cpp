#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto fileUtils = FileUtils::getInstance();
        auto screenSize = glview->getFrameSize();
        std::vector<std::string> resDirOrders;

        CCLog("Visible size = height:%f; width:%f", screenSize.height, screenSize.width);

        //check which asset device requires

        if (1920 == screenSize.width || 1920 == screenSize.height)
        {
        	resDirOrders.push_back("Images/1080");

        	glview->setDesignResolutionSize(1080,1920,ResolutionPolicy::NO_BORDER);
        }
        else if (1280 == screenSize.width || 1280 == screenSize.height)
        	    {
        			resDirOrders.push_back("Images/720");

        	    	glview->setDesignResolutionSize(800,1280,ResolutionPolicy::NO_BORDER);
        	    }
        else if (960 == screenSize.width || 960 == screenSize.height)
        {
        	resDirOrders.push_back("Images/960");

        	glview->setDesignResolutionSize(540,960,ResolutionPolicy::NO_BORDER);
        }
        else if (800 == screenSize.width || 800 == screenSize.height)
                {
                	resDirOrders.push_back("Images/800");

                	glview->setDesignResolutionSize(480,800,ResolutionPolicy::NO_BORDER);
                }
        else
        {
        	resDirOrders.push_back("Images/800");

    		glview->setDesignResolutionSize(320,480,ResolutionPolicy::NO_BORDER);
        }

        fileUtils->setSearchPaths(resDirOrders);


    // create a scene. it's an autorelease object
    auto scene = SplashScreen::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
