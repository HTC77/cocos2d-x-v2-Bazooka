#ifndef __bazooka__GameplayLayer__
#define __bazooka__GameplayLayer__
#include "cocos2d.h"
using namespace cocos2d;
class GameplayLayer : public CCLayer
{
public:
	GameplayLayer();
	~GameplayLayer();
	void update();
	
	CCSize visibleSize;
	CCArray* enemies;
	CCArray* getEnemiesArray();
	CCArray* enemiesToBeDeleted;

	CCArray* enemyBullets;
	CCArray* enemyBulletsToBeDeleted;

	CCArray* getEnemyBulletsArray();

	CCArray* playerBullets;
	CCArray* getPlayerBulletsArray();
};
#endif /* defined(__bazooka__GameplayLayer__) */