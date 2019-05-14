#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	image = new Image();
	image->initWithImageFile("gf.png");
	CCLOG("%d，%d", image->getHeight(), image->getWidth());
	
	background = Sprite::create("background2.jpg");
	background->setPosition(0, 0);
	background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background,0,200);
	//background[1] = Sprite::create("background3.png");
    //background[1]->setOpacity(150);
	//background[1]->setPosition(-600, -550);
	//background[1]->setAnchorPoint(Vec2(0, 0));
	//this->addChild(background[1],1 ,201);

	hero = Hero::createHeroSprite(Vec2(320, 180), 2, "stand");
	addChild(hero);
	monster = Monster::createMonsterSprite(Vec2(1050, 950), 2, "stand");
	addChild(monster);
	rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(100, 100));
	addChild(rocker, 3);
	rocker->startRocker(true);

	scheduleUpdate();
	//delete image;
	return true;
}
void HelloWorld::update(float dt)
{

	if (rocker->isCanMove == true)
	{
		if (hero->isRun == false)
		{
			hero->isRun = true;
			hero->direction = rocker->direction;
			hero->setAction(hero->direction, "run", 8);
		}
		else if (hero->isRun == true)
		{
			if (hero->direction != rocker->direction)
			{
				hero->direction = rocker->direction;
				hero->setAction(hero->direction, "run", 8);
			}
		}
		float r = sqrt((rocker->dx*rocker->dx) + (rocker->dy*rocker->dy));
		//CCLOG("hhh%f", r);
		float x = 0;
		float y = 0;
		float w = 0;
		if (0 != r)
		{
			//CCLOG("YES");
		}
		if (r !=0 )
		{
			float w = 1 / r;
			float x = rocker->dx / r;
			float y = rocker->dy / r;
		}
		//CCLOG("%f", w);
		//CCLOG("%f,%f", rocker->dx / r, rocker->dy / r);
		//CCLOG("%f,%f", x, y);
		//Point position = background[1]->getPosition();
		float m = background->getPositionX();
		float n = background->getPositionY();
		float monsterX = monster->getPositionX();
		float monsterY = monster->getPositionY();
       // CCLOG("%f,%f", m, n);
		/*auto pix = 320 - (int)m;
		auto piy = 180 - (int)n;
		//
		if (x > 0)
		{
			pix = pix - 3;
		}
		else
		{
			pix = pix + 3;
		}
		if (y > 0)
		{
			piy += 3;
		}
		else
		{
			piy -= 3;
		}*/
		//if (getColor(pix, piy).a == 255)
		auto pix = 320-(int)background->getPositionX();//320 - 
		auto piy = 160-(int)background->getPositionY();//180 -
		CCLOG("%d,%d", pix, piy);
		/*if (x > 0)
		{
			pix = pix - 3;
		}
		else
		{
			pix = pix + 3;
		}
		if (y > 0)
		{
			piy += 3;
		}
		else
		{
			piy -= 3;
		}*/
		//if ((getColor(pix, piy).g ==255)&&(getColor(pix, piy).b == 0)&&(getColor(pix, piy).r == 0))
		//if(getColor(pix, piy).g >=0)
		//{
			
		   //auto v=getColor(0, 0);
			//CCLOG("color r:%d g:%d b:%d a:%d ", v.r, v.g, v.b, v.a);
			if (r != 0)
			{
				auto sp1 = this->getChildByTag(200);
				//sp1->setPosition((m - x)*dt, (n - y)*dt);
				//sp1->setPosition(m - x, n - y);
				sp1->setPosition(m - rocker->dx / r, n - rocker->dy / r);
				monster->setPosition(monsterX - rocker->dx / r, monsterY - rocker->dy / r);
				//auto sp2 = this->getChildByTag(201);
				//sp2->setPosition((m - x)*dt, (n - y)*dt);
				//sp2->setPosition(m - rocker->dx / r, n - rocker->dy / r);
			}
	    //}
	}
	else if (hero->isRun == true && rocker->isCanMove == false)
	{
		hero->isRun = false;
		hero->setAction(hero->direction, "stand", 7);
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
	unsigned char *m_pData = image->getData();

	//int x = (int)posx;
	//int y = (int)posy;
	Color4B c = { 0, 0, 0, 0 };
	unsigned int *pixel = (unsigned int *)m_pData;
	//int width = image->getWidth();
	pixel = pixel + y*2998 + x;        //480 是图片的宽
	c.r = *pixel & 0xff;
	c.g = (*pixel >> 8) & 0xff;
	c.b = (*pixel >> 16) & 0xff;
	c.a = (*pixel >> 24) & 0xff;
	CCLOG("color r:%d g:%d b:%d a:%d ", c.r, c.g, c.b, c.a);
	return c;

}

/*getColor(int x, int y)
{
	ccColor4B c = { 0, 0, 0, 0 };
	//cocos2dx使用的是openGL坐标系，y坐标是从下到上递增的。
	//libpng读取png图片时是从上到下逐行读取的，因此这里的纵坐标需要处理下。
	y = image->getHeight() - y;
	int width = image->getWidth();

	unsigned char *data_ = image->getData();
	unsigned int *pixel = (unsigned int *)data_;//以unsigned int来处理

	pixel = pixel + (y * width) + x;//跳到指定的像素点。
	c.a = (*pixel >> 24) & 0xff;

	float scale = (c.a + 1.0f) / 256;
	c.r = *pixel & 0xff;
	c.r = c.r / scale;
	c.g = (*pixel >> 8) & 0xff;
	c.g = c.g / scale;
	c.b = (*pixel >> 16) & 0xff;
	c.b = c.b / scale;
	//CCLOG("%d,%d==%d,%d,%d,%d", x, y, c.r, c.g, c.b, c.a);
	return c;
}*/