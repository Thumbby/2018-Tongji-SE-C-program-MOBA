#include "SecondScene.h"
#include "OpeningScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
Scene* OpeningScene::createScene()
{
	return OpeningScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool OpeningScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/backgroundmusic.mp3", true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Label* start = Label::create("Start", "Arial", 30);
	start->setColor(Color3B(150, 150, 150));
	auto nextItem = MenuItemLabel::create(start, CC_CALLBACK_1(OpeningScene::menuCloseCallback, this));
	nextItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	auto menu = Menu::create(nextItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto sprite = Sprite::create("UI/entrance1.jpg");
	auto spriteSize = sprite->getContentSize();
	sprite->setScaleX(visibleSize.height * 1.0 / spriteSize.height);
	sprite->setScaleY(visibleSize.width * 1.0 / spriteSize.width);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}



void OpeningScene::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/click.mp3");
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, SecondScene::createScene()));
	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}