#ifndef __MenuScene_H__
#define __MenuScene_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;

#include "AboutLayer.h"

class MenuScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    virtual bool init();  
	CREATE_FUNC(MenuScene);

	void addUI();
	void turnToGameScene(Ref* sender, Widget::TouchEventType type);
	void showAbout(Ref* sender, Widget::TouchEventType type);
	void hideAbout();
	void removeAbout();
	void quit(Ref* sender, Widget::TouchEventType type);

private:
	AboutLayer* aboutLayer;
	bool isAboutShow;
};

#endif // __MenuScene_H__
