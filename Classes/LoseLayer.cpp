#include"LoseLayer.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* LoseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = LoseLayer::create();
	scene->addChild(layer);
	return scene;
}
bool LoseLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* sprite = Sprite::create("UI/lose.png");
	sprite->setScale(0.5f);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	return true;
}