#include "HelloWorldScene.h"
#include "SocketManager.h"
#include<string>
USING_NS_CC;
using namespace std;
Scene* HelloWorld::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
	char str[100] = "hello world";

	 
    SocketManager::getInstance()->start();
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	scheduleUpdate();
	log("%d", pos.x);
    return true;
}
void  HelloWorld::update(float dt)
{
	char msg[100];
	if (pos.x != 0)
	{
		itoa(pos.x, msg, 10);
		SocketManager::getInstance()->sendMsg(msg);
	}
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{
	pos = touch->getLocation();
	return true;
}

