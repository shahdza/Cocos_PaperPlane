#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class GameScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    virtual bool init();  
    void menuCloseCallback(Ref* pSender);
	CREATE_FUNC(GameScene);

	void resetMusic();
	void addUI();
	void addEdge();
	void addPlayer();
	void addEnemy(Sprite* bg);
	void addContactEvent();
	void addTouchEvent();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	bool onContactBegin(PhysicsContact& contact);

	void update(float dt);

	void showGameOverLayer();

private:
	Size WIN_SIZE;
	Vec2 ORIGIN;

	// ready UI
	Layout* readyUI;
	Layer* layer;

	// 边界
	Sprite* edge;
	Sprite* wallLeft;
	Sprite* wallRight;
	Sprite* bg1;
	Sprite* bg2;
	Size bgSize;
	
	Sprite* player;			// 玩家
	Vector<Sprite*> enemy;	// 敌人

	bool firstTouch;		// 是否开始游戏
	bool isOver;			// 游戏是否结束

	int fps;
	int ang;				// 飞机角度
	Vec2 touchPos;			// 触摸点
	bool isTouched;			// 是否触摸

	// 记录分数
	double score;
	Label* lbScore;


};

#endif // __GameScene_H__
