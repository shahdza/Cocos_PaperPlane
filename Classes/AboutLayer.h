#ifndef __AboutLayer_H__
#define __AboutLayer_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;

class AboutLayer : public cocos2d::Layer
{
public:
    virtual bool init();  
	CREATE_FUNC(AboutLayer);

	void addUI();
	void showAction();
	void hideAction();
	void turnToMenuScene(Ref* sender, Widget::TouchEventType type);

private:
	Size WIN_SIZE;
	Vec2 ORIGIN;
};

#endif // __AboutLayer_H__
