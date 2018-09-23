#ifndef __bazooka__ParticleSpin__
#define __bazooka__ParticleSpin__
class ProjectileObject;
#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class ParticleSpin : public CCSprite
{
	ParticleSpin();
	~ParticleSpin();
	CCPoint speed;
	CCPoint gravity;
	float spinCounter;
public:
	bool init();
	static ParticleSpin* create(CCPoint _cp, char *fileName);
	void update(float dt);
};
#endif /* defined(__sdpdd__ProjectileSpin__) */