#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Hero.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class ShopLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(ShopLayer);
	void shopMenuCallback(Ref* psender);
	void buyCallback(Ref* psender, int price);
	void sellCallback(Ref* psender, int num, int price);
	static ShopLayer* createLayer(Hero* hero1);
private:
	ScrollView* mscrollView;
	Point touchPoint;
	Point offsetPoint;
	int m_nCurPage;

};