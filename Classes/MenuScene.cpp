#include "MenuScene.h"
#include "GameScene.h"
#include "AboutLayer.h"

USING_NS_CC;


Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}


bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	this->addUI();
    
	this->isAboutShow = false;

    return true;
}


void MenuScene::addUI()
{
	// ±³¾°
	auto bg = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("MenuUI/MenuUI.json");
	this->addChild(bg);

	// play button
	auto btnPlay = (Button*)Helper::seekWidgetByName(bg, "BtnPlay");
	btnPlay->addTouchEventListener(CC_CALLBACK_2(MenuScene::turnToGameScene, this));

	// about button
	auto btnAbout = (Button*)Helper::seekWidgetByName(bg, "BtnAbout");
	btnAbout->addTouchEventListener(CC_CALLBACK_2(MenuScene::showAbout, this));

	// exit button
	auto btnQuit = (Button*)Helper::seekWidgetByName(bg, "BtnExit");
	btnQuit->addTouchEventListener(CC_CALLBACK_2(MenuScene::quit, this));


	// Ìí¼ÓAboutLayer
	aboutLayer = AboutLayer::create();
	this->addChild(aboutLayer, 999, 999);
}


void MenuScene::turnToGameScene(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = GameScene::createScene();
		auto tt = TransitionFade::create(1.0f, scene);
		Director::getInstance()->replaceScene(tt);
	}
}


void MenuScene::showAbout(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (isAboutShow == true) return;
		isAboutShow = true;
		aboutLayer->showAction();
	}
}


void MenuScene::hideAbout()
{
	aboutLayer->hideAction();
	isAboutShow = false;
}


void MenuScene::quit(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->end();
		exit(0);
	}
}

