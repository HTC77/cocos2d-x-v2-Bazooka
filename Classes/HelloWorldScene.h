#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "GameplayLayer.h"
#include "Enemy.h"
#include "HUDLayer.h"
#include "ScrollingBgLayer.h"
#include <spine/spine-cocos2dx.h>
class HelloWorld : public cocos2d::CCLayer
{
public:
	CCSprite* hero;
	CCSize visibleSize;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);
	
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	GameplayLayer* gameplayLayer;
	void spawnEnemy(float dt);

	void fireRocket();
	CCRect leftButton, rightButton;

	CCPoint gravity;

	int jumpTimer;
	bool jumping;

	void gameOver();

	HUDLayer* hudLayer;

	void gamePaused();
	void gameResumed();

	ScrollingBgLayer* scrollingBgLayer;

	typedef enum ActionState
	{
		kActionStateNone = 0,
		kActionStateIdle,
		kActionStateBoost
	};
	typedef enum PlayerState
	{
		kPlayerStateNone = 0,
		kPLayerStateIdle,
		kPlayerStateBoost
	};

	ActionState mActionState;
	PlayerState mPlayerState;
	CCAction* mIdleAction;
	CCAction* mBoostAction;

	void idleAnim();
	void boostAnim();
	void AnimationStates();

	extension::CCSkeletonAnimation* skeletonNode;
};

#endif // __HELLOWORLD_SCENE_H__
