#include "HelloWorldScene.h"

#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"

#include "ShopLayer.h"

#include <cmath>

#include "WinLayer.h"

#include "LoseLayer.h"
int ID1;

USING_NS_CC;



using namespace cocostudio::timeline;



Scene* HelloWorld::createScene(int ID)
{
	auto scene = Scene::createWithPhysics();

	ID1 = ID;

	auto layer = HelloWorld::create();



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

	_heroAttack = TimeCounter::create();

	this->addChild(_heroAttack);

	_heroDeath = TimeCounter::create();

	this->addChild(_heroDeath);


	HeroTimeCounter = TimeCounter::create();

	this->addChild(HeroTimeCounter);

	DeadTime = TimeCounter::create();

	this->addChild(DeadTime);

	Atk = TimeCounter::create();

	this->addChild(Atk);

	//英雄
	hero = Hero::createHeroSprite(Vec2(400, 200), 2, "stand", ID1);

	hero->setScale(1.0f);

	hero->setName("hero");

	hero->life = 1;

	hero->Level = 1;

	hero->MaxExp = 600;

	hero->Money = 0;

	hero->speed = 0.9;

	hero->Exp = 0;

	hero->Attack_Ready = 0;

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
	//AI
	_hero = Hero::createHeroSprite(Vec2(2670, 1500), 2, "stand", 1);//2670 1500

	_hero->life = 0;

	_hero->MaxHP = 1000;

	_hero->MaxMP = 300;

	_hero->HP = 1000;

	_hero->MP = 300;

	_hero->Attack = 70;

	_hero->Attack_Speed = 3.5;

	_hero->Attack_Range = 20;

	_hero->Skill_Enhance = 0;

	_hero->Critical_Rate = 10;

	_hero->Defense = 55;

	_hero->Resistance = 35;

	_hero->HP_Recover = 0.5;

	_hero->MP_Recover = 0.15;

	_hero->setScale(1.0f);

	_hero->setName("_hero");

	_hero->life = 1;

	_hero->Level = 1;

	_hero->Money = 0;

	_hero->speed = 0.9;

	_hero->Exp = 0;

	_hero->Attack_Ready = 0;

	_sprBar = Sprite::create("bar.png");

	_sprBar->setScale(0.1f);

	_hero->addChild(_sprBar);

	_sprBar2 = Sprite::create("bar.png");

	_sprBar2->setScale(0.1f);

	_hero->addChild(_sprBar2);

	_sprBlood = Sprite::create("blood.png");

	_progress = ProgressTimer::create(_sprBlood);

	_progress->setType(ProgressTimer::Type::BAR);

	_progress->setScale(0.1f);

	_progress->setMidpoint(Point(0, 0.5));

	_progress->setBarChangeRate(Point(1, 0));

	_hero->addChild(_progress);

	_sprMagic = Sprite::create("magic.png");

	_progress2 = ProgressTimer::create(_sprMagic);

	_progress2->setType(ProgressTimer::Type::BAR);

	_progress2->setScale(0.1f);

	_progress2->setMidpoint(Point(0, 0.5));

	_progress2->setBarChangeRate(Point(1, 0));

	_hero->addChild(_progress2);

	_sprBar->setPosition(Point(_hero->position.x, _hero->position.y + 45));

	_sprBar2->setPosition(Point(_hero->position.x, _hero->position.y + 40));

	_progress->setPosition(Point(_hero->position.x, _hero->position.y + 45));

	_progress2->setPosition(Point(_hero->position.x, _hero->position.y + 40));

	_hero->setTag(6);

	background->addChild(_hero);

	//小兵和塔命名和tag对方为正，本方为负
	//近战小兵
	Death_7 = TimeCounter::create();
	this->addChild(Death_7);
	Attack_7 = TimeCounter::create();
	this->addChild(Attack_7);
	soldier_7 = Hero::createHeroSprite(Vec2(2430, 1345), 2, "stand", 4);
	soldier_7->life = 0;
	soldier_7->Able_To_Attack = 0;
	soldier_7->MaxHP = 500;
	soldier_7->HP = 500;
	soldier_7->Attack = 50;
	soldier_7->Attack_Speed = 3.5;
	soldier_7->Defense = 15;
	soldier_7->Resistance = 10;
	soldier_7->setScale(1.0f);
	soldier_7->setName("soldier_7");
	soldier_7->speed = 0.9;
	soldier_7->Attack_Ready = 0;
	sprBar_7 = Sprite::create("bar.png");
	sprBar_7->setScale(0.1f);
	soldier_7->addChild(sprBar_7);
	sprBlood_7 = Sprite::create("blood.png");
	progress_7 = ProgressTimer::create(sprBlood_7);
	progress_7->setType(ProgressTimer::Type::BAR);
	progress_7->setScale(0.1f);
	progress_7->setMidpoint(Point(0, 0.5));
	progress_7->setBarChangeRate(Point(1, 0));
	soldier_7->addChild(progress_7);
	sprBar_7->setPosition(Point(soldier_7->position.x, soldier_7->position.y + 45));
	progress_7->setPosition(Point(soldier_7->position.x, soldier_7->position.y + 45));
	soldier_7->setTag(7);
	background->addChild(soldier_7);

	_Death_7 = TimeCounter::create();
	this->addChild(_Death_7);
	_Attack_7 = TimeCounter::create();
	this->addChild(_Attack_7);
	_soldier_7 = Hero::createHeroSprite(Vec2(655, 505), 2, "stand", 4);
	_soldier_7->life = 0;
	_soldier_7->Able_To_Attack = 0;
	_soldier_7->MaxHP = 500;
	_soldier_7->HP = 500;
	_soldier_7->Attack = 50;
	_soldier_7->Attack_Speed = 3.5;
	_soldier_7->Defense = 15;
	_soldier_7->Resistance = 10;
	_soldier_7->setScale(1.0f);
	_soldier_7->setName("_soldier_7");
	_soldier_7->speed = 0.9;
	_soldier_7->Attack_Ready = 0;
	_sprBar_7 = Sprite::create("bar.png");
	_sprBar_7->setScale(0.1f);
	_soldier_7->addChild(_sprBar_7);
	_sprBlood_7 = Sprite::create("blood.png");
	_progress_7 = ProgressTimer::create(_sprBlood_7);
	_progress_7->setType(ProgressTimer::Type::BAR);
	_progress_7->setScale(0.1f);
	_progress_7->setMidpoint(Point(0, 0.5));
	_progress_7->setBarChangeRate(Point(1, 0));
	_soldier_7->addChild(_progress_7);
	_sprBar_7->setPosition(Point(_soldier_7->position.x, _soldier_7->position.y + 45));
	_progress_7->setPosition(Point(_soldier_7->position.x, _soldier_7->position.y + 45));
	_soldier_7->setTag(-7);
	background->addChild(_soldier_7);
	_soldier_7->setAction(4, "stand", 4, 4);

	//远程小兵
	Death_8 = TimeCounter::create();
	this->addChild(Death_8);
	Attack_8 = TimeCounter::create();
	this->addChild(Attack_8);
	soldier_8 = Hero::createHeroSprite(Vec2(2440, 1355), 2, "stand", 5);
	soldier_8->life = 0;
	soldier_8->Able_To_Attack = 0;
	soldier_8->MaxHP = 400;
	soldier_8->HP = 400;
	soldier_8->Attack = 55;
	soldier_8->Attack_Speed = 3.5;
	soldier_8->Defense = 15;
	soldier_8->Resistance = 10;
	soldier_8->setScale(1.0f);
	soldier_8->setName("soldier_8");
	soldier_8->speed = 0.9;
	soldier_8->Attack_Ready = 0;
	sprBar_8 = Sprite::create("bar.png");
	sprBar_8->setScale(0.1f);
	soldier_8->addChild(sprBar_8);
	sprBlood_8 = Sprite::create("blood.png");
	progress_8 = ProgressTimer::create(sprBlood_8);
	progress_8->setType(ProgressTimer::Type::BAR);
	progress_8->setScale(0.1f);
	progress_8->setMidpoint(Point(0, 0.5));
	progress_8->setBarChangeRate(Point(1, 0));
	soldier_8->addChild(progress_8);
	sprBar_8->setPosition(Point(soldier_8->position.x, soldier_8->position.y + 45));
	progress_8->setPosition(Point(soldier_8->position.x, soldier_8->position.y + 45));
	soldier_8->setTag(8);
	background->addChild(soldier_8);

	_Death_8 = TimeCounter::create();
	this->addChild(_Death_8);
	_Attack_8 = TimeCounter::create();
	this->addChild(_Attack_8);
	_soldier_8 = Hero::createHeroSprite(Vec2(645, 495), 2, "stand", 5);
	_soldier_8->life = 0;
	_soldier_8->Able_To_Attack = 0;
	_soldier_8->MaxHP = 400;
	_soldier_8->HP = 400;
	_soldier_8->Attack = 5;
	_soldier_8->Attack_Speed = 3.5;
	_soldier_8->Defense = 15;
	_soldier_8->Resistance = 10;
	_soldier_8->setScale(1.0f);
	_soldier_8->setName("_soldier_8");
	_soldier_8->speed = 0.9;
	_soldier_8->Attack_Ready = 0;
	_sprBar_8 = Sprite::create("bar.png");
	_sprBar_8->setScale(0.1f);
	_soldier_8->addChild(_sprBar_8);
	_sprBlood_8 = Sprite::create("blood.png");
	_progress_8 = ProgressTimer::create(_sprBlood_8);
	_progress_8->setType(ProgressTimer::Type::BAR);
	_progress_8->setScale(0.1f);
	_progress_8->setMidpoint(Point(0, 0.5));
	_progress_8->setBarChangeRate(Point(1, 0));
	_soldier_8->addChild(_progress_8);
	_sprBar_8->setPosition(Point(_soldier_8->position.x, _soldier_8->position.y + 45));
	_progress_8->setPosition(Point(_soldier_8->position.x, _soldier_8->position.y + 45));
	_soldier_8->setTag(-8);
	background->addChild(_soldier_8);
	_soldier_8->setAction(4, "stand", 4, 5);

	//炮
	Death_9 = TimeCounter::create();
	this->addChild(Death_9);
	Attack_9 = TimeCounter::create();
	this->addChild(Attack_9);
	soldier_9 = Hero::createHeroSprite(Vec2(2450, 1365), 2, "stand", 6);
	soldier_9->life = 0;
	soldier_9->Able_To_Attack = 0;
	soldier_9->MaxHP = 1000;
	soldier_9->HP = 1000;
	soldier_9->Attack = 70;
	soldier_9->Attack_Speed = 2.0;
	soldier_9->Defense = 35;
	soldier_9->Resistance = 30;
	soldier_9->setScale(1.0f);
	soldier_9->setName("soldier_9");
	soldier_9->speed = 0.9;
	soldier_9->Attack_Ready = 0;
	sprBar_9 = Sprite::create("bar.png");
	sprBar_9->setScale(0.1f);
	soldier_9->addChild(sprBar_9);
	sprBlood_9 = Sprite::create("blood.png");
	progress_9 = ProgressTimer::create(sprBlood_9);
	progress_9->setType(ProgressTimer::Type::BAR);
	progress_9->setScale(0.1f);
	progress_9->setMidpoint(Point(0, 0.5));
	progress_9->setBarChangeRate(Point(1, 0));
	soldier_9->addChild(progress_9);
	sprBar_9->setPosition(Point(soldier_9->position.x, soldier_9->position.y + 45));
	progress_9->setPosition(Point(soldier_9->position.x, soldier_9->position.y + 45));
	soldier_9->setTag(9);
	background->addChild(soldier_9);

	_Death_9 = TimeCounter::create();
	this->addChild(_Death_9);
	_Attack_9 = TimeCounter::create();
	this->addChild(_Attack_9);
	_soldier_9 = Hero::createHeroSprite(Vec2(635, 485), 2, "stand", 6);
	_soldier_9->life = 0;
	_soldier_9->Able_To_Attack = 0;
	_soldier_9->MaxHP = 1000;
	_soldier_9->HP = 1000;
	_soldier_9->Attack = 70;
	_soldier_9->Attack_Speed = 2.0;
	_soldier_9->Defense = 35;
	_soldier_9->Resistance = 30;
	_soldier_9->setScale(1.0f);
	_soldier_9->setName("_soldier_9");
	_soldier_9->speed = 0.9;
	_soldier_9->Attack_Ready = 0;
	_sprBar_9 = Sprite::create("bar.png");
	_sprBar_9->setScale(0.1f);
	_soldier_9->addChild(_sprBar_9);
	_sprBlood_9 = Sprite::create("blood.png");
	_progress_9 = ProgressTimer::create(_sprBlood_9);
	_progress_9->setType(ProgressTimer::Type::BAR);
	_progress_9->setScale(0.1f);
	_progress_9->setMidpoint(Point(0, 0.5));
	_progress_9->setBarChangeRate(Point(1, 0));
	_soldier_9->addChild(_progress_9);
	_sprBar_9->setPosition(Point(_soldier_9->position.x, _soldier_9->position.y + 45));
	_progress_9->setPosition(Point(_soldier_9->position.x, _soldier_9->position.y + 45));
	_soldier_9->setTag(-9);
	background->addChild(_soldier_9);
	_soldier_9->setAction(4, "stand", 4, 6);
	//英雄技能
	if (hero->ID == 1) {

		Skill_Q = TimeCounter::create();

		this->addChild(Skill_Q);

		Skill_W = TimeCounter::create();

		this->addChild(Skill_W);

		Skill_R = TimeCounter::create();

		this->addChild(Skill_R);

		hero->Skill_Q_Cool_Down = 3;

		hero->Skill_W_Cool_Down = 10;

		hero->Skill_R_Cool_Down = 30;

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;

		hero->Skill_E_On_Release = 0;

		hero->Skill_R_On_Release = 0;

		hero->MaxHP = 1000;

		hero->MaxMP = 300;

		hero->HP = 1000;

		hero->MP = 300;

		hero->Attack = 70;

		hero->Attack_Speed = 3.5;

		hero->Attack_Range = 20;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 10;

		hero->Defense = 55;

		hero->Resistance = 35;

		hero->HP_Recover = 0.5;

		hero->MP_Recover = 0.15;

		this->addChild(hero);

	}
	if (hero->ID == 2) {

		Skill_Q = TimeCounter::create();

		this->addChild(Skill_Q);

		Skill_W = TimeCounter::create();

		this->addChild(Skill_W);

		Skill_E = TimeCounter::create();

		this->addChild(Skill_E);


		hero->Skill_Q_Cool_Down = 4;

		hero->Skill_W_Cool_Down = 10;

		hero->Skill_E_Cool_Down = 20;

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;

		hero->Skill_R_On_Release = 0;

		hero->MaxHP = 600;

		hero->MaxMP = 450;

		hero->HP = 600;

		hero->MP = 450;

		hero->Attack = 55;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 10;

		hero->Attack_Speed = 3.2;

		hero->Attack_Range = 100;

		hero->Defense = 30;

		hero->Resistance = 30;

		hero->HP_Recover = 0.1;

		hero->MP_Recover = 0.4;

		this->addChild(hero);

	}
	if (hero->ID == 3) {


		Skill_W = TimeCounter::create();

		this->addChild(Skill_W);

		Skill_E = TimeCounter::create();

		this->addChild(Skill_E);

		Skill_R = TimeCounter::create();

		this->addChild(Skill_R);

		hero->Skill_W_Cool_Down = 10;

		hero->Skill_E_Cool_Down = 15;

		hero->Skill_R_Cool_Down = 30;

		hero->Skill_Q_On_Release = 0;

		hero->Skill_W_On_Release = 0;

		hero->Skill_E_On_Release = 0;

		hero->Skill_R_On_Release = 0;

		hero->MaxHP = 650;

		hero->MaxMP = 300;

		hero->HP = 650;

		hero->MP = 300;

		hero->Attack = 70;

		hero->Skill_Enhance = 0;

		hero->Critical_Rate = 10;

		hero->Attack_Speed = 3.5;

		hero->Attack_Range = 100;

		hero->Defense = 40;

		hero->Resistance = 25;

		hero->HP_Recover = 0.3;

		hero->MP_Recover = 0.2;

		this->addChild(hero);

	}
	//防御塔
	Tower* tower1 = Tower::create();

	tower1->setTag(2);

	tower1->setPosition(Point(1800, 1000));//1800 1000
	TimeCounter* t1 = TimeCounter::create(); t1->setName("t");
	tower1->addChild(t1);
	background->addChild(tower1);

	tower.push_back(tower1);

	Tower* tower2 = Tower::create();

	tower2->setTag(3);
	TimeCounter* t2 = TimeCounter::create(); t2->setName("t");
	tower2->addChild(t2);
	tower2->setPosition(Point(1960, 1160));

	background->addChild(tower2);

	tower.push_back(tower2);

	Tower* tower3 = Tower::create();

	tower3->setTag(4);
	TimeCounter* t3 = TimeCounter::create(); t3->setName("t");
	tower3->addChild(t3);
	tower3->setPosition(Point(2220, 1255));

	background->addChild(tower3);

	tower.push_back(tower3);

	Tower* tower4 = Tower::create();

	tower4->setTag(5);

	tower4->setPosition(Point(2430, 1390));

	TimeCounter* t4 = TimeCounter::create(); t4->setName("t");

	background->addChild(tower4);

	tower.push_back(tower4);

	tower4->addChild(t4);

	Tower* tower5 = Tower::create();

	tower5->setTag(-2);

	tower5->setPosition(Point(1400, 780));

	TimeCounter* t5 = TimeCounter::create(); t5->setName("t");

	background->addChild(tower5);

	tower.push_back(tower5);

	tower5->addChild(t5);

	Tower* tower6 = Tower::create();

	tower6->setTag(-3);

	tower6->setPosition(Point(1100, 600));

	TimeCounter* t6 = TimeCounter::create(); t6->setName("t");

	background->addChild(tower6);

	tower.push_back(tower6);

	tower6->addChild(t6);

	Tower* tower7 = Tower::create();

	tower7->setTag(-4);

	tower7->setPosition(Point(850, 500));

	TimeCounter* t7 = TimeCounter::create(); t7->setName("t");

	background->addChild(tower7);

	tower.push_back(tower7);

	tower7->addChild(t7);

	Tower* tower8 = Tower::create();

	tower8->setTag(-5);

	tower8->setPosition(Point(650, 350));

	TimeCounter* t8 = TimeCounter::create(); t8->setName("t");

	background->addChild(tower8);

	tower.push_back(tower8);

	tower8->addChild(t8);

	level = to_string(hero->Level);

	label = Label::createWithTTF(level, "fonts/Marker Felt.ttf", 30);

	label->setColor(Color3B(0, 0, 0));

	label->setPosition(Point(hero->position.x - 35, hero->position.y + 43));

	label->setScale(0.3f);

	label->setName("lab");

	hero->addChild(label);

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
	hero->removeChildByName("lab");

	level = to_string(hero->Level);

	label = Label::createWithTTF(level, "fonts/Marker Felt.ttf", 30);

	label->setColor(Color3B(0, 0, 0));

	label->setPosition(Point(hero->position.x - 35, hero->position.y + 43));

	label->setScale(0.3f);

	label->setName("lab");

	hero->addChild(label);

	float coin = rand() % 100 + 1;
	if (coin <= hero->Critical_Rate)
	{
		hero->Critical = 1;
	}
	else
	{
		hero->Critical = 0;
	}
	hero->Attack_Cool_Down = 5 / (hero->Attack_Speed);

	progress->setPercentage((((float)hero->HP) / hero->MaxHP) * 100);

	progress2->setPercentage((((float)hero->MP) / hero->MaxMP) * 100);

	_progress->setPercentage((((float)_hero->HP) / _hero->MaxHP) * 100);

	_progress2->setPercentage((((float)_hero->MP) / _hero->MaxMP) * 100);

	progress_7->setPercentage((((float)soldier_7->HP) / soldier_7->MaxHP) * 100);
	progress_8->setPercentage((((float)soldier_8->HP) / soldier_8->MaxHP) * 100);
	progress_9->setPercentage((((float)soldier_9->HP) / soldier_9->MaxHP) * 100);
	_progress_7->setPercentage((((float)_soldier_7->HP) / _soldier_7->MaxHP) * 100);
	_progress_8->setPercentage((((float)_soldier_8->HP) / _soldier_8->MaxHP) * 100);
	_progress_9->setPercentage((((float)_soldier_9->HP) / _soldier_9->MaxHP) * 100);

	string level = to_string(hero->Level);

	label = Label::createWithTTF(level, "fonts/Marker Felt.ttf", 30);

	label->setColor(Color3B(0, 0, 0));

	label->setPosition(Point(hero->position.x - 110, hero->position.y + 75));

	//AI复活
	if (_hero->HP <= 0 && _heroLife == 0) {
		hero->kill++;
		hero->Exp += 200;
		hero->Money += 300;
		_hero->setVisible(false);
		_heroDeath->start();
		_heroLife = 1;
	}
	if (_heroLife == 1) {
		if (_heroDeath->getfCurTime() >= 10) {
			_hero->HP = _hero->MaxHP;
			_hero->MP = _hero->MaxMP;
			_heroLife = 0;

			_hero->setPosition(Vec2(2670, 1500) + background->getPosition());

			_hero->setVisible(true);
		}
	}
	//小兵复活
	if (soldier_7->HP <= 0 && soldier_7->life == 0) {
		soldier_7->setVisible(false);
		hero->Exp += 200;
		hero->Money += 30;
		Death_7->start();
		soldier_7->life = 1;
	}
	if (soldier_7->life == 1) {
		if (Death_7->getfCurTime() >= 5) {
			soldier_7->HP = soldier_7->MaxHP;
			soldier_7->life = 0;
			soldier_7->setPosition(Vec2(2430, 1345) + background->getPosition());
			soldier_7->setVisible(true);
		}
	}

	if (soldier_8->HP <= 0 && soldier_8->life == 0) {
		soldier_8->setVisible(false);
		hero->Exp += 200;
		hero->Money += 30;
		Death_8->start();
		soldier_8->life = 1;
	}
	if (soldier_8->life == 1) {
		if (Death_8->getfCurTime() >= 5) {
			soldier_8->HP = soldier_8->MaxHP;
			soldier_8->life = 0;
			soldier_8->setPosition(Vec2(2440, 1355) + background->getPosition());
			soldier_8->setVisible(true);
		}
	}

	if (soldier_9->HP <= 0 && soldier_9->life == 0) {
		soldier_9->setVisible(false);
		hero->Exp += 300;
		hero->Money += 50;
		Death_9->start();
		soldier_9->life = 1;
	}
	if (soldier_9->life == 1) {
		if (Death_9->getfCurTime() >= 5) {
			soldier_9->HP = soldier_9->MaxHP;
			soldier_9->life = 0;
			soldier_9->setPosition(Vec2(2450, 1365) + background->getPosition());
			soldier_9->setVisible(true);
		}
	}

	if (_soldier_7->HP <= 0 && _soldier_7->life == 0) {
		_soldier_7->setVisible(false);
		//_hero->Exp += 200;
		//_hero->Money += 30;
		_Death_7->start();
		_soldier_7->life = 1;
	}
	if (_soldier_7->life == 1) {
		if (_Death_7->getfCurTime() >= 5) {
			_soldier_7->HP = _soldier_7->MaxHP;
			_soldier_7->life = 0;
			_soldier_7->setPosition(Vec2(655, 505) + background->getPosition());
			_soldier_7->setVisible(true);
		}
	}

	if (_soldier_8->HP <= 0 && _soldier_8->life == 0) {
		_soldier_8->setVisible(false);
		//hero->Exp += 200;
		//hero->Money += 30;
		_Death_8->start();
		_soldier_8->life = 1;
	}
	if (_soldier_8->life == 1) {
		if (_Death_8->getfCurTime() >= 5) {
			_soldier_8->HP = _soldier_8->MaxHP;
			_soldier_8->life = 0;
			_soldier_8->setPosition(Vec2(645, 495) + background->getPosition());
			_soldier_8->setVisible(true);
		}
	}

	if (_soldier_9->HP <= 0 && _soldier_9->life == 0) {
		_soldier_9->setVisible(false);
		//hero->Exp += 300;
		//hero->Money += 50;
		_Death_9->start();
		_soldier_9->life = 1;
	}
	if (_soldier_9->life == 1) {
		if (_Death_9->getfCurTime() >= 5) {
			_soldier_9->HP = _soldier_9->MaxHP;
			_soldier_9->life = 0;
			_soldier_9->setPosition(Vec2(635, 485) + background->getPosition());
			_soldier_9->setVisible(true);
		}
	}
	//英雄
	if (hero->Level <= 18 && hero->Exp >= hero->MaxExp)
	{
		hero->Level++;
		hero->MaxExp += 100;
		hero->Attack += 5;
		hero->MaxHP += 20;
		hero->MaxMP += 10;
	}
	if (hero->HP > 0 && hero->life == 1)
	{
		hero->setVisible(true);
	}
	if (hero->HP <= 0 && hero->life == 1) {
		hero->dead++;
		DeadTime->start();
		hero->life = 0;
	}
	if (hero->life == 0) {

		hero->setVisible(false);

		if (hero->ID == 1)
		{
			hero->Skill_E_On_Release = 0;
		}
		if (hero->ID == 3)
		{
			hero->Skill_E_On_Release = 0;
		}
		if ((DeadTime->getfCurTime()) >= 10) {
			background->setPosition(0, 0);

			hero->life = 1;

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
		switch (hero->Skill_Q_On_Release)
		{
		case 1: {
			Skill_Q->start();

			Effect_Q->setPosition(Point(400, 200));

			this->addChild(Effect_Q);

			hero->Skill_Q_On_Release = 2;

			break;
		}

		case 2: {
			if (Skill_Q->getfCurTime() < 0.5)
			{
				for (int j = 0; j < 1000; j++) {
					if (j >= 6)
					{
						auto target = (Hero*)background->getChildByTag(j);
						Point Target;
						switch (j) {
						case 6: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2670, 1500);
							break;
						}
						case 7: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2430, 1345);
							break;
						}
						case 8: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2440, 1355);
							break;
						}
						case 9: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2450, 1365);
							break;
						}
						}
						if (target == NULL)continue;
						if (Target.x <= 450 && Target.x >= 350)
						{
							if (Target.y <= 250 && Target.y >= 150) {
								target->HP -= 2 * (1 + hero->Level * 0.2 + hero->Attack * 0.15);
							}
						}
					}
					else
					{
						auto target = (Tower*)background->getChildByTag(j);
						if (target == NULL)continue;
						if (target->getPosition().x + background->getPosition().x <= 450 && target->getPosition().x + background->getPosition().x >= 350)
						{
							if (target->getPosition().y + background->getPosition().y <= 250 && target->getPosition().y + background->getPosition().y >= 150) {
								target->HP -= 2 * (1 + hero->Level * 0.2 + hero->Attack * 0.15);
							}
						}
					}
				}
			}
			else if (Skill_Q->getfCurTime() >= 0.5) {
				hero->Skill_Q_On_Release = 3;
				this->removeChild(Effect_Q);
			}
			break;
		}

		case 3: {
			if (Skill_Q->getfCurTime() >= hero->Skill_Q_Cool_Down) {
				hero->Skill_Q_On_Release = 0;
			}
			break;
		}
		}
		//英雄W技能
		switch (hero->Skill_W_On_Release)
		{
		case 1: {
			Skill_W->start();

			hero->Skill_W_On_Release = 2;

			break;
		}

		case 2: {
			if (Skill_W->getfCurTime() < 5)
			{
				for (int j = 0; j < 1000; j++) {
					if (j >= 6) {
						auto target = (Hero*)background->getChildByTag(j);
						Point Target;
						switch (j) {
						case 6: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2670, 1500);
							break;
						}
						case 7: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2430, 1345);
							break;
						}
						case 8: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2440, 1355);
							break;
						}
						case 9: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2450, 1365);
							break;
						}
						}
						if (target == NULL)continue;
						if (Target.x <= 450 && Target.x >= 350)
						{
							if (Target.y <= 250 && Target.y >= 150) {
								target->HP -= 5 * (1 + hero->Level * 0.1 + hero->Skill_Enhance * 0.15);
								if (hero->HP <= hero->MaxHP)
								{
									hero->HP += 2;
								}
							}
						}
					}
					else {
						auto target = (Tower*)background->getChildByTag(j);
						if (target == NULL)continue;
						if (target->getPosition().x + background->getPosition().x <= 450 && target->getPosition().x + background->getPosition().x >= 350)
						{
							if (target->getPosition().y + background->getPosition().y <= 250 && target->getPosition().y + background->getPosition().y >= 150) {
								target->HP -= 2 * (1 + hero->Level * 0.15 + hero->Skill_Enhance * 0.35);
								if (hero->HP < hero->MaxHP) {
									hero->HP += 5;
								}
							}
						}
					}
				}
			}
			else if (Skill_W->getfCurTime() >= 5) {
				hero->Skill_W_On_Release = 3;
				this->removeChild(Effect_W);
			}
			break;
		}

		case 3: {
			if (Skill_W->getfCurTime() >= hero->Skill_W_Cool_Down) {
				hero->Skill_W_On_Release = 0;
			}
			break;
		}
		}
		//英雄E技能
		switch (hero->Skill_E_On_Release)
		{
		case 1: {

			hero->HP -= 3;

			break;
		}
		}
		//英雄R技能
		switch (hero->Skill_R_On_Release)
		{
		case 1: {
			Skill_R->start();
			hero->Skill_R_On_Release = 2;
			hero->HP_Recover += 15 * (1 + hero->Level / 10);
			hero->Defense += 35 * (1 + hero->Level / 10);
			hero->Resistance += 35 * (1 + hero->Level / 10);
			hero->Attack_Speed *= 1.75;
			break;
		}
		case 2: {

			if (Skill_R->getfCurTime() >= 10) {
				hero->Skill_R_On_Release = 2;
				hero->HP_Recover -= 15 * (1 + hero->Level / 10);
				hero->Defense -= 35 * (1 + hero->Level / 10);
				hero->Resistance -= 35 * (1 + hero->Level / 10);
				hero->Attack_Speed /= hero->Attack * 1.75;
				hero->Skill_R_On_Release = 3;
			}
			break;
		}
		case 3: {
			if (Skill_R->getfCurTime() >= hero->Skill_R_Cool_Down) {
				hero->Skill_R_On_Release = 0;
			}
			break;
		}
		}
	}
	if (hero->ID == 2) {
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
		switch (hero->Skill_Q_On_Release)
		{
		case 1: {
			Skill_Q->start();

			hero->Skill_Q_On_Release = 2;

			break;
		}
		case 2: {
			if (Skill_Q->getfCurTime() >= hero->Skill_Q_Cool_Down)
			{
				hero->Skill_Q_On_Release = 0;
			}
			break;
		}
		}

		//英雄W技能
		switch (hero->Skill_W_On_Release)
		{
		case 1: {
			Skill_W->start();
			hero->Skill_W_On_Release = 2;
			break;
		}
		case 2: {
			if (Skill_W->getfCurTime() < 3) {
				for (int j = 0; j < 1000; j++) {
					if (j >= 6) {
						auto target = (Hero*)background->getChildByTag(j);
						Point Target;
						switch (j) {
						case 6: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2670, 1500);
							break;
						}
						case 7: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2430, 1345);
							break;
						}
						case 8: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2440, 1355);
							break;
						}
						case 9: {
							Target = background->convertToWorldSpaceAR(target->getPosition()) + Point(2450, 1365);
							break;
						}
						}
						if (target == NULL)continue;
						if (Target.x <= Effect_W->getPosition().x + 100 && Target.x >= Effect_W->getPosition().x - 100) {
							if (Target.y <= Effect_W->getPosition().y + 100 && Target.y >= Effect_W->getPosition().y - 100) {
								target->HP -= 5 * (1 + hero->Level * 0.15 + hero->Skill_Enhance / 100);
							}
						}
					}
					else {
						auto target = (Tower*)background->getChildByTag(j);
						if (target == NULL)continue;
						if (target->getPosition().x + background->getPosition().x <= Effect_W->getPosition().x + 100 && target->getPosition().x + background->getPosition().x >= Effect_W->getPosition().x - 100) {
							if (target->getPosition().y + background->getPosition().y <= Effect_W->getPosition().y + 100 && target->getPosition().y + background->getPosition().y >= Effect_W->getPosition().y - 100) {
								target->HP -= 10 * (1 + hero->Level * 0.35 + hero->Skill_Enhance / 100);
							}
						}
					}
				}
			}
			if (Skill_W->getfCurTime() >= 3)
			{
				this->removeChild(Effect_W);
				hero->Skill_W_On_Release = 3;
			}
			break;
		}
		case 3: {
			if (Skill_W->getfCurTime() >= hero->Skill_W_Cool_Down)
			{
				hero->Skill_W_On_Release = 0;
			}
		}
		}
		//英雄E技能
		switch (hero->Skill_E_On_Release)
		{
		case 1: {
			Skill_E->start();
			hero->HP_Recover += 1.5 * (1 + hero->Level * 0.2);
			hero->Skill_Enhance += 300;
			hero->Skill_E_On_Release = 2;
			break;
		}
		case 2: {
			if (Skill_E->getfCurTime() >= 5)
			{
				hero->HP_Recover -= 1.5 * (1 + hero->Level * 0.2);
				hero->Skill_Enhance -= 300;
				hero->Skill_E_On_Release = 3;
			}
			break;
		}
		case 3: {
			if (Skill_E->getfCurTime() >= hero->Skill_E_Cool_Down) {
				hero->Skill_E_On_Release = 0;
			}
			break;
		}
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
		if (hero->MP < 8)
		{
			hero->Skill_Q_On_Release = 0;
		}

		//英雄W技能
		switch (hero->Skill_W_On_Release)
		{
		case 1: {
			Skill_W->start();
			hero->Attack_Speed += 4;
			hero->Skill_W_On_Release = 2;
			break;
		}
		case 2: {
			if (Skill_W->getfCurTime() >= 3) {
				hero->Attack_Speed -= 4;
				hero->Skill_W_On_Release = 3;
			}
			break;
		}
		case 3: {
			if (Skill_W->getfCurTime() >= hero->Skill_W_Cool_Down)
			{
				hero->Skill_W_On_Release = 0;
			}
			break;
		}
		}
		//英雄E技能
		switch (hero->Skill_E_On_Release)
		{
		case 1: {
			Skill_E->start();
			hero->Skill_E_On_Release = 2;
			break;
		}
		case 2: {
			hero->setVisible(false);
			if (Skill_E->getfCurTime() >= hero->Skill_E_Cool_Down) {
				hero->Skill_E_On_Release = 3;
				break;
			}
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
			if (Skill_R->getfCurTime() >= hero->Skill_R_Cool_Down)
			{
				hero->Skill_R_On_Release = 0;
			}
			break;
		}
		}
	}

	hero->Money++;



	Point temp;

	temp.x = pos.x;

	temp.y = pos.y;

	if ((temp.x - hero->position.x) * (temp.x - hero->position.x) + (temp.y - hero->position.y) * (temp.y - hero->position.y) <= (1 / hero->speed) * (1 / hero->speed))

	{

		hero->isRun = false;

		hero->setAction(hero->direction, "stand", 4, hero->ID);

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

	if (pos == Point::ZERO)

	{

		hero->isRun = false;

		hero->setAction(hero->direction, "stand", 4, hero->ID);

		return;

	}



	if (hero->isRun == false)

	{

		hero->isRun = true;

		nowDirection = hero->direction;

		hero->setAction(hero->direction, "run", 4, hero->ID);

	}

	else if (hero->isRun == true)

	{

		if (nowDirection != hero->direction)

		{

			nowDirection = hero->direction;

			hero->setAction(hero->direction, "run", 2, hero->ID);

		}

	}

	float r = (sqrt(((temp.x - hero->position.x) * (temp.x - hero->position.x)) + ((temp.y - hero->position.y) * (temp.y - hero->position.y)))) / ((hero->speed) * 5);

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

	float m = background->getPositionX();

	float n = background->getPositionY();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//AI移动和攻击
	Vec2 point = _hero->getParent()->convertToWorldSpaceAR(_hero->getPosition()) + Point(2670, 1500);

	float r4 = sqrt((point.x - hero->position.x) * (point.x - hero->position.x) + (point.y - hero->position.y) * (point.y - hero->position.y));
	int flag1 = 0;//是否打小兵
	int flag2 = 0;//是否打英雄


	for (int i = -9; i <= -7; i++)
	{
		Hero* aim = (Hero*)background->getChildByTag(i);
		Point point0;
		switch (i)
		{
		case -9:
			point0 = Point(635, 485);
			break;
		case -8:
			point0 = Point(645, 495);
			break;
		case -7:
			point0 = Point(655, 505);
			break;
		}
		Point _heroPos = background->convertToWorldSpaceAR(_hero->getPosition()) + Point(2670, 1500);
		Point points = background->convertToWorldSpaceAR(aim->getPosition()) + point0;
		float r = (_heroPos.x - points.x) * (_heroPos.x - points.x) + (_heroPos.y - points.y) * (_heroPos.y - points.y);
		if (r <= 10000 && aim->HP > 0)
		{
			flag1 = 1;
			if (_heroAttack->getfCurTime() == 0)
				_heroAttack->start();
			if (_heroAttack->getfCurTime() >= 1 && _heroLife == 0)
			{
				_hero->setAction(1, "attack", 4, _hero->ID);
				aim->HP -= _hero->Attack;
				_heroAttack->start();

				break;
			}
		}
	}

	if (r4 >= 50 && flag1 == 0 && hero->HP > 0)
	{
		_hero->setPosition(Point(_hero->getPosition().x + 2 * (hero->position.x - point.x) / r4, _hero->getPosition().y + 2 * (hero->position.y - point.y) / r4));
	}


	else if (flag1 == 0)
	{
		if (_heroAttack->getfCurTime() == 0)
			_heroAttack->start();
		if (_heroAttack->getfCurTime() >= 1 && _heroLife == 0)
		{
			_hero->setAction(1, "attack", 4, _hero->ID);
			hero->HP -= _hero->Attack;
			_heroAttack->start();

		}
	}


	//小兵移动和攻击
	Point point_7 = soldier_7->getPosition() + Point(2430, 1345);
	Point point_8 = soldier_8->getPosition() + Point(2440, 1355);
	Point point_9 = soldier_9->getPosition() + Point(2450, 1365);
	Point _point_7 = _soldier_7->getPosition() + Point(655, 505);
	Point _point_8 = _soldier_8->getPosition() + Point(645, 495);
	Point _point_9 = _soldier_9->getPosition() + Point(635, 485);
	Point real_point_7 = convertToWorldSpaceAR(soldier_7->getPosition()) + Point(2430, 1345);
	Point real_point_8 = convertToWorldSpaceAR(soldier_8->getPosition()) + Point(2440, 1355);
	Point real_point_9 = convertToWorldSpaceAR(soldier_9->getPosition()) + Point(2450, 1365);
	Point _real_point_7 = convertToWorldSpaceAR(_soldier_7->getPosition()) + Point(655, 505);
	Point _real_point_8 = convertToWorldSpaceAR(_soldier_8->getPosition()) + Point(645, 495);
	Point _real_point_9 = convertToWorldSpaceAR(_soldier_9->getPosition()) + Point(635, 485);
	for (int ix = -2; ix >= -5; ix--) {
		auto Aim_Tower = (Tower*)background->getChildByTag(ix);
		if (Aim_Tower->HP <= 0) {
			continue;
		}
		else {
			Point Aim_Position;
			Aim_Position = Aim_Tower->getPosition();
			float r7 = sqrt((Aim_Position.x - point_7.x) * (Aim_Position.x - point_7.x) + (Aim_Position.y - point_7.y) * (Aim_Position.y - point_7.y));
			float r8 = sqrt((Aim_Position.x - point_8.x) * (Aim_Position.x - point_8.x) + (Aim_Position.y - point_8.y) * (Aim_Position.y - point_8.y));
			float r9 = sqrt((Aim_Position.x - point_9.x) * (Aim_Position.x - point_9.x) + (Aim_Position.y - point_9.y) * (Aim_Position.y - point_9.y));
			int stop_7 = 0;
			int stop_8 = 0;
			int stop_9 = 0;
			if (r7 >= 50) {
				for (int iy = -7; iy >= -9; iy--) {
					Point Enemy_Position;
					switch (iy)
					{
					case -7: {
						Enemy_Position = _real_point_7;
						break;
					}
					case -8: {
						Enemy_Position = _real_point_8;
						break;
					}
					case -9: {
						Enemy_Position = _real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - real_point_7.x) * (Enemy_Position.x - real_point_7.x) + (Enemy_Position.y - real_point_7.y) * (Enemy_Position.y - real_point_7.y));
						if (distance <= 50 && enemy->life == 0) {
							stop_7++;
							if (soldier_7->Able_To_Attack == 0 && soldier_7->life == 0) {
								soldier_7->setAction(1, "attack", 4, 4);
								enemy->HP -= soldier_7->Attack;
								soldier_7->Able_To_Attack = 1;
								Attack_7->start();
							}
							else {
								if (Attack_7->getfCurTime() >= 1) {
									soldier_7->setAction(1, "run", 4, 4);
									soldier_7->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (stop_7 == 0) {
					soldier_7->setPosition(Point(soldier_7->getPosition().x + (Aim_Position.x - point_7.x) / r7, soldier_7->getPosition().y + (Aim_Position.y - point_7.y) / r7));
				}
			}
			else {
				if (soldier_7->Able_To_Attack == 0 && soldier_7->life == 0) {
					soldier_7->setAction(1, "attack", 4, 4);
					Aim_Tower->HP -= soldier_7->Attack;
					soldier_7->Able_To_Attack = 1;
					Attack_7->start();
				}
				else {
					if (Attack_7->getfCurTime() >= 1) {
						soldier_7->setAction(1, "run", 4, 4);
						soldier_8->setAction(1, "run", 4, 5);
						soldier_9->setAction(1, "run", 4, 6);
						soldier_7->Able_To_Attack = 0;
					}
				}
			}
			if (r8 >= 80) {
				for (int iy = -7; iy >= -9; iy--) {
					Point Enemy_Position;
					switch (iy)
					{
					case -7: {
						Enemy_Position = _real_point_7;
						break;
					}
					case -8: {
						Enemy_Position = _real_point_8;
						break;
					}
					case -9: {
						Enemy_Position = _real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - real_point_8.x) * (Enemy_Position.x - real_point_8.x) + (Enemy_Position.y - real_point_8.y) * (Enemy_Position.y - real_point_8.y));
						if (distance <= 80 && enemy->life == 0) {
							stop_8++;
							if (soldier_8->Able_To_Attack == 0 && soldier_8->life == 0) {
								soldier_8->setAction(1, "attack", 4, 5);
								enemy->HP -= soldier_8->Attack;
								soldier_8->Able_To_Attack = 1;
								Attack_8->start();
							}
							else {
								if (Attack_8->getfCurTime() >= 1) {
									soldier_8->setAction(1, "run", 4, 5);
									soldier_8->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (stop_8 == 0) {
					soldier_8->setPosition(Point(soldier_8->getPosition().x + (Aim_Position.x - point_8.x) / r8, soldier_8->getPosition().y + (Aim_Position.y - point_8.y) / r8));
				}
			}
			else {
				if (soldier_8->Able_To_Attack == 0 && soldier_8->life == 0) {
					soldier_8->setAction(1, "attack", 4, 5);
					Aim_Tower->HP -= soldier_8->Attack;
					soldier_8->Able_To_Attack = 1;
					Attack_8->start();
				}
				else if (soldier_8->Able_To_Attack == 1) {
					if (Attack_8->getfCurTime() >= 1) {
						soldier_8->Able_To_Attack = 0;
					}
				}
			}
			if (r9 >= 80) {
				for (int iy = -7; iy >= -9; iy--) {
					Point Enemy_Position;
					switch (iy)
					{
					case -7: {
						Enemy_Position = _real_point_7;
						break;
					}
					case -8: {
						Enemy_Position = _real_point_8;
						break;
					}
					case -9: {
						Enemy_Position = _real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - real_point_9.x) * (Enemy_Position.x - real_point_9.x) + (Enemy_Position.y - real_point_9.y) * (Enemy_Position.y - real_point_9.y));
						if (distance <= 80 && enemy->life == 0) {
							stop_9++;
							if (soldier_9->Able_To_Attack == 0 && soldier_9->life == 0) {
								soldier_9->setAction(1, "attack", 4, 6);
								enemy->HP -= soldier_9->Attack;
								soldier_9->Able_To_Attack = 1;
								Attack_9->start();
							}
							else {
								if (Attack_9->getfCurTime() >= 1) {
									soldier_9->setAction(1, "run", 4, 6);
									soldier_9->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (stop_9 == 0) {
					soldier_9->setPosition(Point(soldier_9->getPosition().x + (Aim_Position.x - point_9.x) / r9, soldier_9->getPosition().y + (Aim_Position.y - point_9.y) / r9));
				}
			}
			else {
				if (soldier_9->Able_To_Attack == 0 && soldier_9->life == 0) {
					soldier_9->setAction(1, "attack", 4, 6);
					Aim_Tower->HP -= soldier_9->Attack;
					soldier_9->Able_To_Attack = 1;
					Attack_9->start();
				}
				else if (soldier_9->Able_To_Attack == 1) {
					if (Attack_9->getfCurTime() >= 1) {
						soldier_9->Able_To_Attack = 0;
					}
				}
			}
			break;
		}
	}
	for (int ix = 2; ix <= 5; ix++) {
		auto Aim_Tower = (Tower*)background->getChildByTag(ix);
		if (Aim_Tower->HP <= 0) {
			continue;
		}
		else {
			Point Aim_Position;
			Aim_Position = Aim_Tower->getPosition();
			float _r7 = sqrt((Aim_Position.x - _point_7.x) * (Aim_Position.x - _point_7.x) + (Aim_Position.y - _point_7.y) * (Aim_Position.y - _point_7.y));
			float _r8 = sqrt((Aim_Position.x - _point_8.x) * (Aim_Position.x - _point_8.x) + (Aim_Position.y - _point_8.y) * (Aim_Position.y - _point_8.y));
			float _r9 = sqrt((Aim_Position.x - _point_9.x) * (Aim_Position.x - _point_9.x) + (Aim_Position.y - _point_9.y) * (Aim_Position.y - _point_9.y));
			int _stop_7 = 0;
			int _stop_8 = 0;
			int _stop_9 = 0;
			if (_r7 >= 50) {
				for (int iy = 7; iy <= 9; iy++) {
					Point Enemy_Position;
					switch (iy)
					{
					case 7: {
						Enemy_Position = real_point_7;
						break;
					}
					case 8: {
						Enemy_Position = real_point_8;
						break;
					}
					case 9: {
						Enemy_Position = real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - _real_point_7.x) * (Enemy_Position.x - _real_point_7.x) + (Enemy_Position.y - _real_point_7.y) * (Enemy_Position.y - _real_point_7.y));
						if (distance <= 50 && enemy->life == 0) {
							_stop_7++;
							if (_soldier_7->Able_To_Attack == 0 && _soldier_7->life == 0) {
								_soldier_7->setAction(4, "attack", 4, 4);
								enemy->HP -= _soldier_7->Attack;
								_soldier_7->Able_To_Attack = 1;
								_Attack_7->start();
							}
							else {
								if (_Attack_7->getfCurTime() >= 1) {
									_soldier_7->setAction(4, "run", 4, 4);
									_soldier_7->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (_stop_7 == 0) {
					_soldier_7->setPosition(Point(_soldier_7->getPosition().x + (Aim_Position.x - _point_7.x) / _r7, _soldier_7->getPosition().y + (Aim_Position.y - _point_7.y) / _r7));
				}
			}
			else {
				if (_soldier_7->Able_To_Attack == 0 && _soldier_7->life == 0) {
					_soldier_7->setAction(4, "attack", 4, 4);
					Aim_Tower->HP -= _soldier_7->Attack;
					_soldier_7->Able_To_Attack = 1;
					_Attack_7->start();
				}
				else {
					if (_Attack_7->getfCurTime() >= 1) {
						_soldier_7->setAction(4, "run", 4, 4);
						_soldier_8->setAction(4, "run", 4, 5);
						_soldier_9->setAction(4, "run", 4, 6);
						_soldier_7->Able_To_Attack = 0;
					}
				}
			}
			if (_r8 >= 80) {
				for (int iy = 7; iy <= 9; iy++) {
					Point Enemy_Position;
					switch (iy)
					{
					case 7: {
						Enemy_Position = real_point_7;
						break;
					}
					case 8: {
						Enemy_Position = real_point_8;
						break;
					}
					case 9: {
						Enemy_Position = real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - _real_point_8.x) * (Enemy_Position.x - _real_point_8.x) + (Enemy_Position.y - _real_point_8.y) * (Enemy_Position.y - _real_point_8.y));
						if (distance <= 80 && enemy->life == 0) {
							_stop_8++;
							if (_soldier_8->Able_To_Attack == 0 && _soldier_8->life == 0) {
								_soldier_8->setAction(4, "attack", 4, 5);
								enemy->HP -= _soldier_8->Attack;
								_soldier_8->Able_To_Attack = 1;
								_Attack_8->start();
							}
							else {
								if (_Attack_8->getfCurTime() >= 1) {
									_soldier_8->setAction(4, "run", 4, 5);
									_soldier_8->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (_stop_8 == 0) {
					_soldier_8->setPosition(Point(_soldier_8->getPosition().x + (Aim_Position.x - _point_8.x) / _r8, _soldier_8->getPosition().y + (Aim_Position.y - _point_8.y) / _r8));
				}
			}
			else {
				if (_soldier_8->Able_To_Attack == 0 && _soldier_8->life == 0) {
					_soldier_8->setAction(4, "attack", 4, 5);
					Aim_Tower->HP -= _soldier_8->Attack;
					_soldier_8->Able_To_Attack = 1;
					_Attack_8->start();
				}
				else if (_soldier_8->Able_To_Attack == 1) {
					if (_Attack_8->getfCurTime() >= 1) {
						_soldier_8->Able_To_Attack = 0;
					}
				}
			}
			if (_r9 >= 80) {
				for (int iy = 7; iy <= 9; iy++) {
					Point Enemy_Position;
					switch (iy)
					{
					case 7: {
						Enemy_Position = real_point_7;
						break;
					}
					case 8: {
						Enemy_Position = real_point_8;
						break;
					}
					case 9: {
						Enemy_Position = real_point_9;
						break;
					}
					}
					auto enemy = (Hero*)background->getChildByTag(iy);
					if (enemy->HP <= 0) {
						continue;
					}
					else {
						float distance = sqrt((Enemy_Position.x - _real_point_9.x) * (Enemy_Position.x - _real_point_9.x) + (Enemy_Position.y - _real_point_9.y) * (Enemy_Position.y - _real_point_9.y));
						if (distance <= 80 && enemy->life == 0) {
							_stop_9++;
							if (_soldier_9->Able_To_Attack == 0 && _soldier_9->life == 0) {
								_soldier_9->setAction(4, "attack", 4, 6);
								enemy->HP -= _soldier_9->Attack;
								_soldier_9->Able_To_Attack = 1;
								_Attack_9->start();
							}
							else {
								if (_Attack_9->getfCurTime() >= 1) {
									_soldier_9->setAction(4, "run", 4, 6);
									_soldier_9->Able_To_Attack = 0;
								}
							}
							break;
						}
					}
				}
				if (_stop_9 == 0) {
					_soldier_9->setPosition(Point(_soldier_9->getPosition().x + (Aim_Position.x - _point_9.x) / _r9, _soldier_9->getPosition().y + (Aim_Position.y - _point_9.y) / _r9));
				}
			}
			else {
				if (_soldier_9->Able_To_Attack == 0 && _soldier_9->life == 0) {
					_soldier_9->setAction(4, "attack", 4, 6);
					Aim_Tower->HP -= _soldier_9->Attack;
					_soldier_9->Able_To_Attack = 1;
					_Attack_9->start();
				}
				else if (_soldier_9->Able_To_Attack == 1) {
					if (_Attack_9->getfCurTime() >= 1) {
						_soldier_9->Able_To_Attack = 0;
					}
				}
			}
			break;
		}
	}
	auto sp1 = this->getChildByTag(200);

	auto effect_w = this->getChildByName("explosion");

	auto bgPoint = sp1->getPosition();

	auto remPoint = bgPoint;
	auto flag = 0;

	Point egPoint;
	if (effect_w != NULL)
		egPoint = effect_w->getPosition() - bgPoint;

	auto bgSize = sp1->getContentSize();

	bgPoint = Point(bgPoint.x - (temp.x - hero->position.x) / r, bgPoint.y - (temp.y - hero->position.y) / r);

	auto color = getColor(hero->position.x - (int)bgPoint.x, hero->position.y - (int)bgPoint.y);

	if (color.r < 10 && color.g < 10 && color.b>250)
	{
		bgPoint = remPoint;
		flag = 1;
	}
	if ((temp.x - hero->position.x) * (temp.x - hero->position.x) + (temp.y - hero->position.y) * (temp.y - hero->position.y) <= 100 * hero->speed * hero->speed)
	{
		temp = hero->position;
	}

	else if (bgPoint.y <= 0 && bgPoint.x <= 0 && bgPoint.x + bgSize.width >= visibleSize.width && bgPoint.y + bgSize.height >= visibleSize.height)

	{
		sp1->setPosition(bgPoint);
	}
	if (effect_w != NULL)
		effect_w->setPosition(sp1->getPosition() + egPoint);

	for (int i = 0; i < tower.size(); i++)
	{
		TimeCounter* t = (TimeCounter*)tower[i]->getChildByName("t");
		tower[i]->progress->setPercentage((((float)tower[i]->HP) / tower[i]->MaxHP) * 100);
		if (tower[i]->HP <= 0)
		{
			if (tower[i]->getTag() == 5)
				win();
			if (tower[i]->getTag() == -5)
				lose();
			tower[i]->sprBar->setVisible(false);
			continue;
		}

		if (tower[i]->getTag() > 0)
		{
			int flag = 0;
			auto bullet0 = Sprite::create("towerbullet.png");

			bullet0->setPosition(tower[i]->getPosition() + background->getPosition());

			bullet0->setScale(0.4f);

			for (int j = -9; j <= -7; j++)
			{
				Hero* aim = (Hero*)background->getChildByTag(j);
				Point point0;
				switch (j)
				{
				case -9:
					point0 = Point(635, 485);
					break;
				case -8:
					point0 = Point(645, 495);
					break;
				case -7:
					point0 = Point(655, 505);
					break;
				}
				Point _heroPos = background->convertToWorldSpaceAR(aim->getPosition()) + point0;
				float r = (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) * (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) + (_heroPos.y - tower[i]->getPositionY() - background->getPositionY()) * (_heroPos.y - tower[i]->getPositionY() - background->getPositionY());

				if (r <= 10000 && aim->HP > 0)
				{
					tower[i]->isAttack = 1;
					flag = 1;
					if (t->getfCurTime() == 0)
						t->start();
					if (t->getfCurTime() >= 1)
					{

						switch (j)
						{
						case -9:
							this->addChild(bullet0);
							bullett9.push_back(bullet0);
							break;
						case -8:
							this->addChild(bullet0);
							bullett8.push_back(bullet0);
							break;
						case -7:
							this->addChild(bullet0);
							bullett7.push_back(bullet0);
							break;
						}
						t->start();
					}
				}
			}
			if (flag == 0 && hero->HP > 0)
			{


				float r = (hero->position.x - tower[i]->getPositionX() - background->getPositionX()) * (hero->position.x - tower[i]->getPositionX() - background->getPositionX()) + (hero->position.y - tower[i]->getPositionY() - background->getPositionY()) * (hero->position.y - tower[i]->getPositionY() - background->getPositionY());

				if (r <= 10000)
				{
					if (t->getfCurTime() == 0)
						t->start();
					if (t->getfCurTime() >= 1)
					{
						this->addChild(bullet0);
						bullett.push_back(bullet0);
						t->start();
					}

				}
			}

		}
		else
		{
			int flag = 0;
			auto bullet0 = Sprite::create("towerbullet.png");

			bullet0->setPosition(tower[i]->getPosition() + background->getPosition());

			//this->addChild(bullet0);

			bullet0->setScale(0.4f);
			for (int j = 7; j <= 9; j++)
			{
				Hero* aim = (Hero*)background->getChildByTag(j);
				Point point0;
				switch (j)
				{
				case 9:
					point0 = Point(2450, 1365);
					break;
				case 8:
					point0 = Point(2440, 1355);
					break;
				case 7:
					point0 = Point(2430, 1345);
					break;
				}
				Point _heroPos = background->convertToWorldSpaceAR(aim->getPosition()) + point0;
				float r = (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) * (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) + (_heroPos.y - tower[i]->getPositionY() - background->getPositionY()) * (_heroPos.y - tower[i]->getPositionY() - background->getPositionY());


				if (r <= 10000 && aim->HP > 0)
				{
					tower[i]->isAttack = 1;
					flag = 1;
					if (t->getfCurTime() == 0)
						t->start();
					if (t->getfCurTime() >= 1)
					{

						switch (j)
						{
						case 9:
							this->addChild(bullet0);
							_bullett9.push_back(bullet0);
							break;
						case 8:
							this->addChild(bullet0);
							_bullett8.push_back(bullet0);
							break;
						case 7:
							this->addChild(bullet0);
							_bullett7.push_back(bullet0);
							break;
						}
						t->start();
					}
				}
			}
			if (flag == 0 && _hero->HP > 0)
			{
				Point _heroPos = background->convertToWorldSpaceAR(_hero->getPosition()) + Point(2670, 1500);
				float r = (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) * (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) + (_heroPos.y - tower[i]->getPositionY() - background->getPositionY()) * (_heroPos.y - tower[i]->getPositionY() - background->getPositionY());

				if (r <= 10000 && _hero->HP > 0)
				{
					if (t->getfCurTime() == 0)
						t->start();
					if (t->getfCurTime() >= 1)
					{
						this->addChild(bullet0);
						_bullett.push_back(bullet0);
						t->start();
					}
				}
			}

		}
		Point _heroPos = background->convertToWorldSpaceAR(_hero->getPosition()) + Point(2670, 1500);

		float r1 = (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) * (_heroPos.x - tower[i]->getPositionX() - background->getPositionX()) + (_heroPos.y - tower[i]->getPositionY() - background->getPositionY()) * (_heroPos.y - tower[i]->getPositionY() - background->getPositionY());
		float r2 = (hero->position.x - tower[i]->getPositionX() - background->getPositionX()) * (hero->position.x - tower[i]->getPositionX() - background->getPositionX()) + (hero->position.y - tower[i]->getPositionY() - background->getPositionY()) * (hero->position.y - tower[i]->getPositionY() - background->getPositionY());
	}
	pos.x = pos.x - (temp.x - hero->position.x) / r;

	pos.y = pos.y - (temp.y - hero->position.y) / r;

	if (bullet.size() >= 1)
	{
		for (auto it = bullet.begin(); it != bullet.end();)
		{

			if (choice >= 6)
			{
				auto aim = (Hero*)background->getChildByTag(choice);
				Point aimPoint;
				switch (choice) {
				case 6: {
					aimPoint = background->convertToWorldSpaceAR(aim->getPosition()) + Point(2670, 1500);
					break;
				}
				case 7: {
					aimPoint = background->convertToWorldSpaceAR(aim->getPosition()) + Point(2430, 1345);
					break;
				}
				case 8: {
					aimPoint = background->convertToWorldSpaceAR(aim->getPosition()) + Point(2440, 1355);
					break;
				}
				case 9: {
					aimPoint = background->convertToWorldSpaceAR(aim->getPosition()) + Point(2450, 1365);
					break;
				}
				}
				if (aim == NULL)break;
				Point pos1 = (*it)->getPosition();

				(*it)->setRotation(360 - 180 / 3.14 * atan2((aimPoint.y - (*it)->getPositionY()), (aimPoint.x - (*it)->getPositionX())));

				float r2 = sqrt((pos1.x - aimPoint.x) * (pos1.x - aimPoint.x) + (pos1.y - aimPoint.y) * (pos1.y - aimPoint.y));

				float distance = (hero->getPosition().x - aimPoint.x) * (hero->getPosition().x - aimPoint.x) + (hero->getPosition().y - aimPoint.y) * (hero->getPosition().y - aimPoint.y);

				if (distance <= (hero->Attack_Range * hero->Attack_Range))
				{
					hero->Able_To_Attack = 1;
				}
				else
				{
					hero->Able_To_Attack = 0;
				}

				(*it)->setPosition(Point(pos1.x + 20 * (aimPoint.x - pos1.x) / r2, pos1.y + 20 * (aimPoint.y - pos1.y) / r2));



				if (r2 <= 10)
				{
					if ((*it)->getName() == "attack")
					{
						if (hero->Critical == 1)
						{
							aim->HP -= hero->Attack * 1.2;
						}
						else {
							aim->HP -= hero->Attack;
						}
					}
					else if ((*it)->getName() == "skill") {
						aim->HP -= 250 * (1 + hero->Attack * 0.25 + hero->Level * 0.01);
					}
					else if ((*it)->getName() == "magic") {
						aim->HP -= 120 * (1 + hero->Skill_Enhance * 0.01 + hero->Level * 0.01);
					}
					else if ((*it)->getName() == "burnning_bullet") {
						aim->HP -= hero->Attack * 1.2;
					}
					this->removeChild(*it);

					it = bullet.erase(it);

				}
				else
					it++;
			}
			else
			{
				auto aim = (Tower*)background->getChildByTag(choice);
				Point aimPoint;
				aimPoint = aim->getPosition() + background->getPosition();
				if (aim == NULL)break;
				Point pos1 = (*it)->getPosition();

				(*it)->setRotation(360 - 180 / 3.14 * atan2((aimPoint.y - (*it)->getPositionY()), (aimPoint.x - (*it)->getPositionX())));

				float r2 = sqrt((pos1.x - aimPoint.x) * (pos1.x - aimPoint.x) + (pos1.y - aimPoint.y) * (pos1.y - aimPoint.y));

				float distance = (hero->getPosition().x - aimPoint.x) * (hero->getPosition().x - aimPoint.x) + (hero->getPosition().y - aimPoint.y) * (hero->getPosition().y - aimPoint.y);

				if (distance <= (hero->Attack_Range * hero->Attack_Range))
				{
					hero->Able_To_Attack = 1;
				}
				else
				{
					hero->Able_To_Attack = 0;
				}

				(*it)->setPosition(Point(pos1.x + 20 * (aimPoint.x - pos1.x) / r2, pos1.y + 20 * (aimPoint.y - pos1.y) / r2));



				if (r2 <= 10)
				{
					if ((*it)->getName() == "attack")
					{
						if (hero->Critical == 1)
						{
							aim->HP -= hero->Attack * 1.2;
						}
						else {
							aim->HP -= hero->Attack;
						}
					}
					else if ((*it)->getName() == "skill") {
						aim->HP -= 250 * (1 + hero->Attack * 0.25 + hero->Level * 0.01);
					}
					else if ((*it)->getName() == "magic") {
						aim->HP -= 120 * (1 + hero->Skill_Enhance * 0.01 + hero->Level * 0.01);
					}
					else if ((*it)->getName() == "burnning_bullet") {
						aim->HP -= hero->Attack * 1.2;
					}
					this->removeChild(*it);

					it = bullet.erase(it);

				}
				else
					it++;
			}
		}
	}
	if (bullett.size() >= 1)
	{
		for (auto it = bullett.begin(); it != bullett.end();)
		{

			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((hero->position.y - (*it)->getPositionY()), (hero->position.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - hero->position.x) * (pos1.x - hero->position.x) + (pos1.y - hero->position.y) * (pos1.y - hero->position.y));

			(*it)->setPosition(Point(pos1.x + 20 * (hero->position.x - pos1.x) / r3, pos1.y + 20 * (hero->position.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				hero->HP -= 300;
				this->removeChild(*it);

				it = bullett.erase(it);

			}
			else
				it++;
		}
	}
	if (_bullett7.size() >= 1)
	{
		for (auto it = _bullett7.begin(); it != _bullett7.end();)
		{

			Point pos1 = (*it)->getPosition();
			Point _heroPos = background->convertToWorldSpaceAR(soldier_7->getPosition()) + Point(2430, 1345);

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				soldier_7->HP -= 300;
				this->removeChild(*it);

				it = _bullett7.erase(it);

			}
			else
				it++;
		}
	}
	if (_bullett8.size() >= 1)
	{
		for (auto it = _bullett8.begin(); it != _bullett8.end();)
		{

			Point _heroPos = background->convertToWorldSpaceAR(soldier_8->getPosition()) + Point(2440, 1355);
			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				soldier_8->HP -= 300;
				this->removeChild(*it);

				it = _bullett8.erase(it);

			}
			else
				it++;
		}
	}
	if (_bullett9.size() >= 1)
	{
		for (auto it = _bullett9.begin(); it != _bullett9.end();)
		{
			Point _heroPos = background->convertToWorldSpaceAR(soldier_9->getPosition()) + Point(2450, 1365);

			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				soldier_9->HP -= 300;
				this->removeChild(*it);

				it = _bullett9.erase(it);

			}
			else
				it++;
		}
	}
	if (bullett7.size() >= 1)
	{
		for (auto it = bullett7.begin(); it != bullett7.end();)
		{

			Point _heroPos = background->convertToWorldSpaceAR(_soldier_7->getPosition()) + Point(655, 505);

			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				_soldier_7->HP -= 300;
				this->removeChild(*it);

				it = bullett7.erase(it);

			}
			else
				it++;
		}
	}
	if (bullett8.size() >= 1)
	{
		for (auto it = bullett8.begin(); it != bullett8.end();)
		{
			Point _heroPos = background->convertToWorldSpaceAR(_soldier_8->getPosition()) + Point(645, 495);
			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				_soldier_8->HP -= 300;
				this->removeChild(*it);

				it = bullett8.erase(it);

			}
			else
				it++;
		}
	}
	if (bullett9.size() >= 1)
	{
		for (auto it = bullett9.begin(); it != bullett9.end();)
		{

			Point _heroPos = background->convertToWorldSpaceAR(_soldier_9->getPosition()) + Point(635, 485);
			Point pos1 = (*it)->getPosition();

			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				_soldier_9->HP -= 300;
				this->removeChild(*it);

				it = bullett9.erase(it);

			}
			else
				it++;
		}
	}
	if (_bullett.size() >= 1)
	{
		for (auto it = _bullett.begin(); it != _bullett.end();)
		{

			Point pos1 = (*it)->getPosition();
			Point _heroPos = background->convertToWorldSpaceAR(_hero->getPosition()) + Point(2670, 1500);
			(*it)->setRotation(360 - 180 / 3.14 * atan2((_heroPos.y - (*it)->getPositionY()), (_heroPos.x - (*it)->getPositionX())));

			float r3 = sqrt((pos1.x - _heroPos.x) * (pos1.x - _heroPos.x) + (pos1.y - _heroPos.y) * (pos1.y - _heroPos.y));

			(*it)->setPosition(Point(pos1.x + 20 * (_heroPos.x - pos1.x) / r3, pos1.y + 20 * (_heroPos.y - pos1.y) / r3));

			if (r3 <= 10)
			{
				_hero->HP -= 300;
				this->removeChild(*it);

				it = _bullett.erase(it);

			}
			else
				it++;
		}
	}
	this->removeChildByName("kda");
	this->removeChildByName("eco");
	this->removeChildByName("weapon0");
	string kill = to_string(hero->kill);
	string dead = to_string(hero->dead);
	string assist = to_string(hero->assist);
	Label* kda = Label::Label::createWithSystemFont(kill + " " + dead + " " + assist, "Arial", 20);
	kda->setPosition(3 * visibleSize.width / 4, visibleSize.height - 20);
	kda->setName("kda");
	this->addChild(kda);
	string _ = "$ ";
	string money = to_string(hero->Money);
	Label* eco = Label::Label::createWithSystemFont(_ + money, "Arial", 20);
	eco->setPosition(3 * visibleSize.width / 4, visibleSize.height - 40);
	eco->setName("eco");
	this->addChild(eco);
	string weapon = "Weapon  ";
	for (auto it = hero->Weapon.begin(); it != hero->Weapon.end(); it++)
	{
		int num = (*it).first;
		int cnt = (*it).second;
		for (int i = 1; i <= cnt; i++)
		{
			string temp = to_string(num) + " ";
			weapon += temp;
		}
	}
	Label* weapon0 = Label::Label::createWithSystemFont(weapon, "Arial", 20);
	weapon0->setPosition(3 * visibleSize.width / 4, visibleSize.height - 60);
	weapon0->setName("weapon0");
	this->addChild(weapon0);
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

	pixel = pixel + y * 3000 + x;        //480 是图片的宽

	c.r = *pixel & 0xff;

	c.g = (*pixel >> 8) & 0xff;

	c.b = (*pixel >> 16) & 0xff;

	c.a = (*pixel >> 24) & 0xff;

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

	pos = touch->getLocation();

	flag = 1;

	Point touchLocation = convertTouchToNodeSpace(touch);


	for (int i = 2; i <= 9; i++)
	{
		auto sprite = background->getChildByTag(i);
		Point spritePoint;
		switch (i)
		{
		case 2:
			spritePoint = background->getPosition() + Point(1800, 1000);
			break;
		case 3:
			spritePoint = background->getPosition() + Point(1960, 1160);
			break;
		case 4:
			spritePoint = background->getPosition() + Point(2220, 1255);
			break;
		case 5:
			spritePoint = background->getPosition() + Point(2430, 1390);
			break;
		case 6:
			spritePoint = background->convertToWorldSpaceAR(sprite->getPosition()) + Point(2670, 1500);
			break;
		case 7:
			spritePoint = background->convertToWorldSpaceAR(sprite->getPosition()) + Point(2430, 1345);
			break;
		case 8:
			spritePoint = background->convertToWorldSpaceAR(sprite->getPosition()) + Point(2440, 1355);
			break;
		case 9:
			spritePoint = background->convertToWorldSpaceAR(sprite->getPosition()) + Point(2450, 1365);
			break;
		}
		float r2 = sqrt((touchLocation.x - spritePoint.x) * (touchLocation.x - spritePoint.x) + (touchLocation.y - spritePoint.y) * (touchLocation.y - spritePoint.y));

		if (r2 <= 50)
		{

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

			hero->setAction(hero->direction, "attack", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);

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

			hero->setAction(hero->direction, "attack", 4, hero->ID);

		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);

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

				hero->setAction(hero->direction, "attack", 4, hero->ID);

				if (hero->Skill_E_On_Release == 1)
				{
					hero->setVisible(true);

					hero->Skill_E_On_Release = 2;

				}
			}
		}
		case EventKeyboard::KeyCode::KEY_Q:
		{
			//hero->setAction(hero->direction, "skill", 4);
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_E:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);
		}
		case EventKeyboard::KeyCode::KEY_R:
		{
			hero->setAction(hero->direction, "skill", 4, hero->ID);

		}
		}
	}
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero->life == 1)
	{
		Point aimPoint;
		if (choice >= 6) {
			auto aim = (Hero*)background->getChildByTag(choice);
			aimPoint = background->convertToWorldSpaceAR(aim->getPosition()) + Point(2670, 1500);
		}
		else {
			auto aim = (Tower*)background->getChildByTag(choice);
			aimPoint = aim->getPosition() + background->getPosition();
		}
		float distance = (hero->getPosition().x - aimPoint.x) * (hero->getPosition().x - aimPoint.x) + (hero->getPosition().y - aimPoint.y) * (hero->getPosition().y - aimPoint.y);
		if (hero->ID == 1) {
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (hero->Attack_Ready == 0 && (distance <= 300000)) {

					auto bullet0 = Sprite::create("hack.png");

					bullet0->setPosition(Point(hero->position.x, hero->position.y));

					this->addChild(bullet0);

					bullet0->setName("attack");

					bullet0->setScale(0.4f);

					bullet.push_back(bullet0);

					hero->Attack_Ready = 1;
				}
				break;
			}

			case EventKeyboard::KeyCode::KEY_Q: {
				if (hero->MP >= 50 && hero->Skill_Q_On_Release == 0) {

					hero->MP -= 50;

					Effect_Q = Sprite::create("slash.png");

					Effect_Q->setScale(0.4f);

					hero->Skill_Q_On_Release = 1;
				}

				break;
			}
			case EventKeyboard::KeyCode::KEY_W: {

				if (hero->Skill_W_On_Release == 0 && hero->MP >= 75)
				{
					hero->MP -= 75;

					Effect_W = Sprite::create("roar.png");

					Effect_W->setScale(0.4f);

					Effect_W->setPosition(400, 200);

					this->addChild(Effect_W);

					hero->Skill_W_On_Release = 1;

				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_E: {
				if (hero->MP > 25 && hero->Skill_E_On_Release == 0)
				{
					hero->MP -= 25;

					hero->Skill_E_On_Release = 1;

					hero->speed = hero->speed * (1 + 0.3);
				}
				else if (hero->Skill_E_On_Release == 1) {
					hero->Skill_E_On_Release = 0;

					hero->speed = hero->speed / 1.3;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_R: {
				if (hero->MP >= 200 && hero->Level >= 6) {
					hero->MP -= 200;
					hero->Skill_R_On_Release = 1;
				}
			}
			}
		}
		if (hero->ID == 2) {
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (hero->Attack_Ready == 0 && (distance <= 450000)) {


					auto bullet0 = Sprite::create("magicbullet.png");

					bullet0->setPosition(Point(hero->position.x, hero->position.y));

					this->addChild(bullet0);

					bullet0->setName("attack");

					bullet.push_back(bullet0);

					hero->Attack_Ready = 1;
				}
				break;
			}

			case EventKeyboard::KeyCode::KEY_Q: {
				if (hero->MP >= 75 && hero->Skill_Q_On_Release == 0)
				{
					hero->MP -= 75;

					auto visibleSize = Director::getInstance()->getVisibleSize();

					auto bullet0 = Sprite::create("magicbomb.png");

					bullet0->setPosition(Point(hero->position.x, hero->position.y));

					bullet0->setScale(0.5f);

					this->addChild(bullet0);

					bullet0->setName("magic");

					bullet.push_back(bullet0);

					hero->Skill_Q_On_Release = 1;

				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_W: {

				if (hero->MP >= 125 && hero->Skill_W_On_Release == 0)
				{
					hero->MP -= 125;

					hero->Skill_W_On_Release = 1;

					Effect_W = Sprite::create("explosion.png");

					Effect_W->setPosition(Point(pos.x, pos.y));

					Effect_W->setScale(0.6f);

					Effect_W->setName("explosion");

					this->addChild(Effect_W);
				}

				break;
			}
			case EventKeyboard::KeyCode::KEY_E: {
				if (hero->MP > 100 && hero->Skill_E_On_Release == 0)
				{
					hero->MP -= 100;

					hero->Skill_E_On_Release = 1;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_R: {
				if (hero->MP >= 200 && hero->Level >= 6) {
					hero->MP -= 200;
					hero->Skill_Q_On_Release = 0;
					hero->Skill_E_On_Release = 0;
				}
			}
			}
		}
		if (hero->ID == 3) {
			switch (keycode)
			{
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (hero->Attack_Ready == 0 && (distance <= 450000)) {
					if (hero->Skill_E_On_Release == 2 || hero->Skill_E_On_Release == 3)
					{
						hero->setVisible(true);

						hero->speed = hero->speed / 2;

						hero->Critical_Rate = hero->Critical_Rate / 2;

						hero->Skill_E_On_Release = 0;

					}
					auto visibleSize = Director::getInstance()->getVisibleSize();

					if (hero->Skill_Q_On_Release == 1)
					{
						hero->MP -= 8;

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

						bullet0->setName("burnning_bullet");

						bullet.push_back(bullet0);

					}
					hero->Attack_Ready = 1;
				}
				break;
			}

			case EventKeyboard::KeyCode::KEY_Q: {
				if (hero->Skill_Q_On_Release == 0) {
					hero->Skill_Q_On_Release = 1;
				}
				else if (hero->Skill_Q_On_Release == 1) {
					hero->Skill_Q_On_Release = 0;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_W: {
				if (hero->MP >= 50 && hero->Skill_W_On_Release == 0)
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

					hero->Critical_Rate = hero->Critical_Rate * 10;

					hero->speed = hero->speed * 2;

					hero->Skill_E_On_Release = 1;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_R: {
				if (hero->MP >= 120 && hero->Skill_R_On_Release == 0)
				{
					if (hero->Level >= 6)
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
				break;
			}
			}
		}
	}
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
		ShopLayer* scrollView = ShopLayer::createLayer(hero);
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
void HelloWorld::win()
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, WinLayer::createScene()));
}
void HelloWorld::lose()
{
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f, LoseLayer::createScene()));
}