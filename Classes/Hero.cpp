#include "Hero.h"
USING_NS_CC;
int ID2;
Hero* Hero::createHeroSprite(Point position, int direction, const char* name,int ID)
{
	ID2 = ID;
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit(position, direction, name);
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
void Hero::heroInit(Point position, int direction, const char* name)
{
	this->isRun = false;
	this->position = position;
	sprite = Sprite::create(String::createWithFormat("%s11.png", name)->getCString());
	sprite->setPosition(position);
	addChild(sprite);
	auto* action = createAnimate(1, "stand", 2);
	action->setTag(100);
	sprite->runAction(action);
}
Animate* Hero::createAnimate(int direction, const char* action, int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	if (ID2==1)
	{
		m_frameCache->addSpriteFramesWithFile("guanyu.plist", "guanyu.png");
	}
	if (ID2 == 2)
	{
		m_frameCache->addSpriteFramesWithFile("zhugeliang.plist", "zhugeliang.png");
	}
	if (ID2 == 3)
	{
		m_frameCache->addSpriteFramesWithFile("huangzhong.plist", "huangzhong.png");
	}
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d%d.png", action, direction, i)->getCString());
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
void Hero::setAction(int direction, const char* action, int num)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, num);
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
void Hero::Experience_System(int exp, int Level_Exp) {
	Exp = Exp + exp;
	if (Exp >= Level_Exp) {
		Level++;
		Exp = Exp - Level_Exp;
		Attack += 5;
		MaxHP += 20;
		MaxMP += 10;
		Defense += 5;
	}
	if (Level > 18) {
		Level = 18;
		Exp = 0;
	}
}
void Hero::Money_System(int money) {
	Money = Money + money;
}
void Hero::Get_Attack(int damage) {
	HP = HP - damage;
}