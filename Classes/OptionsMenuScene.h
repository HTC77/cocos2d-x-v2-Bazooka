#ifndef __bazooka__OPTIONSMENU_SCENE__
#define __bazooka__OPTIONSMENU_SCENE__
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
using namespace cocos2d;
class OptionsMenu : public cocos2d::CCLayer
{
public:
	virtual bool init();
	ScrollingBgLayer* scrollingBgLayer;
	static cocos2d::CCScene* scene();
	void update(float dt);
	void reset(CCObject* pSender);
	void mainMenu(CCObject* pSender);
	CREATE_FUNC(OptionsMenu);
	CCMenuItemImage* soundOnItem;
	CCMenuItemImage* soundOffItem;
	void SoundOnOff(CCObject* sender);
};
#endif