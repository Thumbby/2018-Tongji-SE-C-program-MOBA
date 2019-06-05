#include "HelloWorldScene.h"

#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"

#include "ShopLayer.h"

#include <cmath>
int ID1;

USING_NS_CC;



using namespace cocostudio::timeline;



Scene* HelloWorld::createScene(int ID)
{
	auto scene = Scene::createWithPhysics();

	ID1 = ID;

	auto layer = HelloWorld::create();

	layer->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;

}



// on "init" you need to initialize your instance
Point Aim_Location;
bool HelloWorld::init()

{

	//////////////////////////////
	log("ID %d", ID1);
	// 1. super init first

	if (!Layer::init())

	{

		return false;

	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//CCTMXTiledMap* map = CCTMXTiledMap::create("background.tmx");

	//this->addChild(map);

	image = new Image();//新建地图

	image->initWithImageFile("gf.png");

	outButton = MenuItemImage::create("MM01.png", "MM07.png", CC_CALLBACK_1(HelloWorld::Shop, this));
	outButton->setTag(0);

	outButton->setRotation(90);
	outButton->setPosition(visibleSize.width / 80, 2 * visibleSize.height / 3);
	//this->addChild(outButton);
	auto menu = Menu::create(outButton, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

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


	//将事件监听器与场景绑定

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//各种计时器
	skillTimeCounter = TimeCounter::create();

	this->addChild(skillTimeCounter);


	soliderTimeCounter = TimeCounter::create();

	this->addChild(soliderTimeCounter);

	soliderTimeCounter->start();

	HeroTimeCounter = TimeCounter::create();

	this->addChild(HeroTimeCounter);

	Atk=TimeCounter::create();

	this->addChild(Atk);

	//英雄
	hero = Hero::createHeroSprite(Vec2(320, 180), 2, "stand",ID1);

	hero->setScale(1.0f);

	hero->setName("hero");
	//
	hero->ID = ID1;

	hero->Level = 6;

	hero->Money = 0;

	hero->Exp = 0;

	hero->Attack_Ready = 0;

	string level = to_string(hero->Level);

	label = Label::createWithTTF(level, "fonts/Marker Felt.ttf", 30);

	label->setColor(Color3B(0, 0, 0));

	label->setPosition(Point(hero->position.x - 35, hero->position.y + 43));

	label->setScale(0.3f);

	hero->addChild(label);

	sprBar = Sprite::create("bar.png");

	sprBar->setScale(0.1f);

	hero->addChild(sprBar);



	sprBar2 = Sprite::create("bar.png");

	sprBar2->setScale(0.1f);

	hero->addChild(sprBar2);



	sprBlood = Sprite::create("blood.png");

	progress = ProgressTimer::create(sprBlood);

	progress->setType(ProgressTimer::Type::BAR);

	progress->setScale(0.1f);

	progress->setMidpoint(Point(0, 0.5));

	progress->setBarChangeRate(Point(1, 0));

	hero->addChild(progress);



	auto sprMagic = Sprite::create("magic.png");

	progress2 = ProgressTimer::create(sprMagic);

	progress2->setType(ProgressTimer::Type::BAR);

	progress2->setScale(0.1f);

	progress2->setMidpoint(Point(0, 0.5));

	progress2->setBarChangeRate(Point(1, 0));

	hero->addChild(progress2);

	sprBar->setPosition(Point(hero->position.x, hero->position.y + 45));

	sprBar2->setPosition(Point(hero->position.x, hero->position.y + 40));

	progress->setPosition(Point(hero->position.x, hero->position.y + 45));

	progress2->setPosition(Point(hero->position.x, hero->position.y + 40));

	log("%d", ID);

	if (hero->ID == 1) {

		Skill_Q = TimeCounter::create();

		this->addChild(Skill_Q);

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;


		hero->HP = 100;

		hero->MP = 100;

		hero->Attack = 70;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 0;

		hero->Defense = 50;

		hero->Resistance = 30;

		hero->HP_Recover = 1;

		hero->MP_Recover = 0.2;

		this->addChild(hero);

	}
	if (hero->ID == 2) {

		Skill_Q = TimeCounter::create();

		this->addChild(Skill_Q);

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;


		hero->HP = 100;

		hero->MP = 100;

		hero->Attack = 70;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 0;

		hero->Defense = 50;

		hero->Resistance = 30;

		hero->HP_Recover = 1;

		hero->MP_Recover = 0.2;

		this->addChild(hero);

	}
	if (hero->ID == 3) {

		Skill_Q = TimeCounter::create();

		this->addChild(Skill_Q);

		Skill_W = TimeCounter::create();

		this->addChild(Skill_W);

		Skill_R = TimeCounter::create();

		this->addChild(Skill_R);

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;

		hero->Skill_R_On_Release = 0;

		hero->HP = 500;

		hero->MP = 500;

		hero->Attack = 70;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 10;

		hero->Attack_Speed = 1;

		hero->Attack_Range = 200;

		hero->Defense = 50;

		hero->Resistance = 30;

		hero->HP_Recover = 1;

		hero->MP_Recover = 0.2;

		this->addChild(hero);

	}
	//野怪
	monster = Monster::createMonsterSprite(Vec2(1050, 950), 2, "stand");

	addChild(monster);

	//防御塔
	tower = Tower::create();

	tower->setTag(1000);

	tower->setPosition(Point(500, 500));

	this->addChild(tower);


	//键盘监听
	auto* dispatcher = Director::getInstance()->getEventDispatcher();

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
	//hero->addChild();
	//auto aim1 = this->getChildByTag(20);

//aim1->setPosition(Point(aim1->getPosition().x + 1, aim1->getPosition().y));

//aim2->setPosition(Point(aim2->getPosition().x + 1, aim2->getPosition().y));
	hero->Attack_Cool_Down = 3 / (hero->Attack_Speed);
	
	progress->setPercentage((((float)hero->HP) / hero->MaxHP) * 100);

	progress2->setPercentage((((float)hero->MP) / hero->MaxMP) * 100);

	hero->Death();

	string level = to_string(hero->Level);

	label = Label::createWithTTF(level, "fonts/Marker Felt.ttf", 30);

	label->setColor(Color3B(0, 0, 0));

	label->setPosition(Point(hero->position.x - 110, hero->position.y + 75));


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
	if (hero->HP <= hero->MaxHP) {
		hero->HP = hero->HP + hero->HP_Recover;
		if (hero->HP > hero->MaxHP) {
			hero->HP = hero->MaxHP;
		}
	}
	if (hero->MP <= hero->MaxMP) {
		hero->MP = hero->MP + hero->MP_Recover;
		if (hero->MP > hero->MaxMP) {
			hero->MP = hero->MaxMP;
		}
	}
	if (hero->ID == 1) {

		//英雄Q技能
		switch (hero->Skill_Q_On_Release)
		{
		case 1: {
			Skill_Q->start();

			hero->Skill_Q_On_Release = 2;

			break;
		}

		case 2: {
			float time1 = Skill_Q->getfCurTime();

			if (time1 >= 5) {

				hero->Skill_Q_On_Release = -1;

				this->removeChild(Effect_Q);
			}

			break;
		}

		case -1: {
			float time2 = Skill_Q->getfCurTime();

			if (time2 >= hero->Skill_Q_Cool_Down) {

				hero->Skill_Q_On_Release = 0;

			}
			break;
		}
		}

		//英雄W技能
		if (hero->Skill_W_On_Release == 1 && hero->MP >= 0) {

			hero->MP--;

		}

		if (hero->Skill_W_On_Release == 1 && hero->MP < 0)
		{
			hero->Skill_W_On_Release = 0;

			hero->speed = hero->speed / 2;

			hero->Attack_Speed = hero->Attack_Speed / 2;
		}
	}
	if (hero->ID == 2) {

		//英雄Q技能
		switch (hero->Skill_Q_On_Release)
		{
		case 1: {
			Skill_Q->start();

			hero->Skill_Q_On_Release = 2;

			break;
		}

		case 2: {
			float time1 = Skill_Q->getfCurTime();

			if (time1 >= 5) {

				hero->Skill_Q_On_Release = -1;

				this->removeChild(Effect_Q);
			}

			break;
		}

		case -1: {
			float time2 = Skill_Q->getfCurTime();

			if (time2 >= hero->Skill_Q_Cool_Down) {

				hero->Skill_Q_On_Release = 0;

			}
			break;
		}
		}

		//英雄W技能
		if (hero->Skill_W_On_Release == 1 && hero->MP >= 0) {

			hero->MP--;

		}

		if (hero->Skill_W_On_Release == 1 && hero->MP < 0)
		{
			hero->Skill_W_On_Release = 0;

			//hero->speed = hero->speed / 2;

			hero->Attack_Speed = hero->Attack_Speed / 2;
		}
	}
	if (hero->ID == 3) {
		//英雄平A
		switch (hero->Attack_Ready)
		{
		case 1: {

			Atk->start();

			hero->Attack_Ready = 2;

			break;
		}
		case 2: {
			float attack_time = Atk->getfCurTime();

			if (attack_time >= hero->Attack_Cool_Down) {

				hero->Attack_Ready = 0;
			}
			break;
		}
		}
		//英雄Q技能
		if (hero->Skill_Q_On_Release==1&&hero->MP>=8)
		{
			hero->Attack = 70+(hero->Level*0.5);

		}
		if (hero->MP<8)
		{
			hero->Skill_Q_On_Release = 0;
		}

		//英雄W技能
		switch (hero->Skill_W_On_Release)
		{
		case 1: {
			Skill_W->start();
			hero->Attack_Speed = 10 ;
			hero->Skill_W_On_Release = 2;
			break;
		}
		case 2: {
			if (Skill_W->getfCurTime() >= 3) {
				hero->Attack_Speed =3;
				hero->Skill_W_On_Release = 3;
			}
			break;
		}
		case 3: {
			if (Skill_W->getfCurTime()>=hero->Skill_W_Cool_Down)
			{
				hero->Skill_W_On_Release = 0;
			}
			break;
		}
		}
		//英雄R技能
		switch (hero->Skill_R_On_Release)
		{
		case 1: {
			Skill_R->start();

			hero->Skill_R_On_Release = 2;

			break;
		}
		case 2: {
			if (Skill_R->getfCurTime()>=hero->Skill_R_Cool_Down)
			{
				hero->Skill_R_On_Release = 0;
			}
		}
		}
	}

	hero->Money++;

	tower->progress->setPercentage((tower->HP / tower->MaxHP) * 100);

	Point temp;

	temp.x = pos.x;

	temp.y = pos.y;

	if ((temp.x - hero->position.x) * (temp.x - hero->position.x) + (temp.y - hero->position.y) * (temp.y - hero->position.y) <= (1 / hero->speed) * (1 / hero->speed))

	{

		hero->isRun = false;

		hero->setAction(hero->direction, "stand", 4);

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

		hero->setAction(hero->direction, "stand", 4);

		return;

	}



	if (hero->isRun == false)

	{

		hero->isRun = true;

		nowDirection = hero->direction;

		hero->setAction(hero->direction, "run", 4);

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

		if ((temp.x - hero->position.x) * (temp.x - hero->position.x) + (temp.y - hero->position.y) * (temp.y - hero->position.y) <= hero->speed)
			temp = hero->position;

		else if (bgPoint.y <= 0 && bgPoint.x <= 0 && bgPoint.x + bgSize.width >= visibleSize.width && bgPoint.y + bgSize.height >= visibleSize.height)

			sp1->setPosition(bgPoint);

		auto tower = (Tower*)this->getChildByTag(1000);

		tower->setPosition(bgPoint + Point(500, 500));

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

	}log("%d");

	if (bullet.size() >= 1)
	{
		for (auto it = bullet.begin(); it != bullet.end();)
		{
			auto aim = (Tower*)this->getChildByTag(choice);
			if (aim == NULL)break;
			Point pos1 = (*it)->getPosition();

			Aim_Location = pos1;

			(*it)->setRotation(360-180/3.14*atan2((aim->getPositionY() - (*it)->getPositionY()) , (aim->getPositionX() - (*it)->getPositionX())));

			float r2 = sqrt((pos1.x - aim->getPosition().x) * (pos1.x - aim->getPosition().x) + (pos1.y - aim->getPosition().y) * (pos1.y - aim->getPosition().y));

			(*it)->setPosition(Point(pos1.x + 20 * (aim->getPosition().x - pos1.x) / r2, pos1.y + 20 * (aim->getPosition().y - pos1.y) / r2));



			if (r2 <= 10)
			{
				if ((*it)->getName()=="attack")
				{
					aim->HP -= hero->Attack;
				}
				else if ((*it)->getName()== "skill") {
					aim->HP -=1000;
				}
				this->removeChild(*it);

				it = bullet.erase(it);

			}
			else
				it++;
		}
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
		-= rc.size.width * 0.5;

	rc.origin.y
		-= rc.size.height * 0.5;

	return rc;

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)

{
	//获取触屏位置（坐标）
	log("TouchBegan");
	pos = touch->getLocation();

	flag = 1;

	Point touchLocation = convertTouchToNodeSpace(touch);


	for (int i = 1000; i <= 1000; i++)
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
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero->ID == 1)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			hero->isRun == false;

			hero->setAction(hero->direction, "attack", 4);

			if (hero->Skill_E_On_Release == 1)
			{
				hero->setVisible(true);

			}
		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4);

		}
		}
	}
	if (hero->ID == 2)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			hero->isRun == false;

			hero->setAction(hero->direction, "attack", 4);

			if (hero->Skill_E_On_Release == 1)
			{
				hero->setVisible(true);

			}
		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4);

		}
		}
	}
	if (hero->ID == 3)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			if (hero->Attack_Ready == 0)
			{
				hero->isRun == false;

				hero->setAction(hero->direction, "attack", 4);

				if (hero->Skill_E_On_Release == 1)
				{
					hero->setVisible(true);

				}
			}
		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			//hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4);

		}
		}
	}
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero->ID == 1) {
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			if (hero->Attack_Ready == 0)
			{
				if (hero->Skill_E_On_Release == 1)
				{
					hero->Critical_Rate = hero->Critical_Rate / 2;

					hero->Skill_E_On_Release = 0;

				}
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

				bullet0->setName("attack");

				bullet.push_back(bullet0);

			}
			break;
		}

		case EventKeyboard::KeyCode::KEY_Q: {
			if (hero->MP >= 20 && hero->Skill_Q_On_Release == 0) {

				hero->MP -= 20;

				Effect_Q = Sprite::create("Huaji.png");

				Effect_Q->setPosition(Point(pos.x, pos.y));

				Effect_Q->setScale(0.2f);

				this->addChild(Effect_Q);

				hero->Skill_Q_On_Release = 1;
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_W: {

			if (hero->Skill_W_On_Release == 0 && hero->HP >= 10)
			{
				hero->HP -= 10;

				hero->Attack = hero->Attack * 2;

				hero->speed = hero->speed * 2;

				hero->Skill_W_On_Release = 1;

			}
			else if (hero->Skill_W_On_Release == 1) {

				if (hero->MP > 0) {

					hero->Attack = hero->Attack / 2;

					hero->speed = hero->speed / 2;

					hero->Skill_W_On_Release = 0;
				}

			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_E: {
			if (hero->MP > 70 && hero->Skill_E_On_Release == 0)
			{
				hero->MP -= 70;

				hero->setVisible(false);

				hero->Critical_Rate = hero->Critical_Rate * 10;

				hero->Skill_E_On_Release = 1;
			}
			break;
		}
		}
	}
	if (hero->ID == 2) {
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			if (hero->Skill_E_On_Release == 1)
			{
				hero->Critical_Rate = hero->Critical_Rate / 2;

				hero->Skill_E_On_Release = 0;

			}
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

			bullet0->setName("attack");

			bullet.push_back(bullet0);


			break;
		}

		case EventKeyboard::KeyCode::KEY_Q: {
			if (hero->MP >= 20 && hero->Skill_Q_On_Release == 0) {

				hero->MP -= 20;

				Effect_Q = Sprite::create("Huaji.png");

				Effect_Q->setPosition(Point(pos.x, pos.y));

				Effect_Q->setScale(0.2f);

				this->addChild(Effect_Q);

				hero->Skill_Q_On_Release = 1;
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_W: {

			if (hero->MP>=50&&hero->Skill_W_On_Release==0)
			{
				hero->MP -= 50;

				hero->Skill_W_On_Release = 1;
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_E: {
			if (hero->MP > 70 && hero->Skill_E_On_Release == 0)
			{
				hero->MP -= 70;

				hero->setVisible(false);

				hero->Critical_Rate = hero->Critical_Rate * 10;

				hero->Skill_E_On_Release = 1;
			}
			break;
		}
		}
	}
	if (hero->ID == 3) {
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_A:
		{
			float distance = (hero->getPosition().x - Aim_Location.x) * (hero->getPosition().x - Aim_Location.x) + (hero->getPosition().y - Aim_Location.y) * (hero->getPosition().y - Aim_Location.y);
			if (hero->Attack_Ready == 0&&hero->Attack_Range>=distance) {
				if (hero->Skill_E_On_Release == 1)
				{

					hero->speed = hero->speed / 2;

					hero->Skill_E_On_Release = 0;

					hero->Critical_Rate = hero->Critical_Rate / 2;

				}
				if (hero->Skill_Q_On_Release == 1)
				{
					hero->MP -= 8;

					auto bullet0 = Sprite::create("bullet.png");
				}
				auto visibleSize = Director::getInstance()->getVisibleSize();

				if (hero->Skill_Q_On_Release == 1)
				{
					auto bullet0 = Sprite::create("bullet.png");

					bullet0->setPosition(Point(hero->position.x, hero->position.y));

					this->addChild(bullet0);

					bullet0->setName("attack");

					bullet.push_back(bullet0);

				}
				else if (hero->Skill_Q_On_Release == 0) {

					auto bullet0 = Sprite::create("arrow.png");

					bullet0->setPosition(Point(hero->position.x, hero->position.y));

					this->addChild(bullet0);

					bullet0->setName("attack");

					bullet.push_back(bullet0);

				}
				hero->Attack_Ready = 1;
			}
			break;
		}

		case EventKeyboard::KeyCode::KEY_Q: {
			if ( hero->Skill_Q_On_Release == 0) {
				hero->Skill_Q_On_Release = 1;
			}
			else if (hero->Skill_Q_On_Release == 1) {
				hero->Skill_Q_On_Release = 0;
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_W: {
			if (hero->MP>=50&&hero->Skill_W_On_Release==0)
			{
				hero->Skill_W_On_Release = 1;

				hero->MP -= 50;
			}

			break;
		}
		case EventKeyboard::KeyCode::KEY_E: {
			if (hero->MP > 70 && hero->Skill_E_On_Release == 0)
			{
				hero->MP -= 70;

				hero->setVisible(false);

				hero->Critical_Rate = hero->Critical_Rate * 10;

				hero->speed = hero->speed * 2;

				hero->Skill_E_On_Release = 1;
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_R: {
			if (hero->MP >= 120 &&hero->Skill_R_On_Release==0)
			{
				hero->MP -= 120;

				auto visibleSize = Director::getInstance()->getVisibleSize();

				auto bullet0 = Sprite::create("bomb.png");

				bullet0->setPosition(Point(hero->position.x, hero->position.y));

				this->addChild(bullet0);

				bullet0->setName("skill");

				bullet.push_back(bullet0);

				hero->Skill_R_On_Release = 1;

			}
		}
		}
	}
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
		{
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
void HelloWorld::Shop(Ref* psender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (outButton->getTag() == 0)
	{
		outButton->setRotation(270);
		

		Sprite* window = Sprite::create("window.png");
		window->setPosition(visibleSize.width / 2, 2 * visibleSize.height / 3 - 50);
		window->setScaleX(1.5);
		this->addChild(window, 0);
		ShopLayer* scrollView = ShopLayer::create();
		window->setName("remove1");
		scrollView->setName("remove2");
		this->addChild(scrollView);
		outButton->setTag(1);
	}
	else
	{
		outButton->setRotation(90);
		this->removeChildByName("remove1");
		this->removeChildByName("remove2");
		outButton->setTag(0);
	}
}
/*PhysicsBody* bulletBody = PhysicsBody::createBox(bullet0->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

bulletBody->setGravityEnable(false);

bulletBody->setCategoryBitmask(0x01);

bulletBody->setContactTestBitmask(0x01);


bulletBody->setCollisionBitmask(0x01);

bullet0->setPhysicsBody(bulletBody);*/