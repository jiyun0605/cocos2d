#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")


#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__



#include<string>
#include "cocos2d.h"
#include"cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;



class GameScene : public cocos2d::Scene,public ScrollViewDelegate
{

public:

	static const int coinTxtTag = 0;
	static const int floatingTxtTag = 1;
	static const int rabbitTextTag = 2;
	static const int rabbitButtonTag = 3;
	static const int menuTag1 = 4;
	static const int catTextTag = 5;
	static const int catButtonTag = 6;
	static const int menuTag2 = 7;



	int totalCoin = 0;
	int coinPerSec = 1;
	int touchCoin = 1;
	int rabbitLevel = 1;
	int catLevel = 0;


    static cocos2d::Scene* createScene();

    virtual bool init();
    
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	void addCoin(float data);
	void initUi();
	bool initButtonMenu();
	void removeFloating();

	void rabbitLevelUp();
	void catLevelUp();
	void totalCoinUpdate();
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
#endif