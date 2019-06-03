#include "Tower.h"
using namespace cocos2d;
bool Tower::init()
{
	if (!Layer::init())
		return false;
	Attack = 20;
	HP = 100;
	MaxHP = 100;
	range = 1000;
	tower = Sprite::create("range.png");
	tower->setScale(0.3f);
	this->addChild(tower);
	sprBar = Sprite::create("bar.png");

	sprBar->setScale(0.15f);

	this->addChild(sprBar);

	sprBlood = Sprite::create("blood.png");

	progress = ProgressTimer::create(sprBlood);

	progress->setType(ProgressTimer::Type::BAR);

	progress->setScale(0.15f);

	progress->setMidpoint(Point(0, 0.5));

	progress->setBarChangeRate(Point(1, 0));

    sprBar->setPosition(Point(this->getPosition().x, this->getPosition().y + 80));

	progress->setPosition(Point(this->getPosition().x, this->getPosition().y + 80));
	this->addChild(progress);
	return true;
}

void Tower::update()
{
	progress->setPercentage((((float)this->HP) / this->MaxHP) * 100);
}