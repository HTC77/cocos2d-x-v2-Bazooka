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
	hero->setPosition(ccp(visibleSize.width * 0.2f,visibleSize.height * 0.4f));
	this->addChild(hero,5);
	

	gameplayLayer = new GameplayLayer(hero);
	this->addChild(gameplayLayer,6);
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	this->setTouchEnabled(true);

	leftButton = CCRectMake(0, 0, visibleSize.width / 2, visibleSize.height);
	rightButton = CCRectMake(visibleSize.width / 2, 0, visibleSize.width / 2, visibleSize.height);

	gravity = ccp(0, -5);
	jumping = false;
	jumpTimer = 0;

	scoreLabel = CCLabelBMFont::create("Score: 0", "PixelFont.fnt");
	scoreLabel->setPosition(ccp(visibleSize.width * 0.870, visibleSize.height * 0.9));
	this->addChild(scoreLabel, 10);
	scoreLabel->setScale(0.5);
    return true;
}
void HelloWorld::update(float dt)
{
	if (!gameplayLayer->gameOver)
	{
		gameplayLayer->update();

		if (jumping)
		{
			jumpTimer = 10;
			jumping = false;
		}
		if (jumpTimer > 0)
		{
			jumpTimer--;
			CCPoint p = hero->getPosition();
			CCPoint mP = ccpAdd(p, ccp(0, 7));
			hero->setPosition(mP);
		}
		else
		{
			jumpTimer = 0;
			CCPoint p = hero->getPosition();
			CCPoint pM = ccpAdd(p, gravity);
			hero->setPosition(pM);
		}

		float maxY = visibleSize.height - hero->getContentSize().height / 2;
		float minY = hero->getContentSize().height / 2;
		float newY = hero->getPosition().y;
		newY = MIN(MAX(newY, minY), maxY);
		hero->setPosition(ccp(hero->getPosition().x, newY));

		char scoreTxt[100];
		sprintf(scoreTxt, "Score: %d", gameplayLayer->score);
		scoreLabel->setString(scoreTxt);
	}
	else
	{
		gameOver();
	}
}
void HelloWorld::spawnEnemy(float dt)
{
	CCLog("spawn enemy");
	Enemy* e = Enemy::createEnemy(gameplayLayer);
	gameplayLayer->addChild(e);
	e->shoot(0.016f);
	gameplayLayer->getEnemiesArray()->addObject(e);
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchBegan");
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	if (!gameplayLayer->gameOver)
	{
		if (rightButton.containsPoint(location))
			fireRocket();

		if (leftButton.containsPoint(location))
			jumping = true;
	}
}
void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchMoved");
}
void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	CCLog("TouchEnded");
}


void HelloWorld::fireRocket()
{
	CCPoint p = hero->getPosition();
	p.x = p.x + hero->getContentSize().width / 2;
	p.y = p.y - hero->getContentSize().height * 0.05;
	Projectile* rocket = Projectile::createProjectile(p, 2);
	gameplayLayer->addChild(rocket);
	gameplayLayer->getPlayerBulletsArray()->addObject(rocket);
}

void HelloWorld::gameOver()
{
	this->unscheduleAllSelectors();
	if (gameplayLayer->getEnemiesArray()->count() >0)
	{
		for (int i = 0; i< gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->getEnemiesArray() ->objectAtIndex(i);
			en->unscheduleAllSelectors();
		}
	}

	CCLabelBMFont* gameOverLabel = CCLabelBMFont::create("GAMEOVER","PixelFont.fnt");
	gameOverLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.6));
	this->addChild(gameOverLabel, 10);
}