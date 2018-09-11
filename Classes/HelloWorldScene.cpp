#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{	
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {	
		
        return false;
    }
	
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	CCSprite* bg = CCSprite::create("bg1.jpg");
	bg->setPosition(ccp(visibleSize.width * 0.5f,visibleSize.height * .5));
	this->addChild(bg,-1);

	hero = CCSprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(ccp(visibleSize.width * 0.4f,visibleSize.height * 0.4f));
	this->addChild(hero,5);
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png", this, menu_selector(HelloWorld::buttonControl));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPoint(25,50));
	this->addChild(pMenu, 1);

	gameplayLayer = new GameplayLayer();
	this->addChild(gameplayLayer,6);
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	this->setTouchEnabled(true);
    return true;
}
void HelloWorld::update(float dt)
{
	gameplayLayer->update();
}
void HelloWorld::spawnEnemy(float dt)
{
	CCLog("spawn enemy");
	Enemy* e = Enemy::createEnemy();
	gameplayLayer->addChild(e);
	gameplayLayer->getEnemiesArray()->addObject(e);
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchBegan");
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCLog("location: xpos:%f , ypos:%f", location.x, location.y);
	CCMoveTo * actionMove = CCMoveTo::create(1, location);
	CCEaseSineInOut *easeInOut = CCEaseSineInOut::create(actionMove);
	hero->runAction(easeInOut);
}
void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchMoved");
}
void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchEnded");
}
void HelloWorld::buttonControl(CCObject* pSender)
{
	CCSprite* test = CCSprite::create("CloseNormal.png ");
	test->setPosition(ccp(hero->getPosition().x + hero ->getContentSize().width / 2, hero->getPosition().y));
	test->setScale(0.5);
	this->addChild(test);
}

