#include "Enemy.h"
USING_NS_CC;

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


Enemy* Enemy::createEnemy()
{
	Enemy* ob = new Enemy();
	if (ob && ob->initEnemy())
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}


bool Enemy::initEnemy()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float mrand = rand() % 3 + 1;
	CCLOG("random height %f", mrand);
	float h = visibleSize.height * mrand * 0.25;
	this->initWithFile("bookGame_enemy.png");
	CCPoint p = ccp(visibleSize.width - this->getContentSize().width / 2,h);
	this->setPosition(p);
	return true;
}


void Enemy::update()
{
	CCPoint _mp = this->getPosition();
	CCPoint _Mp = ccpAdd(_mp, ccp(-3, 0));
	this->setPosition(_Mp);
}