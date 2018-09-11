#ifndef __bazooka__Enemy
#define __bazooka__Enemy

#include "cocos2d.h"
using namespace cocos2d;

class Enemy : public CCSprite
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* createEnemy();
	bool initEnemy();
	void update();
};
#endif
