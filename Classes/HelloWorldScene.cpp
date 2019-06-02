
#include "HelloWorldScene.h"

#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"



USING_NS_CC;



using namespace cocostudio::timeline;



Scene* HelloWorld::createScene()

{
	auto scene = Scene::createWithPhysics();

	auto layer = HelloWorld::create();

	layer->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;

}



// on "init" you need to initialize your instance

bool HelloWorld::init()

{

	//////////////////////////////

	// 1. super init first

	if (!Layer::init())

	{

		return false;

	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	CCTMXTiledMap *map = CCTMXTiledMap::create("background.tmx");

	this->addChild(map);

	image = new Image();//新建地图

	image->initWithImageFile("gf.png");

	CCLOG("%d，%d", image->getHeight(), image->getWidth());



	background = Sprite::create("background.png");

	background->setPosition(0, 0);

	background->setAnchorPoint(Vec2(0, 0));

	this->addChild(background, 0, 200);

	//background[1] = Sprite::create("background3.png");

	//background[1]->setOpacity(150);

	//background[1]->setPosition(-600, -550);

	//background[1]->setAnchorPoint(Vec2(0, 0));

	//this->addChild(background[1],1 ,201);

	Sprite* mouse = Sprite::create("mouse.png");

	mouse->setScale(0.5f);

	this->addChild(mouse);

	//创建事件监听器，监听键盘事件

	auto myKeyListener = EventListenerKeyboard::create();

	//当键盘被按下时响应

	myKeyListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, cocos2d::Event* event)

	{

		CCLOG("key is pressed,keycode is %d", keycode);

	};



	//创建事件监听器，监听鼠标事件

	auto myMouseListener = EventListenerMouse::create();

	//鼠标移动
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);


	myMouseListener->onMouseMove = [=](Event* event)

	{

		EventMouse* e = (EventMouse*)event;

		mouse->setPosition(e->getCursorX(), e->getCursorY());

	};

	//当鼠标被按下



	//将事件监听器与场景绑定

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);



	soliderTimeCounter = TimeCounter::create();

	this->addChild(soliderTimeCounter);

	soliderTimeCounter->start();

	HeroTimeCounter = TimeCounter::create();

	this->addChild(HeroTimeCounter);

	hero = Hero::createHeroSprite(Vec2(320, 180), 2, "stand");

	hero->HP = hero->MaxHP;

	hero->MP = hero->MaxMP;

	hero->setScale(0.8f);

	addChild(hero);

	monster = Monster::createMonsterSprite(Vec2(1050, 950), 2, "stand");

	addChild(monster);



	sprBar = Sprite::create("bar.png");

	sprBar->setScale(0.15f);

	hero->addChild(sprBar);



	sprBar2 = Sprite::create("bar.png");

	sprBar2->setScale(0.15f);

	hero->addChild(sprBar2);



	sprBlood = Sprite::create("blood.png");

	progress = ProgressTimer::create(sprBlood);

	progress->setType(ProgressTimer::Type::BAR);

	progress->setScale(0.15f);

	progress->setMidpoint(Point(0, 0.5));

	progress->setBarChangeRate(Point(1, 0));

	hero->addChild(progress);



	auto sprMagic = Sprite::create("magic.png");

	progress2 = ProgressTimer::create(sprMagic);

	progress2->setType(ProgressTimer::Type::BAR);

	progress2->setScale(0.15f);

	progress2->setMidpoint(Point(0, 0.5));

	progress2->setBarChangeRate(Point(1, 0));

	hero->addChild(progress2);
	//靶子
	auto aim1 = Sprite::create("rocker.png");

	aim1->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));

	this->addChild(aim1);

	aim1->setTag(20);

	PhysicsBody* aim1Body = PhysicsBody::createBox(aim1->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	aim1Body->setGravityEnable(false);

	aim1Body->setCategoryBitmask(0x01);

	aim1Body->setContactTestBitmask(0x01);

	aim1Body->setCollisionBitmask(0x01);

	aim1->setPhysicsBody(aim1Body);

	auto aim2 = Sprite::create("rocker.png");

	aim2->setPosition(Point(visibleSize.width / 4, 3 * visibleSize.height / 4));

	this->addChild(aim2);

	aim2->setTag(21);

	PhysicsBody* aim2Body = PhysicsBody::createBox(aim2->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	aim2Body->setGravityEnable(false);

	aim2Body->setCategoryBitmask(0x01);

	aim2Body->setContactTestBitmask(0x01);

	aim2Body->setCollisionBitmask(0x01);

	aim2->setPhysicsBody(aim2Body);
	//键盘监听
	auto *dispatcher = Director::getInstance()->getEventDispatcher();

	auto* keyListener = EventListenerKeyboard::create();

	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);

	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	scheduleUpdate();

	//delete image;



	return true;

}

void HelloWorld::update(float dt)

{
	//log("dt");
	sprBar->setPosition(Point(hero->position.x, hero->position.y + 80));

	sprBar2->setPosition(Point(hero->position.x, hero->position.y + 73));

	progress->setPosition(Point(hero->position.x, hero->position.y + 80));

	progress->setPercentage((((float)hero->HP) / hero->MaxHP) * 100);

	progress2->setPosition(Point(hero->position.x, hero->position.y + 73));

	progress2->setPercentage((((float)hero->MP) / hero->MaxMP) * 100);



	hero->Death();

	//auto aim1 = this->getChildByTag(20);

	//aim1->setPosition(Point(aim1->getPosition().x + 1, aim1->getPosition().y));

	//auto aim2 = this->getChildByTag(21);

	//aim2->setPosition(Point(aim2->getPosition().x + 1, aim2->getPosition().y));

	if (bullet.size() >= 1)
	{
		for (auto it = bullet.begin(); it != bullet.end(); it++)
		{
			auto aim = this->getChildByTag(choice);
			if (aim == NULL)break;
			Point pos1 = (*it)->getPosition();

			float r2 = sqrt((pos1.x - aim->getPosition().x)*(pos1.x - aim->getPosition().x) + (pos1.y - aim->getPosition().y)*(pos1.y - aim->getPosition().y));

			(*it)->setPosition(Point(pos1.x + 3 * (aim->getPosition().x - pos1.x) / r2, pos1.y + 3 * (aim->getPosition().y - pos1.y) / r2));
		}
	}

	if (hero->HP == 0) {

		hero->DeadTime = 0;

		HeroTimeCounter->start();

	}

	if (hero->HP < 0) {

		if ((HeroTimeCounter->getfCurTime() - hero->DeadTime) >= 5) {

			hero->setVisible(true);

			for (auto solider : m_soliderManager)

			{

				if (solider->isAlive)

				{

					solider->setPosition(solider->getPositionX() - background->getPositionX(), solider->getPositionY() - background->getPositionY());

				}

			}

			background->setPosition(0, 0);

			hero->HP = hero->MaxHP;

			hero->MP = hero->MaxMP;

		}

	}

	//hero->HP--;

	//hero->MP--;

	Point temp;

	temp.x = pos.x;

	temp.y = pos.y;

	if ((temp.x - hero->position.x) * (temp.x - hero->position.x) + (temp.y - hero->position.y) * (temp.y - hero->position.y) <= (1 / hero->speed) * (1 / hero->speed))

	{

		hero->isRun = false;

		hero->setAction(hero->direction, "stand", 2);

	}

	else if (temp.x - hero->position.x == 0 && temp.y - hero->position.y > 0)

		hero->direction = BACK;

	else if (temp.x - hero->position.x == 0 && temp.y - hero->position.y < 0)

		hero->direction = FRONT;

	else if (temp.x - hero->position.x < 0 && temp.y - hero->position.y == 0)

		hero->direction = LEFT;

	else if (temp.x - hero->position.x > 0 && temp.y - hero->position.y == 0)

		hero->direction = RIGHT;

	else if (temp.x - hero->position.x > 0 && temp.y - hero->position.y > 0) {

		if (temp.x - hero->position.x >= temp.y - hero->position.y)

		{

			hero->direction = RIGHT;

		}

		else {

			hero->direction = BACK;

		}

	}

	else if (temp.x - hero->position.x < 0 && temp.y - hero->position.y < 0) {

		if (temp.x - hero->position.x <= temp.y - hero->position.y)

		{

			hero->direction = LEFT;

		}

		else {

			hero->direction = FRONT;

		}

	}

	else if (temp.x - hero->position.x > 0 && temp.y - hero->position.y < 0) {

		if (temp.x - hero->position.x >= (-(temp.y - hero->position.y)))

		{

			hero->direction = RIGHT;

		}

		else {

			hero->direction = FRONT;

		}

	}

	else if (temp.x - hero->position.x < 0 && temp.y - hero->position.y > 0) {

		if ((-(temp.x - hero->position.x)) >= temp.y - hero->position.y)

		{

			hero->direction = LEFT;

		}

		else {

			hero->direction = BACK;

		}

	}

	CCLOG("%f  %f", temp.x - hero->position.x, temp.y - hero->position.y);

	if (pos == Point::ZERO)

	{

		hero->isRun = false;

		hero->setAction(hero->direction, "stand", 2);

		return;

	}



	if (hero->isRun == false)

	{

		hero->isRun = true;

		nowDirection = hero->direction;

		hero->setAction(hero->direction, "run", 2);

	}

	else if (hero->isRun == true)

	{

		if (nowDirection != hero->direction)

		{

			nowDirection = hero->direction;

			hero->setAction(hero->direction, "run", 2);

		}

	}

	float r = (sqrt(((temp.x - hero->position.x) * (temp.x - hero->position.x)) + ((temp.y - hero->position.y) * (temp.y - hero->position.y)))) / (hero->speed);

	float r1 = sqrt(((temp.x - hero->position.x) * (temp.x - hero->position.x)) + ((temp.y - hero->position.y) * (temp.y - hero->position.y))) / (hero->speed);;



	float x = 0;

	float y = 0;

	float w = 0;

	if (r != 0)

	{

		float w = 1 / r;

		float x = (temp.x - hero->position.x) / r;

		float y = (temp.y - hero->position.y) / r;

	}


	if (soliderTimeCounter->getfCurTime() >= 15)

	{

		if (soliderTimeCounter->getfCurTime() - 15 >= counter)

		{

			solider = Monster::createMonsterSprite(Vec2(320 + background->getPositionX(), 180 + background->getPositionY()), 2, "stand");

			this->addChild(solider);

			m_soliderManager.pushBack(solider);

			counter++;

		}

		if (counter >= 5)

		{

			counter = 0;

			soliderTimeCounter->start();

		}

	}

	if (m_soliderManager.size())

	{

		for (auto solider : m_soliderManager)

		{

			if (solider->isAlive)

			{

				if (solider->isAttacked)

				{

					solider->runAttack(solider);

					solider->isAttacked = 0;

				}

				else

				{

					solider->setPosition(solider->getPositionX() + 0.5, solider->getPositionY() + 0.5);

				}

			}

		}

	}

	float m = background->getPositionX();

	float n = background->getPositionY();

	float monsterX = monster->getPositionX();

	float monsterY = monster->getPositionY();



	if (r != 0)

	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		auto sp1 = this->getChildByTag(200);

		auto bgPoint = sp1->getPosition();

		auto bgSize = sp1->getContentSize();

		bgPoint = Point(bgPoint.x - (temp.x - hero->position.x) / r, bgPoint.y - (temp.y - hero->position.y) / r);

		if (bgPoint.y <= 0 && bgPoint.x <= 0 && bgPoint.x + bgSize.width >= visibleSize.width&&bgPoint.y + bgSize.height >= visibleSize.height)

			sp1->setPosition(bgPoint);

		monster->setPosition(monsterX - (temp.x - hero->position.x) / r1, monsterY - (temp.y - hero->position.y) / r1);

		for (auto solider : m_soliderManager)

		{

			solider->setPosition(solider->getPositionX() - (temp.x - hero->position.x) / r1, solider->getPositionY() - (temp.y - hero->position.y) / r1);

		}



		pos.x = pos.x - (temp.x - hero->position.x) / r;

		pos.y = pos.y - (temp.y - hero->position.y) / r;

	}



	if (monster->isAttacked)

	{

		monster->runAttack(monster);

		monster->isAttacked = 0;

	}

	else

	{

		monster->waiting();

	}

}

Color4B HelloWorld::getColor(int x, int y)

{

	//Image * image = new Image();

	//image->initWithImageFile("background1.jpg");

	y = image->getHeight() - y;

	//y = 1690 - y;

	unsigned char* m_pData = image->getData();



	//int x = (int)posx;

	//int y = (int)posy;

	Color4B c = { 0, 0, 0, 0 };

	unsigned int* pixel = (unsigned int*)m_pData;

	//int width = image->getWidth();

	pixel = pixel + y * 2998 + x;        //480 是图片的宽

	c.r = *pixel & 0xff;

	c.g = (*pixel >> 8) & 0xff;

	c.b = (*pixel >> 16) & 0xff;

	c.a = (*pixel >> 24) & 0xff;

	CCLOG("color r:%d g:%d b:%d a:%d ", c.r, c.g, c.b, c.a);

	return c;



}

static CCRect getRect(CCNode* pNode)

{

	CCRect
		rc;

	rc.origin
		= pNode->getPosition();

	rc.size
		= pNode->getContentSize();

	rc.origin.x
		-= rc.size.width*0.5;

	rc.origin.y
		-= rc.size.height*0.5;

	return rc;

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)

{
	//获取触屏位置（坐标）
	log("TouchBegan");
	pos = touch->getLocation();

	flag = 1;

	Point touchLocation = convertTouchToNodeSpace(touch);

	for (int i = 20; i <= 21; i++)
	{
		auto sprite = this->getChildByTag(i);

		if (getRect(sprite).containsPoint(touchLocation))
		{
			log("1");

			choice = i;

			break;
		}

	}

	return true;

}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{

}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bullet0 = Sprite::create("bullet.png");

	PhysicsBody* bulletBody = PhysicsBody::createBox(bullet0->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	bulletBody->setGravityEnable(false);

	bulletBody->setCategoryBitmask(0x01);

	bulletBody->setContactTestBitmask(0x01);


	bulletBody->setCollisionBitmask(0x01);

	bullet0->setPhysicsBody(bulletBody);

	bullet0->setPosition(Point(hero->position.x, hero->position.y));

	this->addChild(bullet0);

	bullet0->setTag(1);

	bullet.push_back(bullet0);

}
bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{

	log("CONTACT");
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (spriteA->getTag() == spriteB->getTag())
		return true;
	if (spriteA->getTag() == 1)
	{
		for (auto it = bullet.begin(); it != bullet.end(); )
		{//
			if (*it == spriteA)
				it = bullet.erase(it);
			else
				it++;
		}
		this->removeChild(spriteA);
	}
	if (spriteB->getTag() == 1)
	{
		for (auto it = bullet.begin(); it != bullet.end(); )
		{//
			if (*it == spriteB)
				it = bullet.erase(it);
			else
				it++;
		}
		this->removeChild(spriteB);
	}
	return true;
}