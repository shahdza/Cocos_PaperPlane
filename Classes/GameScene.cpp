#include "GameScene.h"
#include "GameOverLayer.h"
#include "MenuScene.h"

USING_NS_CC;

// 速度
Vec2 speed[] = {
	Vec2(10, 3),
	Vec2(10 * sqrt(3.0f) / 2.0f, 5),
	Vec2(10 * 0.5f, 8),
	Vec2(0, 12),
	Vec2(-10 * 0.5f, 8),
	Vec2(-10 * sqrt(3.0f) / 2.0f, 5),
	Vec2(-10, 3)
};


Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	scene->addChild(layer);
	
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	
	return scene;
}


bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	// 获取屏幕大小
	WIN_SIZE = Director::getInstance()->getWinSize();
	ORIGIN = Director::getInstance()->getVisibleOrigin();

	this->resetMusic();
	this->addUI();
	this->addEdge();
	this->addPlayer();
	this->addTouchEvent();
	this->addContactEvent();

	this->fps = 0;
	this->ang = 0;
	this->score = 0.0f;
	this->isTouched = false;
	this->isOver = false;
	this->firstTouch = true;

    return true;
}


// 添加音乐
void GameScene::resetMusic()
{

}


// 添加界面元素
void GameScene::addUI()
{
	bg1 = Sprite::create("bgGame.png");
	bg2 = Sprite::create("bgGame.png");
	bgSize = bg1->getContentSize();
	bg1->setAnchorPoint(Vec2(0, 0));
	bg2->setAnchorPoint(Vec2(0, 0));
	bg1->setPosition(0, 0);
	bg2->setPosition(0, -bgSize.height);
	this->addChild(bg1);
	this->addChild(bg2);

	// 显示分数
	lbScore = Label::createWithBMFont("fonts/futura-48.fnt", "0", TextHAlignment::RIGHT);
	lbScore->setAnchorPoint(Vec2(1.0, 1.0));
	lbScore->setPosition(WIN_SIZE.width - 50,
		WIN_SIZE.height - 50);
	this->addChild(lbScore, 100);

	this->addEnemy(bg2);

	// ready ui
	readyUI = (Layout*)cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ReadyUI/ReadyUI.json");
	this->addChild(readyUI, 100, "readyUI");
}


// 添加边界
void GameScene::addEdge()
{
	wallLeft = Sprite::create("WallLeft.png");
	wallRight = Sprite::create("WallRight.png");
	wallLeft->setAnchorPoint(Vec2(0, 0.5));
	wallRight->setAnchorPoint(Vec2(1.0, 0.5));
	wallLeft->setPosition(0, WIN_SIZE.height / 2);
	wallRight->setPosition(WIN_SIZE.width, WIN_SIZE.height / 2);
	this->addChild(wallLeft, 10);
	this->addChild(wallRight, 10);

	this->edge = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(WIN_SIZE, PhysicsMaterial(100.0, 1.0, 0.0), 20.0f);
	this->edge->setPhysicsBody(body);
	this->edge->setPosition(WIN_SIZE / 2);
	this->addChild(this->edge);

	this->edge->getPhysicsBody()->setCategoryBitmask(4);
	this->edge->getPhysicsBody()->setCollisionBitmask(1);
	this->edge->getPhysicsBody()->setContactTestBitmask(1);
}


// 添加玩家
void GameScene::addPlayer()
{
	this->player = Sprite::create("feiji.png");

	Vec2 points[3] =
	{
		Vec2(-this->player->getContentSize().width / 2, -this->player->getContentSize().height / 2),
		Vec2(-this->player->getContentSize().width / 2, this->player->getContentSize().height / 2),
		Vec2(this->player->getContentSize().width / 2, 0)
	};

	auto body = PhysicsBody::createPolygon(points, 3, PhysicsMaterial(1.0, 0, 0));
	this->player->setPhysicsBody(body);
	this->player->setPosition(WIN_SIZE / 2);
	this->addChild(this->player);

	this->player->getPhysicsBody()->setCategoryBitmask(1);
	this->player->getPhysicsBody()->setCollisionBitmask(6);
	this->player->getPhysicsBody()->setContactTestBitmask(6);
}


// 添加敌人
void GameScene::addEnemy(Sprite* bg)
{
	srand(time(NULL));

	bg->removeAllChildren();

	for (int i = 0; i < 4; i++)
	{
		auto rect = Sprite::create("Rect.png");
		auto rect_body = PhysicsBody::createBox(rect->getContentSize(), PhysicsMaterial(100.0, 0.0, 0.0));
		rect->setPhysicsBody(rect_body);

		// 随机位置
		float x = (rand() % (int)(bgSize.width + 100)) + 0.0f;
		float y = i*(bgSize.height / 4) + rect->getContentSize().height;
		rect->setPosition(x, y);

		rect->getPhysicsBody()->setCategoryBitmask(2);
		rect->getPhysicsBody()->setCollisionBitmask(1);
		rect->getPhysicsBody()->setContactTestBitmask(1);

		bg->addChild(rect);
	}
}


// 添加触摸事件
void GameScene::addTouchEvent()
{
	auto dispatcher = this->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


// 添加碰撞检测
void GameScene::addContactEvent()
{
	auto dispatcher = this->getEventDispatcher();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


// 开始触摸，游戏开始
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (firstTouch == true)
	{
		firstTouch = false;
		this->scheduleUpdate();
		readyUI->removeFromParentAndCleanup(true);
	}
	else 
	{
		this->isTouched = true;
		this->touchPos = touch->getLocation();
	}
	return true;
}


// 触摸移动
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	this->touchPos = touch->getLocation();
}


// 触摸结束
void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	this->isTouched = false;
}


// 碰撞检测
bool GameScene::onContactBegin(PhysicsContact& contact)
{
	if (this->isOver == false)
	{
		this->isOver = true;
		this->showGameOverLayer();
	}
	return true;
}


// 定时器刷新
void GameScene::update(float dt)
{
	fps = (fps + 1) % 3;

	// 纸飞机变换角度
	if (fps == 0)
	{
		if (this->isTouched == true)
		{
			if (this->touchPos.x < WIN_SIZE.width / 2)
			{
				this->ang++;
				if (ang >= 6)	ang = 6;
				this->player->setRotation(ang*30.0f);
			}
			else
			{
				this->ang--;
				if (ang <= 0) ang = 0;
				this->player->setRotation(ang*30.0f);
			}
		}
	}

	// 纸飞机移动
	this->player->setPositionX(this->player->getPositionX() + speed[this->ang].x * 0.5);

	// 计算分数
	this->score += (speed[this->ang].y) / 10.0;
	char str[50];
	sprintf(str, "%d", (int)this->score);
	this->lbScore->setString(str);

	// 背景移动
	bg1->setPositionY(bg1->getPositionY() + speed[this->ang].y);
	if (bg1->getPositionY() >= WIN_SIZE.height)
	{
		Sprite* bg = bg1;
		bg1 = bg2;
		bg2 = bg;

		this->addEnemy(bg2);
	}
	bg2->setPositionY(bg1->getPositionY() - bgSize.height);
}


// 游戏结束
void GameScene::showGameOverLayer()
{
	this->unscheduleUpdate();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();

	UserDefault::getInstance()->setIntegerForKey("Score", (int)this->score);

	auto gameOverLayer = GameOverLayer::create();
	this->addChild(gameOverLayer, 999, 999);
}

