#include "AppDelegate.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("PaperPlane");
		glview->setFrameSize(240, 400);
        director->setOpenGLView(glview);
    }
	
	glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::EXACT_FIT);

	director->setAnimationInterval(1.0 / 60.0);
    director->setDisplayStats(false);

	this->addResource();

    auto scene = MenuScene::createScene();
    director->runWithScene(scene);

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}


void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


void AppDelegate::addResource()
{
	FileUtils::getInstance()->addSearchPath("UI");
}

