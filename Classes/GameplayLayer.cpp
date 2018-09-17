#include "GameplayLayer.h"
#include "Enemy.h"
GameplayLayer::GameplayLayer()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	enemies = new CCArray();
	enemiesToBeDeleted = new CCArray();
	
	enemyBullets = new CCArray();
	enemyBulletsToBeDeleted = new CCArray();
	playerBullets = new CCArray();
}
GameplayLayer::~GameplayLayer(){}
void GameplayLayer::update()
{
	if (enemies->count() >= 0)
	{
		for (int i = 0; i < enemies->count(); i++)
		{
			Enemy* e = (Enemy*)enemies->objectAtIndex(i);
			e->update();
			if (e->getPositionX() + e->getContentSize().width / 2 < 0)
			{
				enemiesToBeDeleted->addObject(e);
			}
		}
	}
	CCObject* ee = NULL;
	CCARRAY_FOREACH(enemiesToBeDeleted, ee)
	{
		Enemy *target = (Enemy*)(ee);
		enemies->removeObject(target);
		enemiesToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}

	//enemy bullets
	if (enemyBullets->count()> 0)
	{
		for (int i = 0; i < enemyBullets->count(); i++)
		{
			Projectile* pr = (Projectile*) enemyBullets->objectAtIndex(i);
			pr->update();
			if (pr->getPositionX() <= 0)
			{
				enemyBulletsToBeDeleted->addObject(pr);
			}
		}
	}
	CCObject* eb = NULL;
	CCARRAY_FOREACH(enemyBulletsToBeDeleted, eb)
	{
		Projectile* target = (Projectile*)(eb);
		enemyBullets->removeObject(target);
		enemyBulletsToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}

	//player bullets
	if (playerBullets->count() >= 0)
	{
		for (int i = 0; i<playerBullets->count(); i++)
		{
			Projectile* p = (Projectile*)playerBullets->objectAtIndex(i);
			p->update();
			if (p->getPositionX() >= visibleSize.width)
			{
				this->removeChild(p);
				playerBullets->removeObject(p);
			}
		}
	}
}
CCArray* GameplayLayer::getEnemiesArray()
{
	return enemies;
}

CCArray* GameplayLayer::getEnemyBulletsArray()
{
	return enemyBullets;
}

CCArray* GameplayLayer::getPlayerBulletsArray()
{
	return playerBullets;
}