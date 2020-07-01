
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
	initScrollView();

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
	totalCoin += coinPerSec;

	auto txt = (Label*)this->getChildByTag(coinTxtTag);
	char total[(((sizeof totalCoin)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(total, "%d", totalCoin);
	txt->setString(StringUtils::format(total));
	

	
	char p[(((sizeof coinPerSec)*CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(p, "%d", coinPerSec);



	auto floatingTxt = Label::createWithTTF(p, "fonts/DungGeunMo.ttf", 15);
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


	auto txt = (Label*)this->getChildByTag(coinTxtTag);
	char ntoc[(((sizeof totalCoin) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(ntoc, "%d", totalCoin);
	txt->setString(StringUtils::format(ntoc));

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
	coinTxt->setPosition(Point(70, 770));
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
bool GameScene::initScrollView()
{

	auto button = Sprite::create("charactor/rabbit/rabbit_4.png");
	button->setPosition(Point(50, 100));



	//auto scroll = ScrollView::create();
	//scroll->retain();
	//scroll->setAnchorPoint(Point(0, 0));
	//scroll->setPosition(Point(0, 0));
	//scroll->setViewSize(Size(480, 300));
	//scroll->setContainer(layer);
	//scroll->setDirection(ScrollView::Direction::HORIZONTAL);
	//scroll->setBounceable(false);
	//scroll->setContentSize(layer->getContentSize());
	//scroll->setContentOffset(Point::ZERO, false);
	//scroll->setDelegate(this);
	//this->addChild(scroll);



	auto layer = LayerColor::create(Color4B::WHITE);

	layer->setAnchorPoint(Point(0, 0));
	layer->setPosition(Point(0, 0));
	layer->setContentSize(Size(480, 600));

	layer->addChild(button);



	auto scrollView = ScrollView::create(Size(480, 300), layer);

	scrollView->retain();
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setBounceable(false);
	scrollView->setContentSize(layer->getContentSize());
	scrollView->setContentOffset(Point::ZERO, false);
	scrollView->setPosition(Point(0, 0));
	scrollView->setDelegate(this);



	this->addChild(scrollView);
	return true;
}
void GameScene::removeFloating()
{
	this->removeChildByTag(floatingTxtTag);
}

void GameScene::scrollViewDidScroll(ScrollView * v)
{
	CCLOG("Scrolling");
}



