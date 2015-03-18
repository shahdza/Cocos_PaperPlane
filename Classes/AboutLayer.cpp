#include "AboutLayer.h"
#include "MenuScene.h"

USING_NS_CC;

bool AboutLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	// 获取屏幕大小
	WIN_SIZE = Director::getInstance()->getWinSize();
	ORIGIN = Director::getInstance()->getVisibleOrigin();

	this->setScale(0.0);
	this->setPosition(-WIN_SIZE.width, -WIN_SIZE.height);
	
	this->addUI();

    return true;
}


void AboutLayer::addUI()
{
	auto bg = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("AboutUI/AboutUI.json");
	this->addChild(bg);

	// back button
	auto btnBack = (Button*)Helper::seekWidgetByName(bg, "BtnBack");
	btnBack->addTouchEventListener(CC_CALLBACK_2(AboutLayer::turnToMenuScene, this));
}


void AboutLayer::showAction()
{
	auto moveTo = MoveTo::create(0.3f, Vec2(0, 0));
	auto scaleTo = ScaleTo::create(0.3f, 1.0f);
	this->runAction(moveTo);
	this->runAction(scaleTo);
}


void AboutLayer::hideAction()
{
	auto moveTo = MoveTo::create(0.3f, Vec2(-WIN_SIZE.width, -WIN_SIZE.height));
	auto scaleTo = ScaleTo::create(0.3f, 0.0f);
	this->runAction(moveTo);
	this->runAction(scaleTo);
}


// 返回菜单界面
void AboutLayer::turnToMenuScene(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		((MenuScene*)this->getParent())->hideAbout();
	}
}

