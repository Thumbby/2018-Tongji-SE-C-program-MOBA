#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class LoseLayer :public Layer
{
public:
	bool init();
	static Scene* createScene();
	CREATE_FUNC(LoseLayer);
};