#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
class GameOverLayer : public cocos2d::LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameOverLayer);

	void getData();
	void addUI();
	void update(float dt);
	void showNewLogo();

	void showAction();
	void turnToGameScene(Ref* sender, Widget::TouchEventType type);
	void turnToMenuScene(Ref* sender, Widget::TouchEventType type);

private:
	Layout* bg;
	TextBMFont* text;
	ImageView* image;
	double t;

	int record;
	int score;
	double addScore;

	Size WIN_SIZE;
	Vec2 ORIGIN;
};

#endif // __GameOverLayer_H__
