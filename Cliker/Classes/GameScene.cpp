
#include "GameScene.h"
#include "SimpleAudioEngine.h"


Scene* GameScene::createScene()
{
    return GameScene::create();
}


bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	initUi();
	initButtonMenu();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(schedule_selector(GameScene::addCoin), 1.0f);

    return true;
}


bool GameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	Vec2 loc = touch->getLocation();
	if (loc.y <= 300)
		return false;
	totalCoin += touchCoin;

	totalCoinUpdate();

	
	char p[(((sizeof touchCoin)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(p, "%d", touchCoin);

	auto floatingTxt = Label::createWithTTF(p, "fonts/DungGeunMo.ttf", 20);
	floatingTxt->setPosition(loc);
	floatingTxt->setColor(Color3B::GREEN);
	floatingTxt->setTag(floatingTxtTag);
	floatingTxt->enableOutline(Color4B::BLACK, 2);
	this->addChild(floatingTxt);

	int x = loc.x;
	auto action = Spawn::create(
		MoveTo::create(5, Vec2(x, 1000)),
		FadeOut::create(1),
		NULL
	);
	auto action2 = Sequence::create(
		action,
		DelayTime::create(2),
		CallFunc::create(CC_CALLBACK_0(GameScene::removeFloating, this)),
		NULL
	);

	floatingTxt->runAction(action);
	return true;
}

void GameScene::addCoin(float data)
{
	totalCoin += coinPerSec;

	totalCoinUpdate();

}
void GameScene::initUi()
{

	auto sky = Sprite::create("image/sky.png");
	sky->setPosition(Point(240, 400));
	sky->setScale(2);
	this->addChild(sky);
	auto ground = Sprite::create("image/ground.png");
	ground->setPosition(Point(240, 400));
	ground->setScale(2);
	this->addChild(ground);

	auto coinBar = Sprite::create("ui/coinBar.png");
	coinBar->setScale(1.5);
	coinBar->setAnchorPoint(Point(0,0.5));
	coinBar->setPosition(Point(10, 770));
	this->addChild(coinBar);

	char ntoc[(((sizeof totalCoin) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(ntoc, "%d", totalCoin);

	auto coinTxt = Label::createWithTTF(ntoc, "fonts/DungGeunMo.ttf", 20);
	coinTxt->setTag(coinTxtTag);
	coinTxt->setColor(Color3B::BLACK);
	coinTxt->setPosition(Point(150, 770));
	this->addChild(coinTxt);

	auto rabbit = Sprite::create("charactor/rabbit/rabbit_1.png");
	rabbit->setPosition(Point(60, 480));
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_1.png");
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_2.png");
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_3.png");
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_2.png");
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_3.png");
	animation->addSpriteFrameWithFile("charactor/rabbit/rabbit_4.png");
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	rabbit->runAction(rep);
	this->addChild(rabbit);
}
bool GameScene::initButtonMenu()
{

	auto button = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png",CC_CALLBACK_0(GameScene::rabbitLevelUp,this));
	button->setAnchorPoint(Point(0, 0));
	button->setPosition(Point(0,0));
	button->setTag(rabbitButtonTag);
	auto text1 = Label::createWithTTF("토끼 레벨업\n1레벨", "fonts/DungGeunMo.ttf", 15);
	text1->setPosition(Point(80, 50));
	text1->setColor(Color3B::BLACK);
	text1->setTag(rabbitTextTag);
	button->addChild(text1);

	//auto button2 = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png", CC_CALLBACK_0(GameScene::catLevelUp, this));
	//button2->setAnchorPoint(Point(0, 0));
	//button2->setPosition(Point(0, 0));
	//auto button3 = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png", CC_CALLBACK_0(GameScene::rabbitLevelUp, this));
	//button3->setAnchorPoint(Point(0, 0));
	//button3->setPosition(Point(0, 0));

	auto menu = Menu::create(button, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Point(50, 120));
	this->addChild(menu);
	menu->setTag(menuTag1);

	auto button4 = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png", CC_CALLBACK_0(GameScene::catLevelUp, this));
	button4->setAnchorPoint(Point(0, 0));
	button4->setPosition(Point(0, 0));
	button4->setTag(catButtonTag);
	auto text4=Label::createWithTTF("토끼 10레벨 이후\n잠금해제", "fonts/DungGeunMo.ttf", 15);
	text4->setPosition(Point(80, 50));
	text4->setColor(Color3B::BLACK);
	text4->setTag(catTextTag);
	button4->addChild(text4);


	//auto button5 = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png", CC_CALLBACK_0(GameScene::rabbitLevelUp, this));
	//button5->setAnchorPoint(Point(0, 0));
	//button5->setPosition(Point(0, 0));

	//auto button6 = MenuItemImage::create("ui/button.png", "ui/button2.png", "ui/button2.png", CC_CALLBACK_0(GameScene::rabbitLevelUp, this));
	//button6->setAnchorPoint(Point(0, 0));
	//button6->setPosition(Point(0, 0));


	auto menu2 = Menu::create(button4, NULL);
	menu2->alignItemsVertically();
	menu2->setPosition(Point(250,120));
	menu2->setTag(menuTag2);
	this->addChild(menu2);

	return true;
}
void GameScene::removeFloating()
{
	this->removeChildByTag(floatingTxtTag);
}

void GameScene::rabbitLevelUp()
{
	int cost =80*rabbitLevel;
	if (totalCoin < cost||rabbitLevel==30)
		return;
	totalCoin -= cost;
	rabbitLevel++;
	touchCoin = (rabbitLevel-1)*2;
	totalCoinUpdate();

	
	auto text = (Label*)this->getChildByTag(menuTag1)->getChildByTag(rabbitButtonTag)->getChildByTag(rabbitTextTag);
	string str;
	if (rabbitLevel >= 30)
		str = "\n레벨 최대치 달성!";
	else
		str="토끼 레벨업\n" + to_string(rabbitLevel) + "레벨";
	
	text->setString(str);



	char p[(((sizeof cost)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(p, "%d", cost);


	auto floatingTxt = Label::createWithTTF(p, "fonts/DungGeunMo.ttf", 20);
	floatingTxt->setPosition(Point(150,750));
	floatingTxt->setColor(Color3B::RED);
	floatingTxt->setTag(floatingTxtTag);
	floatingTxt->enableOutline(Color4B::BLACK, 2);
	this->addChild(floatingTxt);

	auto action = Spawn::create(
		MoveTo::create(5, Vec2(150, 1000)),
		FadeOut::create(1),
		NULL
	);
	auto action2 = Sequence::create(
		action,
		DelayTime::create(2),
		CallFunc::create(CC_CALLBACK_0(GameScene::removeFloating, this)),
		NULL
	);

	floatingTxt->runAction(action);
}

void GameScene::catLevelUp()
{
	int cost = (catLevel+1) * 100;
	if (totalCoin<cost||rabbitLevel<10||catLevel>=15)
		return;

	//create cat
	if (catLevel == 0)
	{
		auto cat = Sprite::create("charactor/cat/cat1.png");
		cat->setPosition(Point(180, 480));
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3f);
		animation->addSpriteFrameWithFile("charactor/cat/cat1.png");
		animation->addSpriteFrameWithFile("charactor/cat/cat2.png");
		animation->addSpriteFrameWithFile("charactor/cat/cat3.png");
		animation->addSpriteFrameWithFile("charactor/cat/cat2.png");
		auto animate = Animate::create(animation);
		auto rep = RepeatForever::create(animate);
		cat->runAction(rep);
		this->addChild(cat);
	}
	catLevel++;
	totalCoin -= cost;
	totalCoinUpdate();


	auto text = (Label*)this->getChildByTag(menuTag2)->getChildByTag(catButtonTag)->getChildByTag(catTextTag);
	string str;
	if (catLevel >= 15)
		 str = "\n레벨 최대치 달성!";
	else
		 str = "고양이 레벨업\n    " + to_string(catLevel) + "레벨";
	text->setString(str);

	char p[(((sizeof cost)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(p, "%d", cost);

	auto floatingTxt = Label::createWithTTF(p, "fonts/DungGeunMo.ttf", 20);
	floatingTxt->setPosition(Point(150, 750));
	floatingTxt->setColor(Color3B::RED);
	floatingTxt->setTag(floatingTxtTag);
	floatingTxt->enableOutline(Color4B::BLACK, 2);
	this->addChild(floatingTxt);

	auto action = Spawn::create(
		MoveTo::create(5, Vec2(150, 1000)),
		FadeOut::create(1),
		NULL
	);
	auto action2 = Sequence::create(
		action,
		DelayTime::create(2),
		CallFunc::create(CC_CALLBACK_0(GameScene::removeFloating, this)),
		NULL
	);

	floatingTxt->runAction(action);

	coinPerSec += catLevel-1;
}

void GameScene::totalCoinUpdate()
{
	auto txt = (Label*)this->getChildByTag(coinTxtTag);
	char total[(((sizeof totalCoin)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(total, "%d", totalCoin);
	txt->setString(StringUtils::format(total));
}




