#include "GameplayLayer.h"
#include "Enemy.h"
GameplayLayer::GameplayLayer()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	enemies = new CCArray();
	enemiesToBeDeleted = new CCArray();
}
GameplayLayer::~GameplayLayer(){}
void GameplayLayer::update()
{
	if (enemies->count() >= 0)
	{
		for (int i = 0; i <enemies->count(); i++)
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
}
CCArray* GameplayLayer::getEnemiesArray()
{
	return enemies;
}