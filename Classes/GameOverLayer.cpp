#include "GameOverLayer.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;


bool GameOverLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(162, 162, 162, 162))) 
	{
		return false;
	}

	WIN_SIZE = Director::getInstance()->getWinSize();
	ORIGIN = Director::getInstance()->getVisibleOrigin();

	this->setScale(0.0f);
	this->setPosition(-WIN_SIZE.width, -WIN_SIZE.height);

	this->getData();
	this->addUI();

	this->showAction();
	this->scheduleUpdate();

    return true;
}


// 获取分数数据
void GameOverLayer::getData()
{
	this->record = UserDefault::getInstance()->getIntegerForKey("Record", 0);
	this->score = UserDefault::getInstance()->getIntegerForKey("Score", 0);
	this->addScore = 0;

	if (this->score > this->record)
	{
		UserDefault::getInstance()->setDoubleForKey("Record", this->score);
		UserDefault::getInstance()->flush();
	}
}


// 加载UI
void GameOverLayer::addUI()
{
	this->bg = (Layout*)cocostudio::GUIReader::getInstance()->widgetFromJsonFile("GameOverUI/GameOverUI.json");
	this->addChild(this->bg);

	// again button
	auto btnAgain = (Button*)Helper::seekWidgetByName(bg, "BtnAgain");
	btnAgain->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::turnToGameScene, this));

	// back button
	auto btnBack = (Button*)Helper::seekWidgetByName(bg, "BtnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::turnToMenuScene, this));

	// 新分数
	this->text =(TextBMFont*) ui::Helper::seekWidgetByName(this->bg, "Score");
	char str[50];
	sprintf(str, "%d", this->score);
	this->text->setString(str);

	// 历史记录
	auto rd = (TextBMFont*)ui::Helper::seekWidgetByName(this->bg, "Record");
	char s[50];
	sprintf(s, "%d", this->record);
	rd->setString(s);

	// New Logo --> New
	this->image = (ImageView*)ui::Helper::seekWidgetByName(this->bg, "New");
	this->image->setVisible(false);
	this->image->setScale(0.0);
}


void GameOverLayer::showAction()
{
	auto moveTo = MoveTo::create(0.3f, Vec2(0, 0));
	auto scaleTo = ScaleTo::create(0.3f, 1.0f);
	this->runAction(moveTo);
	this->runAction(scaleTo);
}


// 分数动态效果
void GameOverLayer::update(float dt)
{
	char s[50];
	double delta = this->score * dt;
	if (this->addScore + delta >= this->score)
	{
		sprintf(s, "%d", this->score);
		this->text->setString(s);

		this->unscheduleUpdate();
		this->showNewLogo();
	}
	else 
	{
		this->addScore += delta;
		sprintf(s, "%d", (int)this->addScore);
		this->text->setString(s);
	}
}


// 显示是否为新记录
void GameOverLayer::showNewLogo()
{
	if (this->score > this->record)
	{
		this->image->setVisible(true);
		auto *scaleBig = ScaleTo::create(0.4f, 1.0f);
		auto *delay = DelayTime::create(0.1f);
		auto *scaleSmall = ScaleTo::create(0.2f, 0.7f);
		auto *seq = Sequence::create(scaleBig, delay, scaleSmall, NULL);
		this->image->runAction(seq);
	}
}


// 再玩一次
void GameOverLayer::turnToGameScene(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}


// 返回菜单界面
void GameOverLayer::turnToMenuScene(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = MenuScene::createScene();
		auto tt = TransitionFade::create(1.0, scene);
		Director::getInstance()->replaceScene(tt);
	}
}

