#include "SecondScene.h"
#include "cocos2d.h"
#include "ModeScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* SecondScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}
bool SecondScene::init()
{
	Sprite* sprite = Sprite::create("UI/entrance3.jpg");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto spriteSize = sprite->getContentSize();
	sprite->setScaleX(visibleSize.height * 1.0 / spriteSize.height);
	sprite->setScaleY(visibleSize.width * 1.0 / spriteSize.width);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(sprite, 0);
	auto modeChoice = LabelTTF::create("Mode", "arial", 30);
	modeChoice->setColor(Color3B(0, 0, 0));
	auto choiceItem = MenuItemLabel::create(modeChoice, CC_CALLBACK_1(SecondScene::menuModeChoice, this));
	auto exit = LabelTTF::create("Exit", "arial", 30);
	exit->setColor(Color3B(0, 0, 0));
	auto exitItem = MenuItemLabel::create(exit, CC_CALLBACK_1(SecondScene::menuCloseCallback, this));
	auto menu1 = Menu::create(choiceItem, NULL);
	menu1->setPosition(origin.x + visibleSize.width / 2, origin.y + 4 * visibleSize.height / 5);
	auto menu2 = Menu::create(exitItem, NULL);
	menu2->setPosition(origin.x + 6 * visibleSize.width / 7, origin.y + visibleSize.height / 7);
	this->addChild(menu2, 1);
	this->addChild(menu1, 1);
	return true;
}
void SecondScene::menuModeChoice(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/click.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, ModeScene::createScene()));
}

void SecondScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/click.mp3");
	Director::getInstance()->end();
}