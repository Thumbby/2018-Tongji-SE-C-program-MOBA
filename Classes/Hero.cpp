#include "Hero.h"
USING_NS_CC;
Hero* Hero::createHeroSprite(Point position, int direction, const char* name, int ID)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->ID = ID;
		hero->heroInit(position, direction, name,ID);
		hero->setScale(1.2f);
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}
bool Hero::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void Hero::heroInit(Point position, int direction, const char* name,int ID)
{
	this->isRun = false;
	this->position = position;
	sprite = Sprite::create(String::createWithFormat("%d%s11.png",ID, name)->getCString());
	sprite->setPosition(position);
	addChild(sprite);
	auto* action = createAnimate(1, "stand", 2,ID);
	action->setTag(100);
	sprite->runAction(action);
}
Animate* Hero::createAnimate(int direction, const char* action, int num,int ID)
{
	
	auto* m_frameCache = SpriteFrameCache::getInstance();
	if (ID == 1)
	{
		m_frameCache->addSpriteFramesWithFile("hero/guanyu.plist", "hero/guanyu.png");
	}
	if (ID == 2)
	{
		m_frameCache->addSpriteFramesWithFile("hero/zhugeliang.plist", "hero/zhugeliang.png");
	}
	if (ID == 3)
	{
		m_frameCache->addSpriteFramesWithFile("hero/huangzhong.plist", "hero/huangzhong.png");
	}
	if (ID == 4)
	{
		m_frameCache->addSpriteFramesWithFile("hero/jinzhanxiaobing.plist", "hero/jinzhanxiaobing.png");
	}
	if (ID == 5)
	{
		m_frameCache->addSpriteFramesWithFile("hero/yuanchengxiaobing.plist", "hero/yuanchengxiaobing.png");
	}
	if(ID==6)
	{
		m_frameCache->addSpriteFramesWithFile("hero/paoche.plist", "hero/paoche.png");
	}
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%d%s%d%d.png", ID ,action, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	if (action == "stand" || action == "run")
	{
		animation->setLoops(-1);
	}
	else if (action == "attack" || action == "skill")
	{
		animation->setLoops(1);
	}
	animation->setDelayPerUnit(0.2f);//每两张图片的时间隔，图片数目越少，间隔最小就越小

	//将动画包装成一个动作
	return Animate::create(animation);
}
void Hero::setAction(int direction, const char* action, int num,int ID)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, num,ID);
	animate->setTag(100);
	sprite->runAction(animate);
}
void Hero::moveTo(float x, float y)
{
	float r = sqrt(x * x + y * y);
	position.x += x / r;
	position.y += y / r;
	sprite->setPosition(position);
}
/*void Hero::Death() {
	if (HP <= 0) {
		this->setVisible(false);
	}
}*/
int Hero::Max_Exp(int level) {
	int max_exp;
	max_exp = 300 + (level - 1) * 50;
	return max_exp;
}