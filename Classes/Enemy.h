#ifndef __bazooka__Enemy__
#define __bazooka__Enemy__

#pragma once

#include "cocos2d.h"
#include "GameplayLayer.h"
#include "Projectile.h"
using namespace cocos2d;

class Enemy : public CCSprite
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* createEnemy(GameplayLayer* _gameplayLayer);
	bool initEnemy(GameplayLayer* _gameplayLayer);
	void update();
	void shoot(float dt);
	GameplayLayer* gameplayLayer;
};
#endif
