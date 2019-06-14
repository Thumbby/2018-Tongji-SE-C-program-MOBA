#include"WinLayer.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* WinLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = WinLayer::create();
	scene->addChild(layer);
	return scene;
}
bool WinLayer::init()
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* sprite = Sprite::create("win.png");
	sprite->setScale(0.5f);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	return true;
}