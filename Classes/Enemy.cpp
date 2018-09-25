#include "Enemy.h"
#include "Projectile.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


Enemy* Enemy::createEnemy(GameplayLayer* _gameplayLayer)
{
	Enemy* ob = new Enemy();
	if (ob && ob->initEnemy(_gameplayLayer))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}


bool Enemy::initEnemy(GameplayLayer* _gameplayLayer)
{
	gameplayLayer = _gameplayLayer;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float mrand = rand() % 3 + 1;
	CCLOG("random height %f", mrand);
	float h = visibleSize.height * mrand * 0.25;
	this->initWithFile("bookGame_enemy.png");
	CCPoint p = ccp(visibleSize.width + this->getContentSize().width / 2,h);
	this->setPosition(p);
	this->schedule(schedule_selector(Enemy::shoot), 1.3);

	//enemy animation
	CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("enemy_anim.png");
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("enemy_anim.plist");
	this->createWithSpriteFrameName("enemy_idle_1.png");
	this->addChild(spritebatch);
	//idle animation
	CCArray* animFrames = CCArray::createWithCapacity(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str1, "enemy_idle_%d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str1);
		animFrames->addObject(frame);
	}
	CCAnimation* idleanimation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f);
	this->runAction(CCRepeatForever::create(CCAnimate::create(idleanimation)));

	return true;
}


void Enemy::update()
{
	CCPoint _mp = this->getPosition();
	CCPoint _Mp = ccpAdd(_mp, ccp(-3, 0));
	this->setPosition(_Mp);
}
void Enemy::shoot(float dt)
{
	//CCLog("[Enemy] shoot");
	CCPoint p = this->getPosition();
	p.x = p.x - this->getContentSize().width / 2;
	p.y = p.y - this->getContentSize().height * 0.05;
	Projectile* pr = Projectile::createProjectile(p, 1);
	gameplayLayer->addChild(pr);
	gameplayLayer->getEnemyBulletsArray()->addObject(pr);

	CocosDenshion::SimpleAudioEngine::sharedEngine() ->playEffect("gunshot.wav");
}