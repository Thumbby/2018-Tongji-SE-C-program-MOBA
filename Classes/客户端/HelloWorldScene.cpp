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

	//log("%d", pos.x);



	sprite = Sprite::create("HelloWorld.png");

	sprite->setScale(0.2);

	sprite->setPosition(0, 0);

	this->addChild(sprite);

    return true;
}

void  HelloWorld::update(float dt)
{

	char msg[100];

	char msg1[100];

	char blank[2] = "H";

	//CCLOG("%d  %d", pos.x, pos.y);

	//sprite->setPosition((int)pos.x, (int)pos.y);


	if (pos.x != 0)
	{
		itoa(pos.x, msg, 10);

		itoa(pos.y, msg1, 10);

		strcat(msg, blank);

		strcat(msg, msg1);

		SocketManager::getInstance()->sendMsg(msg);
	}
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{
	pos = touch->getLocation();

	auto moveto = MoveTo::create(1.2f, Point(pos.x, pos.y));

	sprite->runAction(moveto);

	return true;
}

