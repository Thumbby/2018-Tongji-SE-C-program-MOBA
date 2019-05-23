
#include "Shop.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "ShopLayer.h"
using namespace cocos2d::extension;
using namespace cocostudio::timeline;
USING_NS_CC;

Scene* Shop::createScene()
{
    return Shop::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Shop::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	buildScene1();
    return true;
}
void Shop::buildScene1()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto outButton = MenuItemImage::create("MM01.png", "MM07.png", CC_CALLBACK_1(Shop::menuOut, this));
	outButton->setRotation(90);
	outButton->setScale(10);
	CCLOG("1");
	outButton->setPosition(visibleSize.width / 80, 2 * visibleSize.height / 3);
    auto menu = Menu::create(outButton, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
void Shop::buildScene2()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto inButton = MenuItemImage::create("MM01.png", "MM07.png", CC_CALLBACK_1(Shop::menuIn, this));
	inButton->setRotation(270);
	inButton->setScale(10);
	CCLOG("1");
	inButton->setPosition(visibleSize.width / 80, 2 * visibleSize.height / 3);
	auto menu = Menu::create(inButton, NULL);
	menu->setPosition(Point::ZERO);
	Sprite* background = Sprite::create("background.png");
	background->setScale(20);
	background->setPosition(visibleSize.width / 2, 2*visibleSize.height / 3);
	this->addChild(background, 0);
	this->addChild(menu, 1);
	ShopLayer * scrollView = ShopLayer::create();
	this->addChild(scrollView);

}
void Shop::menuOut(Ref* psender)
{
	this->removeAllChildren();
	buildScene2();
}
void Shop::menuIn(Ref* psender)
{
	this->removeAllChildren();
	buildScene1();
}