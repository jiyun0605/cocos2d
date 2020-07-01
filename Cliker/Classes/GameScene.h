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
	static const int rabbitTag = 2;


	int totalCoin = 0;
	int coinPerSec = 1;
	int touchCoin = 1;




    static cocos2d::Scene* createScene();

    virtual bool init();
    
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	void addCoin(float data);
	void initUi();
	bool initScrollView();
	void removeFloating();
	void scrollViewDidScroll(ScrollView *v);
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
#endif