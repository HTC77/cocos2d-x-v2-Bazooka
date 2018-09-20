#ifndef __bazooka__HUDLayer__
#define __bazooka__HUDLayer__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HUDLayer : public CCLayer
{
public:
	HUDLayer(void);
	~HUDLayer(void);
	CCSize visibleSize;
	CCLabelBMFont* scoreLabel;
	void updateScore(int score);

	CCMenu* pauseMenu;
	CCMenu* resumeMenu;

	void pauseGame(CCObject* pSender);
	void resumeGame(CCObject* pSender);
};
#endif