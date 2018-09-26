#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {	
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	pEGLView->setDesignResolutionSize(640, 960, kResolutionFixedWidth);
    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);
	
	//Background Music
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgMusic.wav");
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.wav", true);
	if (isPaused)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}

	//Preload Sound Efects
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("enemyKill.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("fireRocket.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("gunshot.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("playerKill.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("pop.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->preloadEffect("rocketExplode.wav");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();


    // if you use SimpleAudioEngine, it must be pause
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	if (isPaused == false)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();


    // if you use SimpleAudioEngine, it must resume here
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	if (isPaused == false)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}	  

