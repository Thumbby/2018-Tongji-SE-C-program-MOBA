#include "cocos2d.h"
#include "HeroSelectScene.h"
#include"HelloWorldScene.h"
using namespace cocos2d;
Scene* HeroSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HeroSelectScene::create();
	scene->addChild(layer);
	return scene;
}
bool HeroSelectScene::init()
{
	auto sprite = Sprite::create("UI/entrance4.jpg");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto spriteSize = sprite->getContentSize();
	sprite->setScaleX(visibleSize.height * 1.0 / spriteSize.height);
	sprite->setScaleY(visibleSize.width * 1.0 / spriteSize.width);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(sprite, 0);
	auto warrier = Label::create("Warrier", "Arial", 30);
	warrier->setColor(Color3B(139, 0, 0));
	auto itemWarrier = MenuItemLabel::create(warrier, CC_CALLBACK_1(HeroSelectScene::warrierSelect, this));
	auto mage = Label::create("Mage", "Arial", 30);
	mage->setColor(Color3B(139, 0, 0));
	auto itemMage = MenuItemLabel::create(mage, CC_CALLBACK_1(HeroSelectScene::mageSelect, this));
	auto archer = Label::create("Archer", "Arial", 30);
	archer->setColor(Color3B(139, 0, 0));
	auto itemArcher = MenuItemLabel::create(archer, CC_CALLBACK_1(HeroSelectScene::archerSelect, this));
	auto menu1 = Menu::create(itemWarrier, NULL);
	menu1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4);
	this->addChild(menu1, 1);
	auto menu2 = Menu::create(itemArcher, NULL);
	menu2->setPosition(origin.x + visibleSize.width / 3, origin.y + 2 * visibleSize.height / 3);
	this->addChild(menu2, 1);
	auto menu3 = Menu::create(itemMage, NULL);
	menu3->setPosition(origin.x + 2 * visibleSize.width / 3, origin.y + 2 * visibleSize.height / 3);
	this->addChild(menu3, 1);
	return true;
}
void HeroSelectScene::warrierSelect(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, HelloWorld::createScene(1)));
}
void HeroSelectScene::mageSelect(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, HelloWorld::createScene(2)));
}
void HeroSelectScene::archerSelect(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, HelloWorld::createScene(3)));
}