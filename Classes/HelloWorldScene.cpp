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
CCSprite* hero;
CCSize visibleSize;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {	
		
        return false;
    }
    this->scheduleUpdate();
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	CCSprite* bg = CCSprite::create("bg1.jpg");
	bg->setPosition(ccp(visibleSize.width * 0.5f,visibleSize.height * .5));
	this->addChild(bg,-1);

	hero = CCSprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(ccp(visibleSize.width * 0.4f,visibleSize.height * 0.4f));
	this->addChild(hero,5);
    return true;
}
void HelloWorld::update(float dt)
{
	CCPoint p = hero->getPosition();
	hero->setPosition(ccp(p.x + 5, p.y));
	if ((hero->getPositionX() - hero->getContentSize().width / 2) > visibleSize.width)
	{
		hero->setPosition(ccp(0.0 - hero->getContentSize().width / 2, hero ->getPositionY()));
	}
}