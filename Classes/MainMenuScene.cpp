#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "OptionsMenuScene.h"
#include <spine/spine-cocos2dx.h>
#include "SimpleAudioEngine.h"
CCScene* MainMenu::scene()
{
	CCScene *scene = CCScene::create();
	MainMenu *layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}
bool MainMenu::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);

	CCLabelBMFont *nameLabel = CCLabelBMFont::create("Ms.tinyBazooka", "PixelFont.fnt");
	nameLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
	this->addChild(nameLabel);

	//actions
	CCMoveTo* actionMove = CCMoveTo::create(1, CCPoint(nameLabel ->getPosition().x, nameLabel->getPosition().y + 20));
	CCCallFuncN* actionMoveDone = CCCallFuncN::create(nameLabel, callfuncN_selector(MainMenu::MoveUpFinished));
	CCEaseSineInOut *easeInOut = CCEaseSineInOut::create(actionMove);
	nameLabel->runAction(CCSequence::create(easeInOut, actionMoveDone, NULL));

	extension::CCSkeletonAnimation* skeletonNode = extension::CCSkeletonAnimation::createWithFile("player.json", "player.atlas", 1.0f);
	skeletonNode->addAnimation("runCycle", true, 0, 0);
	skeletonNode->setPosition(ccp(visibleSize.width * .125, visibleSize.height * 0.2 - skeletonNode ->getContentSize().height / 2));
	addChild(skeletonNode);

	CCMenuItemImage *pPlayItem = CCMenuItemImage::create("_bookgame_UI_play.png", "_bookgame_UI_play.png",this, menu_selector(MainMenu::playGame));
	pPlayItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height * 0.5));
	
	CCMenuItemImage *pOptionsItem =	CCMenuItemImage::create("_bookgame_UI_options.png",	"_bookgame_UI_options.png", this, menu_selector(MainMenu::optionsScene));
	pOptionsItem->setPosition(ccp(visibleSize.width * 0.75, visibleSize.height * 0.5));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pOptionsItem, pPlayItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);

	CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create("CURRENT HIGH SCORE", "PixelFont.fnt");
	newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.15));
	this->addChild(newHighScoreLabel, 10);
	newHighScoreLabel->setScale(0.5);

	CCLabelBMFont* highScoreLabel = CCLabelBMFont::create("0", "PixelFont.fnt");
	highScoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.065));
	this->addChild(highScoreLabel, 10);
	highScoreLabel->setScale(0.5);
	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bazookaGameHighScore");
	char scoreTxt[100];
	sprintf(scoreTxt, "%d", highScore);
	highScoreLabel->setString(scoreTxt);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this,menu_selector(MainMenu::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width * .25 - pCloseItem->getContentSize().width / 2,origin.y + visibleSize.height * 0.5));

	// create menu, it's an autorelease object
	CCMenu* pMenu2 = CCMenu::create(pCloseItem, NULL);
	pMenu2->setPosition(CCPointZero);
	this->addChild(pMenu2, 1);

	this->scheduleUpdate();

	return true;
}


void MainMenu::update(float dt)
{
	scrollingBgLayer->update();
}

void MainMenu::playGame(CCObject* pSender)
{
	CCScene *mScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
}

void MainMenu::optionsScene(CCObject* pSender)
{
	CCScene *mScene = OptionsMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
}

void MainMenu::MoveDownFinished(CCNode* sender)
{
	//CCLOG("move down fin");
	CCSprite *sprite = (CCSprite *)sender;
	CCMoveTo* actionMove = CCMoveTo::create(1.0, CCPoint(sprite ->getPosition().x, sprite->getPosition().y + 20.0));
	CCCallFuncN* actionMoveDone = CCCallFuncN::create(sprite, callfuncN_selector(MainMenu::MoveUpFinished));
	CCEaseSineInOut *easeInOut = CCEaseSineInOut::create(actionMove);
	sprite->runAction(CCSequence::create(easeInOut, actionMoveDone, NULL));
}

void MainMenu::MoveUpFinished(CCNode* sender)
{
	//CCLOG("move up fin");
	CCSprite *sprite = (CCSprite *)sender;
	CCMoveTo* actionMove = CCMoveTo::create(1.0, CCPoint(sprite->getPosition().x, sprite->getPosition().y - 20.0));
	CCCallFuncN* actionMoveDone = CCCallFuncN::create(sprite, callfuncN_selector(MainMenu::MoveDownFinished));
	CCEaseSineInOut *easeInOut = CCEaseSineInOut::create(actionMove);
	sprite->runAction(CCSequence::create(easeInOut, actionMoveDone, NULL));
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}