#include "ModeScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
Scene* ModeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ModeScene::create();
	scene->addChild(layer);
	return scene;
}
bool ModeScene::init()
{
	auto sprite = Sprite::create("entrance4.jpg");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto spriteSize = sprite->getContentSize();
	sprite->setScaleX(visibleSize.height * 1.0 / spriteSize.height);
	sprite->setScaleY(visibleSize.width * 1.0 / spriteSize.width);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(sprite, 0);
	auto multiplayer = Label::create("5v5", "Arial", 30);
	multiplayer->setColor(Color3B(139, 0, 0));
	auto modeMulti = MenuItemLabel::create(multiplayer, CC_CALLBACK_1(ModeScene::menuMultiplayer5, this));
	auto menu1 = Menu::create(modeMulti, NULL);
	menu1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3);
	this->addChild(menu1, 1);
	auto singleplayer1 = Label::create("1v1(PVP)       ", "Arial", 30);
	singleplayer1->setColor(Color3B(139, 0, 0));
	auto modeSingle1 = MenuItemLabel::create(singleplayer1, CC_CALLBACK_1(ModeScene::menuSingle1, this));
	auto singleplayer2 = Label::create("1v1(PVE)", "Arial", 30);
	singleplayer2->setColor(Color3B(139, 0, 0));
	auto modeSingle2 = MenuItemLabel::create(singleplayer2, CC_CALLBACK_1(ModeScene::menuSingle2, this));
	auto menu2 = Menu::create(modeSingle1, modeSingle2, NULL);
	menu2->alignItemsHorizontally();
	menu2->setPosition(origin.x + visibleSize.width / 2, origin.y + 2 * visibleSize.height / 3);
	this->addChild(menu2, 1);
	return true;
}
void ModeScene::menuMultiplayer5(cocos2d::Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	Director::getInstance()->end();
}

void ModeScene::menuSingle1(cocos2d::Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	Director::getInstance()->end();
}
void ModeScene::menuSingle2(cocos2d::Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	Director::getInstance()->end();
}